#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F3c9b60;
typedef struct { float value[4], phase[4], rate[4]; } SparkTimers;
extern const float g_spark_rate_min __attribute__((sda));
extern const float g_spark_value_min __attribute__((sda));
extern s32 g_spark_emit_chance __attribute__((sda));
extern const float g_spark_l22_speed_min __attribute__((sda));
extern const float g_spark_radius_min __attribute__((sda));
extern s32 g_spark_color_min __attribute__((sda));
extern const float g_spark_life_min __attribute__((sda));
extern s32 g_spark_particle_type_min __attribute__((sda));
extern float g_spark_rate_max[];
extern float g_spark_value_max[];
extern float g_spark_l22_speed_max[];
extern float g_spark_radius_max[];
extern s32 g_spark_color_max[];
extern float g_spark_life_max[];
extern s32 g_spark_particle_type_max[];
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
void spark_emit_random_pal(char *obj)
{
    V4_F3c9b60 aim, spark;
    SparkTimers *timers = (SparkTimers *)(*(char **)(obj + 0x68) + 0x10);
    int i = 0;
    s32 count = 3;
    float step, life;
    float angle, radius;
    s32 color, particle_type;

    do {
        step = timers->phase[i] + timers->rate[i];
        timers->phase[i] = step;
        if (step >= 1.0f) {
            timers->phase[i] = 0.0f;
            timers->rate[i] = math_random_float_range(g_spark_rate_min, g_spark_rate_max[0]) * 0.020000001f;
            timers->value[i] = math_random_float_range(g_spark_value_min, g_spark_value_max[0]);
        }
        count--;
        i++;
    } while (count >= 0);
    if (math_random_int_below(g_spark_emit_chance) != 0) {
        qzero_nc(&spark);
        spark.f[2] = math_random_float_range(g_spark_l22_speed_min, g_spark_l22_speed_max[0]) * 0.020000001f;
        matrix_mul_vec3(&spark, &spark, obj + 0xC0);
        angle = math_random_angle();
        radius = math_random_float_range(g_spark_radius_min, g_spark_radius_max[0]);
        aim.f[0] = math_fast_sin_or_cos_a(angle) * radius;
        aim.f[1] = math_fast_sin_or_cos_b(angle) * radius;
        aim.f[2] = 0.0f;
        matrix_mul_vec3(&aim, &aim, obj + 0xC0);
        FastVecAdd(&aim, &aim, obj + 0x10);
        color = ((s32)(math_random_int_range(g_spark_color_min, g_spark_color_max[0])) * 5 + 2) / 6;
        life = math_random_float_range(g_spark_life_min, g_spark_life_max[0]);
        if (math_random_int_below(2) != 0)
            particle_type = g_spark_particle_type_min;
        else
            particle_type = g_spark_particle_type_max[0];
        part_spawn_hero_relative(&aim, &spark, particle_type, life, color & 0xFF, math_random_int_below(0xFF) & 0xFF, 0);
    }
}
