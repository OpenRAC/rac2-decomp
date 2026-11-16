#include "names.h"
/* func_PAL_L11_0044C6C0, the PAL copy of func_L11_00446C78: the same C, where expr 0.016666668f becomes 0.020000001f; wrap func_002A7820(D_L11_001B1918[0], D_L11_001B1918[1]) (((. */
#include "common.h"
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern float g_l11_laser_speed_range[] __attribute__((sda));
extern float g_arena_spawn_delay_range[] __attribute__((sda));
extern s32 g_robot_laser_particle_count __attribute__((sda));
extern float g_robot_laser_param_table[] __attribute__((sda));
extern float g_robot_laser_scale_min __attribute__((sda));
extern s32 g_robot_laser_kind_a __attribute__((sda));
extern s32 g_robot_laser_kind_b[] __attribute__((sda));
extern s32 g_robot_laser_color_range[] __attribute__((sda));
extern float g_robot_laser_radius_min __attribute__((sda));
extern float g_robot_laser_radius_max[] __attribute__((sda));
extern float g_robot_laser_offset[4] __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_angle(void);
extern s32 math_random_int_range(s32, s32);
extern void *part_spawn_hero_relative(void *, void *, s32, float, s32, s32, s32);

/* (PAL copy of part_emit_robot_laser.) */
/* Advances four animation phases and emits particles around the referenced object.
   The bounds share their measured parameter block; offset reads retain the
   absolute form while the separate scalar scale bound uses small data.
   func_002C3150 keeps the EE integer and FP argument banks in order. */
void part_emit_robot_laser_pal(char *object)
{
    float position[4], velocity[4];
    char *state = *(char **)(object + 0x68);
    float *p = (float *)(state + 0xB0);
    int i, j;
    float angle, radius, scale;
    int color, kind;
    u8 life;
    u8 shade;

    for (j = 3; j >= 0; j--, p++) {
        p[-4] += p[0];
        if (p[-4] >= 1.0f) {
            p[-4] = 0;
            p[0] = math_random_float_range(g_l11_laser_speed_range[0], g_l11_laser_speed_range[1]) * (0.020000001f);
            p[-8] = math_random_float_range(g_arena_spawn_delay_range[0], g_arena_spawn_delay_range[1]);
        }
    }
    for (i = 0; i < g_robot_laser_particle_count; i++) {
        qzero_nc(velocity);
        velocity[2] = math_random_float_range(g_robot_laser_param_table[0], g_robot_laser_param_table[1]) * (0.020000001f);
        matrix_mul_vec3(velocity, velocity, g_moby_l11_table[0] + (*(int *)(state + 0x1D0) << 8) + 0xC0);
        angle = math_random_angle();
        radius = math_random_float_range(g_robot_laser_radius_min, g_robot_laser_radius_max[0]);
        position[0] = math_fast_sin_or_cos_a(angle) * radius;
        position[1] = math_fast_sin_or_cos_b(angle) * radius;
        position[2] = 0;
        matrix_mul_vec3(position, position, g_moby_l11_table[0] + (*(int *)(state + 0x1D0) << 8) + 0xC0);
        FastVecAdd(position, position, g_moby_l11_table[0] + (*(int *)(state + 0x1D0) << 8) + 0x10);
        FastVecAdd(position, position, g_robot_laser_offset);
        color = (((int)(math_random_int_range(g_robot_laser_color_range[0], g_robot_laser_color_range[1])) * 5 + 2) / 6);
        scale = math_random_float_range(g_robot_laser_scale_min, g_robot_laser_param_table[3]);
        kind = math_random_int_below(2) ? g_robot_laser_kind_a : g_robot_laser_kind_b[0];

        life = color;
        shade = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, kind, scale, life, shade, 0);
    }
}
