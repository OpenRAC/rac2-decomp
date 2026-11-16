#include "common.h"
extern f32 g_spark_dir_speed_min __attribute__((sda));
extern f32 g_spark_first_scale __attribute__((sda));
extern s32 g_spark_first_part_id __attribute__((sda));
extern s32 g_spark_first_kind_min __attribute__((sda));
extern s32 g_spark_count __attribute__((sda));
extern f32 g_spark_dir_speed_max[] MACRO_ADDR;
extern f32 g_spark_l16_up_speed_min __attribute__((nosda));
extern f32 g_spark_l16_up_speed_max __attribute__((nosda));
extern f32 g_spark_second_scale[] MACRO_ADDR;
extern s32 g_spark_second_part_id[] MACRO_ADDR;
extern s32 g_spark_first_kind_max[] MACRO_ADDR;
extern s32 g_spark_second_kind_min[] MACRO_ADDR;
extern s32 g_spark_second_kind_max[] MACRO_ADDR;
extern void vec_random_direction(char *, f32, f32);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern char *part_spawn_hero_relative(char *, char *, u32, u32, f32, u32, u32);
extern void vec_clear_128(char *);
extern void FastVecAdd(char *, char *, char *);
extern f32 math_random_float_range(f32, f32);

/* Emits one central particle and the configured ring of falling particles. */
void EmitSnivelakFallingParticles(char *self) {
    char velocity[16];
    char position[16];
    s32 i;
    s32 kind;
    s32 alpha;
    s32 firstKind;
    char *origin = self + 16;
    vec_random_direction(velocity, g_spark_dir_speed_min * 0.01666666753590107f,
                  g_spark_dir_speed_max[0] * 0.01666666753590107f);
    firstKind = math_random_int_range(g_spark_first_kind_min, g_spark_first_kind_max[0]) & 255;
    alpha = math_random_int_below(255);
    part_spawn_hero_relative(origin, velocity, g_spark_first_part_id, firstKind, g_spark_first_scale, alpha & 255, 0);
    vec_clear_128(velocity);
    for (i = 0; i < g_spark_count; i++) {
        vec_random_direction(position, 0.0f, 0.25f);
        FastVecAdd(position, position, self + 16);
        *(f32 *)(velocity + 8) = -(math_random_float_range(g_spark_l16_up_speed_min, g_spark_l16_up_speed_max) * 0.01666666753590107f);
        kind = math_random_int_range(g_spark_second_kind_min[0], g_spark_second_kind_max[0]) & 255;
        alpha = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, g_spark_second_part_id[0], kind, g_spark_second_scale[0], alpha & 255, 0);
    }
}
