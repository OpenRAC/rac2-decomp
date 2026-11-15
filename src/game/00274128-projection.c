/* View-state layout and reconstruction adapted from OpenRAC/rac1-decomp
 * src/game/draw.c, UpdateViewContext (GPL-3.0); RC2-specific conditions retained. */
#include "common.h"

typedef u32 VecQuad __attribute__((mode(TI), aligned(16)));
typedef union { VecQuad q; float f[4]; int i[4]; } Vec4;
struct ViewP {
    s32 fog_color; s32 unk4; s32 unk8; s32 unkC;
    Vec4 regs[5]; Vec4 gif[4];
    f32 near_clip; f32 far_clip; f32 aspect_x; f32 aspect_y;
    Vec4 fov; f32 proj[16]; f32 proj2[16]; f32 proj3[16];
    Vec4 inverse_screen_scale, screen_scale, screen_bias, inverse_projection_scale, viewport_aspect, aspect_scale, clip_scale, clip_distances;
    f32 half_width, half_height, scr_x, scr_y, fog_mul, fog_add, fog_near_dist, fog_far_dist, fog_slope, fog_base, fog_near_int, fog_far_int;
    s32 fog_r, fog_g, fog_b;
};

extern struct ViewP D_001B9040;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001A8BB0 MACRO_ADDR;
extern unsigned char D_001A7BB1 MACRO_ADDR;
extern Vec4 D_001B9300[4], D_002633E0[3], D_002636D0[2];
extern float D_001AC6E0[4];
extern float D_001ACBD0 MACRO_ADDR;
extern float D_00264DB0, D_002650B0;
struct FogRegs2P { char pad[0x28]; int mul, max, far_int, near_int; };
extern struct FogRegs2P D_00263640, D_00263690;
struct FogPacketP { char pad[0x10]; int mul, far_int, near_int; char pad1c[0x44]; Vec4 constants[3]; char pad90[0x10]; int x, y; };
extern struct FogPacketP D_00263440;
extern float func_00283180(float), func_00283248(float, float);
extern void func_002EF080(void), func_00282AB0(void *, const void *, int);

/* Rebuild clip, fog, projection and renderer packet constants for the current view. */
void func_0027AB40(void) {
    struct ViewP *view;
    struct ViewP *clip_view;
    struct ViewP *packet_view;
    f32 depth_scale;
    f32 depth_bias;
    f32 horizontal_clip_scale;
    f32 vertical_clip_scale;
    f32 fog_distance_range;
    f32 fog_intensity_range;
    f32 fog_distance_slope;
    f32 projection_near_clip;
    f32 far_clip;
    f32 fog_multiplier;
    f32 projection_fog_multiplier;
    f32 horizontal_fov;
    f32 vertical_fov;
    f32 viewport_width;
    f32 viewport_height;
    s32 near_bits;
    s32 far_bits;
    s32 mul_bits;

    depth_scale = -8388080.0f;
    depth_bias = 8388112.0f;
    if (gIsPalVideo != 0) {
        D_001B9040.fov.f[1] = D_001B9040.fov.f[0] * 0.756f;
    } else {
        D_001B9040.fov.f[1] = D_001B9040.fov.f[0] * 0.775f;
    }
    if (D_001A7BB1) {
        D_001B9040.fov.f[1] *= 0.7500000596046448f;
    }
    view = &D_001B9040;
    view->aspect_x = view->scr_x / view->half_width;
    view->aspect_y = view->scr_y / view->half_height;
    view->fov.f[2] = 1.0f / FastSinOrCosA(FastMatrixHelperA(1.0f, view->fov.f[0]));
    view->fov.f[3] = 1.0f / FastSinOrCosA(FastMatrixHelperA(1.0f, view->fov.f[1]));
    horizontal_clip_scale = 1.0f / FastSinOrCosA(FastMatrixHelperA(1.0f, view->fov.f[0] * view->aspect_x));
    vertical_clip_scale = 1.0f / FastSinOrCosA(FastMatrixHelperA(1.0f, view->fov.f[1] * view->aspect_y));
    horizontal_clip_scale /= view->fov.f[2];
    vertical_clip_scale /= view->fov.f[3];
    horizontal_clip_scale += vertical_clip_scale;
    horizontal_clip_scale *= 0.5f;
    if (gCurrentGameMode == 2 && view->fov.f[0] < 0.62f)
        horizontal_clip_scale *= 1.15f;
    clip_view = &D_001B9040;
    clip_view->aspect_scale.f[2] = 1.0f / clip_view->aspect_x;
    clip_view->aspect_scale.f[3] = 1.0f / clip_view->aspect_y;
    clip_view->clip_scale.f[0] = clip_view->fov.f[2];
    clip_view->clip_scale.f[1] = clip_view->fov.f[3];
    clip_view->clip_scale.f[2] = horizontal_clip_scale;
    clip_view->clip_distances.f[0] = clip_view->far_clip;
    clip_view->clip_distances.f[1] = clip_view->near_clip;
    clip_view->aspect_scale.f[0] = clip_view->aspect_x;
    clip_view->aspect_scale.f[1] = clip_view->aspect_y;
    qcopy(&D_001B9300[0], &clip_view->fov);
    qcopy(&D_001B9300[1], &clip_view->aspect_scale);
    qcopy(&D_001B9300[2], &clip_view->clip_scale);
    qcopy(&D_001B9300[3], &clip_view->clip_distances);

    if (clip_view->fog_far_dist < clip_view->fog_near_dist + 1024.0f)
        clip_view->fog_far_dist = clip_view->fog_near_dist + 1024.0f;

    /* Carry the float bits into packet fields. */
    far_bits = *(s32 *)&clip_view->fog_far_int;
    near_bits = *(s32 *)&clip_view->fog_near_int;
    fog_distance_range = clip_view->fog_far_dist - clip_view->fog_near_dist;
    fog_intensity_range = clip_view->fog_far_int - clip_view->fog_near_int;
    fog_multiplier = fog_intensity_range * clip_view->near_clip / fog_distance_range;
    fog_distance_slope = fog_intensity_range / (fog_distance_range / 1024.0f);
    clip_view->fog_add =
        (clip_view->fog_near_int * clip_view->fog_far_dist - clip_view->fog_far_int * clip_view->fog_near_dist) /
        fog_distance_range;
    clip_view->fog_slope = fog_distance_slope;
    clip_view->fog_base = clip_view->fog_near_int - clip_view->fog_near_dist * (fog_distance_slope * (1.0f / 1024.0f));
    clip_view->fog_mul = fog_multiplier;
    D_001ACBD0 = fog_multiplier;
    D_00264DB0 = fog_multiplier;
    D_002650B0 = fog_multiplier;
    mul_bits = *(s32 *)&clip_view->fog_mul;
    D_00263440.mul = mul_bits;
    D_00263440.far_int = far_bits;
    D_00263440.near_int = near_bits;
    D_00263640.mul = mul_bits;
    D_00263690.mul = mul_bits;
    D_00263640.far_int = far_bits;
    D_00263640.near_int = near_bits;
    D_00263690.far_int = far_bits;
    D_00263690.near_int = near_bits;
    D_00263640.max = 0x437EFFFF;
    D_00263690.max = 0x437EFFFF;
    SetTfragDists();

    projection_near_clip = clip_view->near_clip;
    far_clip = clip_view->far_clip;
    horizontal_fov = clip_view->fov.f[0];
    vertical_fov = clip_view->fov.f[1];
    viewport_width = clip_view->half_width;
    viewport_height = clip_view->half_height;
    projection_fog_multiplier = clip_view->fog_mul;
    D_001AC6E0[0] = 0.5f / 210000.0f;
    D_001AC6E0[1] = -0.5f / 210000.0f;
    D_001AC6E0[2] = 0.5f;
    D_001AC6E0[3] = viewport_width / (horizontal_fov * 210000.0f);
    clip_view->proj[0] = viewport_width / (horizontal_fov * projection_near_clip);
    clip_view->proj[1] = 0.0f;
    clip_view->proj[2] = 0.0f;
    clip_view->proj[3] = 0.0f;
    clip_view->proj[4] = 0.0f;
    clip_view->proj[5] = viewport_height / (vertical_fov * projection_near_clip);
    clip_view->proj[6] = 0.0f;
    clip_view->proj[7] = 0.0f;
    clip_view->proj[8] = 0.0f;
    clip_view->proj[9] = 0.0f;
    clip_view->proj[10] = (far_clip + projection_near_clip) /
                           (projection_near_clip * (far_clip - projection_near_clip)) * depth_scale;
    clip_view->proj[11] = 1.0f / projection_near_clip * projection_fog_multiplier;
    clip_view->proj[12] = 0.0f;
    clip_view->proj[13] = 0.0f;
    clip_view->proj[14] = projection_near_clip * (far_clip * -2.0f) /
                           (projection_near_clip * (far_clip - projection_near_clip)) * depth_scale;
    clip_view->proj[15] = 0.0f;
    CopyMemoryAligned(clip_view->proj2, clip_view->proj, 0x40);
    clip_view->proj2[11] = 1.0f / clip_view->near_clip;
    CopyMemoryAligned(clip_view->proj3, clip_view->proj2, 0x40);
    clip_view->proj3[0] /= clip_view->scr_x;
    clip_view->proj3[5] /= clip_view->scr_y;
    clip_view->proj3[10] /= depth_scale;
    clip_view->proj3[14] /= depth_scale;
    clip_view->inverse_screen_scale.f[0] = 1.0f / clip_view->scr_x;
    clip_view->inverse_screen_scale.f[1] = 1.0f / clip_view->scr_y;
    clip_view->inverse_screen_scale.f[2] = 1.0f / depth_scale;
    clip_view->inverse_screen_scale.f[3] = 1.0f / clip_view->fog_mul;
    clip_view->screen_scale.f[0] = clip_view->scr_x;
    clip_view->screen_scale.f[1] = clip_view->scr_y;
    clip_view->screen_scale.f[2] = depth_scale;
    clip_view->screen_scale.f[3] = clip_view->fog_mul;
    clip_view->inverse_projection_scale.f[0] = clip_view->scr_x / clip_view->proj[0];
    clip_view->inverse_projection_scale.f[1] = clip_view->scr_y / clip_view->proj[5];
    clip_view->inverse_projection_scale.f[2] = depth_scale / clip_view->proj[10];
    clip_view->inverse_projection_scale.f[3] = clip_view->fog_mul;
    clip_view->screen_bias.f[0] = 2048.0f;
    clip_view->screen_bias.f[1] = 2048.0f;
    clip_view->screen_bias.f[2] = depth_bias;
    clip_view->screen_bias.f[3] = clip_view->fog_add;
    clip_view->viewport_aspect.f[0] = clip_view->scr_x / clip_view->half_width;
    clip_view->viewport_aspect.f[1] = clip_view->scr_y / clip_view->half_height;
    clip_view->viewport_aspect.f[2] = 1.0f;
    clip_view->viewport_aspect.f[3] = 1.0f;
    clip_view->fog_color = *(s32 *)&clip_view->fog_far_int;
    clip_view->unk4 = 0x103E4000;
    clip_view->unk8 = 0xE;
    clip_view->unkC = 0;
    /* Clear the first register quadword before the packet is rebuilt below. */
    qzero_nc(&clip_view->regs[0]);

    packet_view = &D_001B9040;
    packet_view->gif[0].i[0] = *(s32 *)&packet_view->fog_mul;
    packet_view->gif[0].i[1] = 0x303E4000;
    packet_view->gif[0].i[2] = 0x412;
    packet_view->gif[0].i[3] = 0x303EC000;
    packet_view->gif[1].i[0] = *(s32 *)&packet_view->fog_mul;
    packet_view->gif[1].i[1] = 0x302E4000;
    packet_view->gif[1].i[2] = 0x412;
    packet_view->gif[1].i[3] = 0x302EC000;
    packet_view->gif[2].i[0] = *(s32 *)&packet_view->fog_mul;
    packet_view->gif[2].i[1] = 0x20364000;
    packet_view->gif[2].i[2] = 0x41;
    packet_view->gif[2].i[3] = 0;
    packet_view->gif[3].i[0] = *(s32 *)&packet_view->fog_mul;
    packet_view->gif[3].i[1] = 0x20264000;
    packet_view->gif[3].i[2] = 0x41;
    packet_view->gif[3].i[3] = 0;
    qcopy(&packet_view->regs[0], &packet_view->gif[0]);
    qcopy(&packet_view->regs[1], &packet_view->viewport_aspect);
    qcopy(&packet_view->regs[2], &packet_view->inverse_screen_scale);
    qcopy(&packet_view->regs[3], &packet_view->screen_scale);
    qcopy(&packet_view->regs[4], &packet_view->screen_bias);
    qcopy(&D_002633E0[0], &packet_view->screen_bias);
    qcopy(&D_002633E0[1], &packet_view->screen_scale);
    qcopy(&D_002633E0[2], &packet_view->viewport_aspect);
    qcopy(&D_00263440.constants[0], &packet_view->screen_bias);
    qcopy(&D_00263440.constants[1], &packet_view->inverse_screen_scale);
    qcopy(&D_00263440.constants[2], &packet_view->screen_scale);
    D_00263440.x = packet_view->viewport_aspect.i[0];
    D_00263440.y = packet_view->viewport_aspect.i[1];
    qcopy(&D_002636D0[0], &packet_view->screen_scale);
    qcopy(&D_002636D0[1], &packet_view->screen_bias);
}
