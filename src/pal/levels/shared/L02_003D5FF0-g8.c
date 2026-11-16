#include "names.h"
/* func_PAL_L02_003D5FF0, the PAL copy of func_L02_003D1FA0: the same C, where 1/60 becomes 0.02, the lifetime 60 becomes 50
   and the last particle argument is scaled by 1.44 (6/5 squared). */
#include "common.h"
extern float g_dust_pair_scale_min __attribute__((sda)), g_dust_pair_scale_max __attribute__((sda));
extern float g_dust_pair_speed_min __attribute__((sda)), g_dust_pair_speed_max __attribute__((sda)), g_dust_pair_rise_min __attribute__((sda)), g_dust_pair_rise_max __attribute__((sda)), g_dust_pair_ground_param __attribute__((sda));
extern float g_camera_l02_position[];
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern int math_random_int_below(int), FloatToInt(float);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(float, void *, void *, void *);
extern char *part_spawn_ground_effect(float, void *, int, float, int, int, int, void *, int, float);
/* Emits two particles per iteration, with opposite signed orientation. */
void func_PAL_L02_003D5FF0(float *pos, int count) {
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
        scale = math_random_float_range(g_dust_pair_scale_min, g_dust_pair_scale_max);
        sign = math_random_int_below(2); if (!sign) sign--;
        math_apply_axis_rotation_to_quat(math_random_float_range(-1.047197699546814f, 1.047197699546814f), vel, dir, axis);
        vec_scale_to_length(vel, vel, math_random_float_range(g_dust_pair_speed_min, g_dust_pair_speed_max) * 0.020000001f);
        vel[2] = math_random_float_range(g_dust_pair_rise_min, g_dust_pair_rise_max) * 0.020000001f;
        FastVecAdd(out, pos, offset);
        pos[0] += math_random_signed_float_range(0.0f, 0.15f);
        pos[1] += math_random_signed_float_range(0.0f, 0.15f);
        pos[2] += math_random_signed_float_range(0.0f, 0.15f);
        particle = part_spawn_ground_effect(scale * 0.1f, out, 50, scale, 0x7F007F40, 0, sign, vel, 0, g_dust_pair_ground_param * 1.44f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(scale * 0.07f, out, 50, scale * 0.7f, 0x047F047F, 1, -sign, vel, 0, g_dust_pair_ground_param * 1.44f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}
