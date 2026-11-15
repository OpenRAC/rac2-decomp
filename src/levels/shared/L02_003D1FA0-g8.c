#include "common.h"
extern float D_L02_001B0164 __attribute__((sda)), D_L02_001B0168 __attribute__((sda));
extern float D_L02_001B0150 __attribute__((sda)), D_L02_001B0154 __attribute__((sda)), D_L02_001B0158 __attribute__((sda)), D_L02_001B015C __attribute__((sda)), D_L02_001B0160 __attribute__((sda));
extern float g_camera_l02_position[];
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern int math_random_int_below(int), FloatToInt(float);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(float, void *, void *, void *);
extern char *part_spawn_ground_effect(float, void *, int, float, int, int, int, void *, int, float);
/* Emits two particles per iteration, with opposite signed orientation. */
void part_spawn_dust_pairs(float *pos, int count) {
    float vel[4] __attribute__((aligned(16)));
    float out[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale;
    int i, sign;
    char *particle;
    FastVecSub(dir, g_camera_l02_position, pos);
    vec_scale_to_length(offset, dir, 0.3f);
    dir[2] = 0.0f;
    axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    for (i=0;i<count;i++) {
        scale = math_random_float_range(D_L02_001B0164, D_L02_001B0168);
        sign = math_random_int_below(2); if (!sign) sign--;
        math_apply_axis_rotation_to_quat(math_random_float_range(-1.047197699546814f, 1.047197699546814f), vel, dir, axis);
        vec_scale_to_length(vel, vel, math_random_float_range(D_L02_001B0150, D_L02_001B0154) * (1.0f / 60.0f));
        vel[2] = math_random_float_range(D_L02_001B0158, D_L02_001B015C) * (1.0f / 60.0f);
        FastVecAdd(out, pos, offset);
        pos[0] += math_random_signed_float_range(0.0f, 0.15f);
        pos[1] += math_random_signed_float_range(0.0f, 0.15f);
        pos[2] += math_random_signed_float_range(0.0f, 0.15f);
        particle = part_spawn_ground_effect(scale * 0.1f, out, 60, scale, 0x7F007F40, 0, sign, vel, 0, D_L02_001B0160);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(scale * 0.07f, out, 60, scale * 0.7f, 0x047F047F, 1, -sign, vel, 0, D_L02_001B0160);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
