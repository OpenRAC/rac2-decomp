#include "common.h"

/* func_PAL_L06_00407B38, the PAL copy of func_L06_00403DA8: the same C, where the two velocity
   ranges are scaled by 6/5 and the func_00283CF0 argument by 5/6 as x * 5 + 2 over 6. */
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void *part_spawn_spark_2(void *, void *, int, int);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_random_tinted_effect(char *, char *, int, float, float);
extern int FloatToInt(float);
extern float g_splash_burst_data MACRO_ADDR;
extern char g_effect_vector[] MACRO_ADDR;

void func_PAL_L06_00407B38(void *unused, void *position)
{
    float vector[4];
    float angle, radius;
    int life, kind;
    char *effect;
    int i;
    float *data = &g_splash_burst_data;
    for (i = 15; i >= 0; --i) {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.060000002f);
        vector[0] = math_fast_sin_or_cos_a(angle) * radius;
        vector[1] = math_fast_sin_or_cos_b(angle) * radius;
        vector[2] = math_random_float_range(0.060000002f, 0.13000001f);
        life = math_random_int_range(90, 120);
        kind = math_random_int_below(2);
        part_spawn_spark_2(position, vector, kind, life);
    }
    for (i = 0; i < 16; ++i) {
        vec_random_direction(vector, 1.0f, 1.0f);
        FastVecAdd(vector, vector, position);
        vector[2] = g_splash_burst_data + 0.05f;
        effect = part_spawn_random_tinted_effect((char *)vector, g_effect_vector, (int)data, math_random_float_range(0.7f, 1.0f), i == 0 ? 2.0f : -2.0f);
        if (effect != 0)
            *(short *)(effect + 10) = FloatToInt((math_random_float_range(30.0f, 60.0f) * 5.0f + 2.0f) * 0.16666667f);
    }
}
