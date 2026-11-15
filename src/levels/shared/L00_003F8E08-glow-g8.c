#include "common.h"

typedef float V4[4] __attribute__((aligned(16)));
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 corner[4];
    s32 rgba[4];
    float uv[4][2];
    s64 d70;
    s64 d78;
    s64 d80;
    s64 d88;
} Quad;

typedef struct {
    f32 ang[6];
    s32 pad18;
    s16 t1C;
    s16 t1E;
    f32 k20;
    f32 k24;
    s16 n28;
    s16 n2A;
    f32 k2C;
    f32 k30;
    s16 t34;
    s16 t36;
    f32 k38;
    f32 k3C;
    s32 t40;
    f32 k44;
} Pv;

extern f32 D_L00_001B0A98 __attribute__((sda));
extern f32 D_L00_001B0A9C __attribute__((sda));
extern s32 D_L00_001B0AA4 __attribute__((sda));
extern s32 D_L00_001B0AA8 __attribute__((sda));
extern s32 D_L00_001B0B54 __attribute__((sda));
extern f32 D_L00_001B0B58 __attribute__((sda));
extern f32 D_L00_001B0B5C __attribute__((sda));
extern f32 D_L00_001B0B70 __attribute__((sda));
extern s32 D_L00_001B0B74 __attribute__((sda));
extern f32 D_L00_001B0B7C __attribute__((sda));
extern f32 D_L00_001B0B80 __attribute__((sda));
extern s32 D_L00_001B0B84 __attribute__((sda));
extern s32 D_L00_001B0B88 __attribute__((sda));
extern f32 D_L00_001B0B8C __attribute__((sda));
extern f32 D_L00_001B0B90 __attribute__((sda));
extern f32 D_L00_001B0B94 __attribute__((sda));
extern s32 D_L00_001B0B98 __attribute__((sda));
extern s32 D_L00_001B0B9C __attribute__((sda));
extern f32 D_L00_001B0BA0 __attribute__((sda));
extern f32 D_L00_001B0BA4 __attribute__((sda));
extern f32 D_L00_001B0BA8 __attribute__((sda));
extern f32 D_L00_001B0BAC __attribute__((sda));
extern TI128 D_L00_001AA310[];
extern char g_camera_l00_position[];

extern void gfx_project_world_point_to_screen(void *, void *);
extern void gfx_world_to_screen_unit(void *, void *, void *);
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, int, int);
extern void gfx_init_quad_packet_state(void *, s32, s32, s32);
extern int FastDecTimer(void *);
extern float math_fabs(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float cubic_hermite_scalar(float, float, float, float, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern float FastVecLength(void *);
extern void VU1_addGSregister(unsigned int, unsigned long long);

static __inline__ u32 pack_alpha(s32 value)
{
    return (u32)value << 24;
}

/* Width of one flare edge. x and y start at zero: with four expansions they are eight of the RTL insns that
 * take gcse to retail's 717 hash buckets, which is what orders the spill slots from 0x1C0 on. */
static __inline__ void set_edge(f32 *v, s32 i, f32 t, f32 half)
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    if (t < half) {
        y = 2.0f * t;
        v[i] = D_L00_001B0BA4 + (D_L00_001B0BA8 - D_L00_001B0BA4) * y;
    } else {
        x = 2.0f * (t - half);
        v[i] = D_L00_001B0BA8 + (D_L00_001B0BAC - D_L00_001B0BA8) * x;
    }
}

/* Draws a moby's glow: eight camera-facing quads, the screen-edge flare set, then the pvars 0x34 and 0x40 quads.
 * moby is a late copy of the argument, so it has a high pseudo: moby + 0xC0 hashes after the frame addresses and
 * takes the last spill slot. It has to stay the first assignment in the function, or cprop folds it back. */
void draw_moby_glow_sprites(u8 *self)
{
    Quad quad;
    V4 matrix[4];
    V4 dir;
    V4 rot;
    V4 basis[5];
    V4 v140;
    V4 v150;
    V4 v160;
    V4 v170;
    V4 v180;
    V4 v190;
    V4 v1A0;
    V4 v1B0;
    Pv *vars;
    f32 distance;
    f32 fade;
    f32 dot;
    f32 size;
    f32 a;
    f32 scale;
    f32 k;
    s32 color;
    s32 t2;
    s32 b;
    s32 i1;
    s32 i2;
    s32 i3;
    s32 i4;
    s32 i5;
    s32 i6;
    s32 i7;
    s32 i8;
    s32 i9;
    s32 i10;
    s32 i11;
    f32 t;
    f32 least;
    f32 *s;
    f32 inv;
    f32 one;
    f32 span;
    f32 nx;
    f32 ny;
    s32 alpha;
    u8 *moby = self;

    vars = *(Pv **)(moby + 0x68);
    FastVecSub(dir, moby + 0x10, g_camera_l00_position);
    distance = FastVecLength(dir);
    if (distance != 0.0f) {
        FastVecScale(dir, dir, 1.0f / distance);
    }
    fade = 1.0f;
    if (distance < 11.0f) {
        if (distance <= 7.0f) {
            fade = 0.0f;
        } else {
            fade = (distance - 7.0f) * 0.25f;
        }
    }
    dot = FastVecDot(dir, (f32 *)(moby + 0xC0));
    a = IntToFloat(vars->t1C) * vars->k20;
    size = D_L00_001B0A9C + (D_L00_001B0A98 - D_L00_001B0A9C) * a;
    if (vars->t1C < vars->n28) {
        k = IntToFloat(vars->t1C) * vars->k2C;
        a = IntToFloat(D_L00_001B0AA8) * k;
    } else {
        a = IntToFloat(D_L00_001B0AA8);
    }
    a *= dot;
    /* A scheduling barrier: the shift stays ahead of the next call's argument load. */
    do {
        alpha = FloatToInt(a * dot) << 24;
    } while (0);

    if (math_fabs(vars->ang[0]) > 0.00001f) {
        math_build_axis_angle_quat(rot, (f32 *)(moby + 0xC0), vars->ang[0]);
        vec_rotate_by_quaternion(matrix[1], (f32 *)(moby + 0xD0), rot);
        vec_rotate_by_quaternion(matrix[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(matrix[1], (f32 *)(moby + 0xD0));
        qcopy(matrix[2], (f32 *)(moby + 0xE0));
    }
    qcopy(matrix[3], (f32 *)(moby + 0x10));
    FastVecScale(matrix[0], (f32 *)(moby + 0xC0), size);
    FastVecScale(matrix[1], matrix[1], size);
    FastVecScale(matrix[2], matrix[2], size);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    gfx_init_quad_packet_state(&quad, 0x38, 1, 0x80);
    color = alpha | D_L00_001B0AA4;
    quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = color;
    quad.uv[0][0] = 0.0f;
    quad.uv[0][1] = 0.0f;
    quad.uv[1][0] = 0.0f;
    quad.uv[1][1] = 1.0f;
    quad.uv[2][0] = 1.0f;
    quad.uv[2][1] = 0.0f;
    quad.uv[3][0] = 1.0f;
    quad.uv[3][1] = 1.0f;
    for (i1 = 0; i1 < 4; i1++) {
        transform_vector(&quad.corner[i1], &D_L00_001AA310[i1], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    if (math_fabs(vars->ang[0]) > 0.00001f) {
        math_build_axis_angle_quat(rot, (f32 *)(moby + 0xC0), -vars->ang[0]);
        vec_rotate_by_quaternion(matrix[1], (f32 *)(moby + 0xD0), rot);
        vec_rotate_by_quaternion(matrix[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(matrix[1], (f32 *)(moby + 0xD0));
        qcopy(matrix[2], (f32 *)(moby + 0xE0));
    }
    qcopy(matrix[3], (f32 *)(moby + 0x10));
    FastVecScale(matrix[0], (f32 *)(moby + 0xC0), size);
    FastVecScale(matrix[1], matrix[1], size);
    FastVecScale(matrix[2], matrix[2], size);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i2 = 0; i2 < 4; i2++) {
        transform_vector(&quad.corner[i2], &D_L00_001AA310[i2], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    a = IntToFloat(vars->t1E) * vars->k24;
    size = D_L00_001B0B5C + (D_L00_001B0B58 - D_L00_001B0B5C) * a;
    if (vars->t1E < vars->n2A) {
        a = IntToFloat(vars->t1E) * vars->k30;
        k = cubic_hermite_scalar(1.0f, 0.0f, 1.0f, 2.0f, a);
    } else {
        k = 1.0f;
    }
    alpha = FloatToInt(IntToFloat(D_L00_001B0B54) * k * fade);
    a = IntToFloat(alpha) * 0.2f;
    alpha = pack_alpha(alpha);
    b = pack_alpha(FloatToInt(a));
    quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = b | 0xFFFFFF;
    if (math_fabs(vars->ang[1]) > 0.00001f) {
        math_build_axis_angle_quat(rot, (f32 *)(moby + 0xC0), vars->ang[1]);
        vec_rotate_by_quaternion(matrix[1], (f32 *)(moby + 0xD0), rot);
        vec_rotate_by_quaternion(matrix[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(matrix[1], (f32 *)(moby + 0xD0));
        qcopy(matrix[2], (f32 *)(moby + 0xE0));
    }
    scale = size * 1.5f;
    FastVecScale(matrix[0], (f32 *)(moby + 0xC0), scale);
    FastVecScale(matrix[1], matrix[1], scale);
    FastVecScale(matrix[2], matrix[2], scale);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i3 = 0; i3 < 4; i3++) {
        transform_vector(&quad.corner[i3], &D_L00_001AA310[i3], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    {
        b = FloatToInt(IntToFloat(D_L00_001B0B54) * k * fade * 1.5f);
        if (b >= 0x100) {
            b = 0xFF;
        }
        gfx_init_quad_packet_state(&quad, 0x39, 1, 0x80);
        quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = pack_alpha(b) | 0xFFFFFF;
    }
    quad.uv[0][0] = 0.0f;
    quad.uv[0][1] = 0.0f;
    quad.uv[1][0] = 0.0f;
    quad.uv[1][1] = 1.0f;
    quad.uv[2][0] = 1.0f;
    quad.uv[2][1] = 0.0f;
    quad.uv[3][0] = 1.0f;
    quad.uv[3][1] = 1.0f;
    qcopy(basis[3], (f32 *)(moby + 0x10));
    if (math_fabs(vars->ang[2]) > 0.00001f) {
        math_build_axis_angle_quat(rot, (f32 *)(moby + 0xC0), vars->ang[2]);
        vec_rotate_by_quaternion(matrix[1], (f32 *)(moby + 0xD0), rot);
        vec_rotate_by_quaternion(matrix[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(matrix[1], (f32 *)(moby + 0xD0));
        qcopy(matrix[2], (f32 *)(moby + 0xE0));
    }
    scale = size * 1.25f;
    FastVecScale(matrix[0], (f32 *)(moby + 0xC0), scale);
    FastVecScale(matrix[1], matrix[1], scale);
    FastVecScale(matrix[2], matrix[2], scale);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i4 = 0; i4 < 4; i4++) {
        transform_vector(&quad.corner[i4], &D_L00_001AA310[i4], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    if (math_fabs(vars->ang[3]) > 0.00001f) {
        math_build_axis_angle_quat(rot, (f32 *)(moby + 0xC0), vars->ang[3]);
        vec_rotate_by_quaternion(matrix[1], (f32 *)(moby + 0xD0), rot);
        vec_rotate_by_quaternion(matrix[2], (f32 *)(moby + 0xE0), rot);
    } else {
        qcopy(matrix[1], (f32 *)(moby + 0xD0));
        qcopy(matrix[2], (f32 *)(moby + 0xE0));
    }
    qcopy(matrix[3], (f32 *)(moby + 0x10));
    FastVecScale(matrix[0], (f32 *)(moby + 0xC0), size);
    FastVecScale(matrix[1], matrix[1], size);
    FastVecScale(matrix[2], matrix[2], size);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i5 = 0; i5 < 4; i5++) {
        transform_vector(&quad.corner[i5], &D_L00_001AA310[i5], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    color = alpha | 0xFFFFFF;
    quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = color;
    FastVecSub(rot, g_camera_l00_position, (f32 *)(moby + 0x10));
    vec_scale_to_length(rot, rot, 0.25f);
    FastVecAdd(matrix[3], (f32 *)(moby + 0x10), rot);
    cam_compute_view_direction(basis[3], basis[4], 1);
    FastVecSub(basis[0], g_camera_l00_position, matrix[3]);
    vec_scale_to_length(basis[0], basis[0], 1.0f);
    FastVecCross(basis[1], basis[0], basis[4]);
    vec_scale_to_length(basis[1], basis[1], 1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);

    if (math_fabs(vars->ang[4]) > 0.00001f) {
        math_build_axis_angle_quat(v140, basis[0], vars->ang[4]);
        vec_rotate_by_quaternion(matrix[1], basis[1], v140);
        vec_rotate_by_quaternion(matrix[2], basis[2], v140);
    } else {
        qcopy(matrix[1], basis[1]);
        qcopy(matrix[2], basis[2]);
    }
    FastVecScale(matrix[0], basis[0], size);
    FastVecScale(matrix[1], matrix[1], size);
    FastVecScale(matrix[2], matrix[2], size);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i6 = 0; i6 < 4; i6++) {
        transform_vector(&quad.corner[i6], &D_L00_001AA310[i6], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    if (math_fabs(vars->ang[5]) > 0.00001f) {
        math_build_axis_angle_quat(v140, basis[0], vars->ang[5]);
        vec_rotate_by_quaternion(matrix[1], basis[1], v140);
        vec_rotate_by_quaternion(matrix[2], basis[2], v140);
    } else {
        qcopy(matrix[1], basis[1]);
        qcopy(matrix[2], basis[2]);
    }
    scale = size * 0.75f;
    FastVecScale(matrix[0], basis[0], scale);
    FastVecScale(matrix[1], matrix[1], scale);
    FastVecScale(matrix[2], matrix[2], scale);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i7 = 0; i7 < 4; i7++) {
        transform_vector(&quad.corner[i7], &D_L00_001AA310[i7], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    t2 = pack_alpha(FloatToInt(IntToFloat((u8)(alpha >> 24)) * 0.2f));
    gfx_init_quad_packet_state(&quad, 0x38, 1, 0x80);
    color = t2 | 0xFFFFFF;
    quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = color;
    if (math_fabs(vars->ang[1]) > 0.00001f) {
        math_build_axis_angle_quat(v140, basis[0], vars->ang[1]);
        vec_rotate_by_quaternion(matrix[1], basis[1], v140);
        vec_rotate_by_quaternion(matrix[2], basis[2], v140);
    } else {
        qcopy(matrix[1], basis[1]);
        qcopy(matrix[2], basis[2]);
    }
    scale = size * 1.5f;
    FastVecScale(matrix[0], basis[0], scale);
    FastVecScale(matrix[1], matrix[1], scale);
    FastVecScale(matrix[2], matrix[2], scale);
    matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    matrix[3][3] = 1.0f;
    for (i8 = 0; i8 < 4; i8++) {
        transform_vector(&quad.corner[i8], &D_L00_001AA310[i8], matrix);
    }
    draw_world_quad(&quad, 0, 0);

    if (FastDecTimer(&vars->t36) == 0) {
        gfx_project_world_point_to_screen(v140, (f32 *)(moby + 0x10));
        if (v140[0] >= 28492.0f && v140[0] <= 37082.0f && v140[1] >= 28492.0f && v140[1] <= 37082.0f) {
            f32 h;
            inv = 0.000116414434f;
            one = 1.0f;
            v140[0] -= 28492.0f;
            v140[1] -= 28492.0f;
            span = 8590.0f;
            k = (f32)vars->t36 * vars->k38;
            alpha = pack_alpha(FloatToInt(D_L00_001B0BA0 * k));
            math_apply_axis_rotation_to_quat(v150, basis[4], dir, 0.78539824f);
            gfx_init_quad_packet_state(&quad, D_L00_001B0B88, 1, 0x80);
            least = v140[1] <= v140[0] ? v140[1] : v140[0];
            t = least * inv;
            color = alpha | D_L00_001B0B98;
            quad.d70 = 5;
            k = D_L00_001B0B94 / D_L00_001B0B90;
            quad.uv[0][0] = 0.0f;
            quad.uv[0][1] = one;
            quad.uv[1][0] = one;
            quad.uv[1][1] = one;
            quad.uv[2][0] = 0.0f;
            quad.uv[2][1] = 0.0f;
            quad.uv[3][0] = one;
            quad.uv[3][1] = 0.0f;
            quad.rgba[0] = quad.rgba[1] = D_L00_001B0B9C;
            quad.rgba[2] = quad.rgba[3] = color;
            h = 0.5f;
            set_edge(v160, 3, t, h);
            ny = span - v140[1];
            least = ny <= v140[0] ? ny : v140[0];
            t = least * inv;
            h = 0.5f;
            set_edge(v160, 2, t, h);
            nx = span - v140[0];
            least = ny <= nx ? ny : nx;
            t = least * inv;
            set_edge(v160, 1, t, 0.5f);
            least = v140[1] <= nx ? v140[1] : nx;
            t = least * inv;
            set_edge(v160, 0, t, 0.5f);
            vec_scale_to_length(v170, dir, D_L00_001B0B8C);
            s = v160;
            for (i9 = 0; i9 < 4; i9++) {
                vec_scale_to_length(v150, v150, *s);
                FastVecCross(v180, dir, v150);
                vec_scale_to_length(v180, v180, D_L00_001B0B90);
                FastVecAdd(v190, g_camera_l00_position, v170);
                FastVecSub(v1A0, v190, (f32 *)(moby + 0x10));
                FastVecAdd(&quad.corner[0], v190, v180);
                FastVecSub(&quad.corner[1], v190, v180);
                FastVecAdd(v190, (f32 *)(moby + 0x10), v150);
                FastVecAdd(v190, v1A0, v190);
                FastVecScale(v180, v180, k);
                FastVecAdd(&quad.corner[2], v190, v180);
                FastVecSub(&quad.corner[3], v190, v180);
                draw_world_quad(&quad, 0, 0);
                if (i9 < 3) {
                    math_apply_axis_rotation_to_quat(v150, v150, dir, 1.5707965f);
                }
                s++;
            }
        }
    }

    if (vars->t34 != 0) {
        k = IntToFloat(vars->t34) * vars->k3C;
        gfx_init_quad_packet_state(&quad, 0xB, 4, 0x80);
        color = pack_alpha(FloatToInt(k * 255.0f)) | 0x808080;
        quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = color;
        quad.uv[0][0] = 0.0f;
        quad.uv[0][1] = 0.0f;
        quad.uv[1][0] = 0.0f;
        quad.uv[1][1] = 1.0f;
        quad.uv[2][0] = 1.0f;
        quad.uv[2][1] = 0.0f;
        quad.uv[3][0] = 1.0f;
        quad.uv[3][1] = 1.0f;
        FastVecSub(v140, (f32 *)(moby + 0x10), g_camera_l00_position);
        vec_scale_to_length(v150, v140, 0.1f);
        FastVecAdd(v160, g_camera_l00_position, v150);
        FastVecCross(v170, v140, basis[4]);
        vec_scale_to_length(v170, v170, D_L00_001B0B70);
        FastVecCross(v180, v170, v140);
        vec_scale_to_length(v180, v180, D_L00_001B0B70);
        FastVecAdd(v190, v160, v180);
        FastVecAdd(&quad.corner[0], v190, v170);
        FastVecSub(&quad.corner[1], v190, v170);
        FastVecSub(v190, v160, v180);
        FastVecAdd(&quad.corner[2], v190, v170);
        FastVecSub(&quad.corner[3], v190, v170);
        draw_world_quad(&quad, 0, 0);
    }

    if (vars->t40 != 0 && vars->t40 <= D_L00_001B0B74) {
        f32 sz;
        k = IntToFloat(vars->t40) * vars->k44;
        sz = D_L00_001B0B80 + (D_L00_001B0B7C - D_L00_001B0B80) * k;
        FastVecSub(v140, (f32 *)(moby + 0x10), g_camera_l00_position);
        vec_scale_to_length(v140, v140, 0.3f);
        FastVecAdd(v150, g_camera_l00_position, v140);
        gfx_init_quad_packet_state(&quad, D_L00_001B0B84, 1, 0x80);
        quad.d88 = (0x8000LL << 24) | 0x4A;
        color = pack_alpha(FloatToInt(k * 255.0f)) | 0x808080;
        quad.rgba[0] = quad.rgba[1] = quad.rgba[2] = quad.rgba[3] = color;
        quad.uv[0][0] = 0.0f;
        quad.uv[0][1] = 0.0f;
        quad.uv[1][0] = 0.0f;
        quad.uv[1][1] = 1.0f;
        quad.uv[2][0] = 1.0f;
        quad.uv[2][1] = 0.0f;
        quad.uv[3][0] = 1.0f;
        quad.uv[3][1] = 1.0f;
        qcopy(v160, basis[4]);
        FastVecCross(v170, v140, v160);
        vec_scale_to_length(v170, v170, sz);
        FastVecCross(v180, v170, v140);
        vec_scale_to_length(v180, v180, sz);
        FastVecAdd(v190, v150, v180);
        FastVecAdd(&quad.corner[0], v190, v170);
        FastVecSub(&quad.corner[1], v190, v170);
        FastVecSub(v190, v150, v180);
        FastVecAdd(&quad.corner[2], v190, v170);
        FastVecSub(&quad.corner[3], v190, v170);
        VU1_addGSregister(0x47, 0x31001);
        draw_world_quad(&quad, 0, 0);
        VU1_addGSregister(0x47, 0x33001);
        qzero_nc(v1A0);
        for (i10 = 0; i10 < 4; i10++) {
            FastVecAdd(v1A0, v1A0, &quad.corner[i10]);
        }
        FastVecScale(v1A0, v1A0, 0.25f);
        for (i11 = 0; i11 < 4; i11++) {
            FastVecSub(v1B0, &quad.corner[i11], v1A0);
            FastVecScale(v1B0, v1B0, 0.8f);
            FastVecAdd(v1B0, v1A0, v1B0);
            gfx_world_to_screen_unit(&quad.corner[i11], &quad.uv[i11][0], &quad.uv[i11][1]);
            if (quad.uv[i11][0] > 0.9f) {
                quad.uv[i11][0] = 0.9f;
            } else if (quad.uv[i11][0] < 0.0f) {
                quad.uv[i11][0] = 0.0f;
            }
            if (quad.uv[i11][1] > 0.9f) {
                quad.uv[i11][1] = 0.9f;
            } else if (quad.uv[i11][1] < 0.0f) {
                quad.uv[i11][1] = 0.0f;
            }
        }
        quad.d78 = GetEffectTextureDescriptor(-7);
        quad.d80 = (0xFF90LL << 32) | 0x260;
        quad.d88 = (0x8000LL << 24) | 0x54;
        quad.d70 = 0;
        draw_world_quad(&quad, 0, 0);
    }
}
