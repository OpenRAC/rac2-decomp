#include "common.h"
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern float D_L11_001B1590[] __attribute__((sda));
extern float D_L11_001B1598[] __attribute__((sda));
extern s32 D_L11_001B1928 __attribute__((sda));
extern float D_L11_001B1900[] __attribute__((sda));
extern float D_L11_001B1908 __attribute__((sda));
extern s32 D_L11_001B1910 __attribute__((sda));
extern s32 D_L11_001B1914[] __attribute__((sda));
extern s32 D_L11_001B1918[] __attribute__((sda));
extern float D_L11_001B1920 __attribute__((sda));
extern float D_L11_001B1924[] __attribute__((sda));
extern float D_L11_001B1930[4] __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_angle(void);
extern s32 math_random_int_range(s32, s32);
extern void *part_spawn_hero_relative(void *, void *, s32, float, s32, s32, s32);

/* Advances four animation phases and emits particles around the referenced object.
   The bounds share their measured parameter block; offset reads retain the
   absolute form while the separate scalar scale bound uses small data.
   func_002C3150 keeps the EE integer and FP argument banks in order. */
void part_emit_robot_laser(char *object)
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
            p[0] = math_random_float_range(D_L11_001B1590[0], D_L11_001B1590[1]) * (1.0f / 60.0f);
            p[-8] = math_random_float_range(D_L11_001B1598[0], D_L11_001B1598[1]);
        }
    }
    for (i = 0; i < D_L11_001B1928; i++) {
        qzero_nc(velocity);
        velocity[2] = math_random_float_range(D_L11_001B1900[0], D_L11_001B1900[1]) * (1.0f / 60.0f);
        matrix_mul_vec3(velocity, velocity, g_moby_l11_table[0] + (*(int *)(state + 0x1D0) << 8) + 0xC0);
        angle = math_random_angle();
        radius = math_random_float_range(D_L11_001B1920, D_L11_001B1924[0]);
        position[0] = math_fast_sin_or_cos_a(angle) * radius;
        position[1] = math_fast_sin_or_cos_b(angle) * radius;
        position[2] = 0;
        matrix_mul_vec3(position, position, g_moby_l11_table[0] + (*(int *)(state + 0x1D0) << 8) + 0xC0);
        FastVecAdd(position, position, g_moby_l11_table[0] + (*(int *)(state + 0x1D0) << 8) + 0x10);
        FastVecAdd(position, position, D_L11_001B1930);
        color = math_random_int_range(D_L11_001B1918[0], D_L11_001B1918[1]);
        scale = math_random_float_range(D_L11_001B1908, D_L11_001B1900[3]);
        kind = math_random_int_below(2) ? D_L11_001B1910 : D_L11_001B1914[0];

        life = color;
        shade = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, kind, scale, life, shade, 0);
    }
}
