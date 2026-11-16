#include "include_asm.h"
#include "names.h"

/* func_L02_003D6388 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void moby_transform_joint_to_world(char *, int, void *);

extern void moby_transform_joint_point(char *, int, void *);

extern void transform_vector(void *, void *, void *);

extern void FastVecAdd(void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern float FastVecDot(void *, void *);

extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

extern float g_camera_l02_position[4];

extern char g_joint_flare_offset_a[8] __attribute__((sda));

extern char g_joint_flare_offset_b[8] __attribute__((sda));

extern unsigned int g_joint_flare_color __attribute__((sda));

extern float g_joint_flare_facing_threshold __attribute__((sda));

extern float g_joint_flare_radius_a __attribute__((sda));

extern float g_joint_flare_size_param __attribute__((sda));

extern float g_joint_flare_radius_b __attribute__((sda));

/* Draws the glow flares at one joint, two offset spots, and fades them out when the joint faces away from the camera. */
void chainblade_draw_joint_flares(char *self, int joint, int mirror) {
    float origin[4];
    float origin2[4];
    float matrix[16];
    float offsetA[4];
    float offsetB[4];
    float toCamera[4];
    float facing[4];
    float facingDot;
    float alpha;
    unsigned int color;

    moby_transform_joint_to_world(self, joint, origin);
    *(TI128 *)origin2 = *(TI128 *)origin;
    moby_transform_joint_point(self, joint, matrix);
    *(TI128 *)offsetA = *(TI128 *)g_joint_flare_offset_a;
    *(TI128 *)offsetB = *(TI128 *)g_joint_flare_offset_b;
    if (mirror != 0) {
        offsetA[1] = -offsetA[1];
        offsetB[1] = -offsetB[1];
    }
    transform_vector(offsetA, offsetA, matrix);
    FastVecAdd(origin, origin, offsetA);
    transform_vector(offsetB, offsetB, matrix);
    FastVecAdd(origin2, origin2, offsetB);
    FastVecSub(toCamera, g_camera_l02_position, origin);
    vec_scale_to_length(toCamera, toCamera, 1.0f);
    vec_scale_to_length(facing, matrix + 8, -1.0f);
    facingDot = FastVecDot(toCamera, facing);
    if (g_joint_flare_facing_threshold < facingDot) {
        color = g_joint_flare_color;
        alpha = (float)(int)(color >> 24);
        color &= 0xFFFFFF;
        facingDot = facingDot * facingDot;
        color |= (int)(facingDot * alpha) << 24;
        gfx_l00_draw_billboard_quad(origin, color, g_joint_flare_radius_a, g_joint_flare_size_param);
        gfx_l00_draw_billboard_quad(origin2, color, g_joint_flare_radius_b, g_joint_flare_size_param);
    }
}
