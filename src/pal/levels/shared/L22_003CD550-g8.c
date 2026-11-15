#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F3c9b60;
typedef struct { float value[4], phase[4], rate[4]; } SparkTimers;
extern const float D_L22_001AFF08 __attribute__((sda));
extern const float D_L22_001AFF10 __attribute__((sda));
extern s32 D_L22_001AFF50 __attribute__((sda));
extern const float D_L22_001AFF28 __attribute__((sda));
extern const float D_L22_001AFF48 __attribute__((sda));
extern s32 D_L22_001AFF40 __attribute__((sda));
extern const float D_L22_001AFF30 __attribute__((sda));
extern s32 D_L22_001AFF38 __attribute__((sda));
extern float D_L22_001AFF0C[];
extern float D_L22_001AFF14[];
extern float D_L22_001AFF2C[];
extern float D_L22_001AFF4C[];
extern s32 D_L22_001AFF44[];
extern float D_L22_001AFF34[];
extern s32 D_L22_001AFF3C[];
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern void matrix_mul_vec3(void *, void *, char *);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, char *);
extern s32 math_random_int_range(s32, s32);
extern void *part_spawn_hero_relative(void *, void *, s32, float, u8, u8, s32);

/* Advance four spark timers, reroll expired ones, and randomly emit a particle. */
void func_PAL_L22_003CD898(char *obj)
{
    V4_F3c9b60 aim, spark;
    SparkTimers *timers = (SparkTimers *)(*(char **)(obj + 0x68) + 0x10);
    int i = 0;
    s32 count = 3;
    float step, t;
    float c, s;
    s32 color, id;

    do {
        step = timers->phase[i] + timers->rate[i];
        timers->phase[i] = step;
        if (step >= 1.0f) {
            timers->phase[i] = 0.0f;
            timers->rate[i] = math_random_float_range(D_L22_001AFF08, D_L22_001AFF0C[0]) * 0.020000001f;
            timers->value[i] = math_random_float_range(D_L22_001AFF10, D_L22_001AFF14[0]);
        }
        count--;
        i++;
    } while (count >= 0);
    if (math_random_int_below(D_L22_001AFF50) != 0) {
        qzero_nc(&spark);
        spark.f[2] = math_random_float_range(D_L22_001AFF28, D_L22_001AFF2C[0]) * 0.020000001f;
        matrix_mul_vec3(&spark, &spark, obj + 0xC0);
        c = math_random_angle();
        s = math_random_float_range(D_L22_001AFF48, D_L22_001AFF4C[0]);
        aim.f[0] = math_fast_sin_or_cos_a(c) * s;
        aim.f[1] = math_fast_sin_or_cos_b(c) * s;
        aim.f[2] = 0.0f;
        matrix_mul_vec3(&aim, &aim, obj + 0xC0);
        FastVecAdd(&aim, &aim, obj + 0x10);
        color = ((s32)(math_random_int_range(D_L22_001AFF40, D_L22_001AFF44[0])) * 5 + 2) / 6;
        t = math_random_float_range(D_L22_001AFF30, D_L22_001AFF34[0]);
        if (math_random_int_below(2) != 0)
            id = D_L22_001AFF38;
        else
            id = D_L22_001AFF3C[0];
        part_spawn_hero_relative(&aim, &spark, id, t, color & 0xFF, math_random_int_below(0xFF) & 0xFF, 0);
    }
}
