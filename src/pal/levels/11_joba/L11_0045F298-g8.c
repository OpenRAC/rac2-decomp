#include "common.h"

/* func_PAL_L11_0045F298, the PAL copy of func_L11_00459640: the same C at 50 Hz, where 1.0f / 60.0f
   becomes 0.020000001f, the lifetimes 60, 40, (10, 20) and (25, 60) become 50, 33, (8, 17) and
   (21, 50), and D_L11_001B1FF0 gains a factor of 1.44f (1.2 squared). */

extern void FastVecSub(void *, void *, void *);
extern float math_random_angle(void);
extern int math_random_int_range(int a0, int a1);
extern float math_random_float_range(float a, float b);
extern float math_random_signed_float_range(float, float);
extern void vec_scale_to_length(char *a0, void *a1, float f12);
extern void FastVecScale(char *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern int func_001163B0(void);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *part_spawn_ground_effect(void *, int, int, float, float, float, int, int, void *, int);
extern void *part_spawn_spinning_particle(void *, void *, int, int, float, float, int, int, int, int, int);
extern char g_hero_l11_position[];
extern float g_smoke_spray_speed_min __attribute__((sda));
extern float g_smoke_spray_speed_max __attribute__((sda));
extern float g_smoke_spray_rise_min __attribute__((sda));
extern float g_smoke_spray_rise_max __attribute__((sda));
extern float g_ground_effect_param __attribute__((sda));
extern float g_effect_size_min __attribute__((sda));
extern float g_effect_size_max __attribute__((sda));
extern int g_ground_effect_kind_a __attribute__((sda));
extern int g_ground_effect_kind_b __attribute__((sda));

/* Sprays smoke puffs and spinning sparks from a point away from the player; mode 1 is the smaller burst (PAL: 50 Hz timings). */
void part_spray_smoke_and_sparks_pal(float *origin, int count, int mode)
{
    float vel[4], pos[4], axis[4], up[4], to_hero[4], step[4], out[4];
    int i, j, sign;
    char *effect;
    float size, speed, angle, azimuth;

    FastVecSub(axis, g_hero_l11_position, origin);
    axis[2] = 0;
    up[0] = 0;
    up[1] = 0;
    up[2] = 1;
    up[3] = 1;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(g_effect_size_min, g_effect_size_max);
        sign = math_random_int_below(2);
        if (!sign)
            --sign;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(vel, axis, up, angle);
        speed = math_random_float_range(g_smoke_spray_speed_min, g_smoke_spray_speed_max) * 0.020000001f;
        vec_scale_to_length((char *)vel, vel, speed);
        vel[2] = math_random_float_range(g_smoke_spray_rise_min, g_smoke_spray_rise_max) * 0.020000001f;
        qcopy(pos, origin);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        if (!mode) {
            if (!(func_001163B0() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = part_spawn_ground_effect(pos, 50, g_ground_effect_kind_a, size * 0.35f, size, g_ground_effect_param * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 50, g_ground_effect_kind_b, size * 0.245f, size * 0.7f, g_ground_effect_param * 1.44f, 1, -sign, vel, 0);
            } else {
                FastVecSub(to_hero, g_hero_l11_position, pos);
                vec_scale_to_length((char *)to_hero, to_hero, speed);
                FastVecAdd(vel, vel, to_hero);
                effect = part_spawn_ground_effect(pos, 33, g_ground_effect_kind_a, size * 2.05f, size, g_ground_effect_param * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 33, g_ground_effect_kind_b, size * 1.4350000619888306f, size * 0.7f, g_ground_effect_param * 1.44f, 1, -sign, vel, 0);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale((char *)vel, vel, 1.5f);
                effect = part_spawn_ground_effect(pos, 50, g_ground_effect_kind_a, size * 0.3f, size, g_ground_effect_param * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 50, g_ground_effect_kind_b, size * (0.3f * 0.7f), size * 0.7f, g_ground_effect_param * 1.44f, 1, -sign, vel, 0);
            } else {
                FastVecSub(to_hero, g_hero_l11_position, pos);
                vec_scale_to_length((char *)to_hero, to_hero, speed);
                FastVecAdd(vel, vel, to_hero);
                effect = part_spawn_ground_effect(pos, 33, g_ground_effect_kind_a, size * 0.25f, size, g_ground_effect_param * 1.44f, 0, sign, vel, 0);
                if (effect)
                    effect[9] = FloatToInt(4.0f) + 112;
                effect = part_spawn_ground_effect(pos, 33, g_ground_effect_kind_b, size * 0.175f, size * 0.7f, g_ground_effect_param * 1.44f, 1, -sign, vel, 0);
            }
        }
        if (effect)
            effect[9] = FloatToInt(4.0f) + 112;
    }
    for (j = 1; j >= 0; j--) {
        angle = math_random_float_range(-0.9599312f, -1.3962636f);
        azimuth = math_random_angle();
        vec_build_spherical_offset(to_hero, math_random_float_range(0, 0.5f) * 0.020000001f, azimuth, angle);
        FastVecSub(step, g_hero_l11_position, origin);
        vec_scale_to_length((char *)step, step, 0.15f);
        FastVecAdd(origin, origin, step);
        size = math_random_float_range(30000, 60000);
        out[0] = origin[0] + math_random_signed_float_range(0, 0.15f);
        out[1] = origin[1] + math_random_signed_float_range(0, 0.15f);
        out[2] = origin[2] + math_random_signed_float_range(0, 0.15f);
        if (mode)
            part_spawn_spinning_particle(out, to_hero, 0x4F93E5FF, 0x102434EE, size, 0.5f, math_random_int_range(8, 17), 1, -1, -1, 0);
        else
            part_spawn_spinning_particle(out, to_hero, 0x4F93E5FF, 0x102434EE, size, 0.5f, math_random_int_range(21, 50), 1, -1, -1, 0);
    }
}
