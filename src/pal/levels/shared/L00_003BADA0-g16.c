#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_003BADA0, the PAL copy of func_L00_003B72B0: the same C, where 1.0f / 60.0f becomes 0.020000001f and both
   func_002A7820 results are scaled to 50 Hz. The loop's result has a local of its own, so it stays in one block. */

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(float *, float *, float *);
extern void matrix_mul_vec3(float *, float *, void *);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern float g_explosion_l00_speed_min __attribute__((sda));
extern float g_explosion_l00_speed_max;
extern float g_sparkle_hero_param_a __attribute__((sda));
extern float g_sparkle_hero_param_b;
extern int g_sparkle_color_a __attribute__((sda));
extern int g_sparkle_color_b;
extern int g_sparkle_kind_min __attribute__((sda));
extern int g_sparkle_kind_ranges[] __attribute__((sda));
extern int g_sparkle_count __attribute__((sda));
extern float g_sparkle_camera_offset[4] __attribute__((sda));
extern char g_camera_l00_position[];
extern float g_default_vector[4];

void func_PAL_L00_003BADA0(void)
{
    float point[4], velocity[4], scatter[4];
    int i = 0;
    unsigned char kind, kind2, random;
    matrix_mul_vec3(point, g_sparkle_camera_offset, g_camera_l00_position + 0x230);
    FastVecAdd(point, point, (float *)g_camera_l00_position);
    kind = ((int)math_random_int_range(g_sparkle_kind_min, g_sparkle_kind_ranges[0]) * 5 + 2) / 6;
    random = math_random_int_below(255);
    part_spawn_hero_relative(point, g_default_vector, g_sparkle_color_a, kind, random, 0, g_sparkle_hero_param_a);
    vec_random_direction(velocity, g_explosion_l00_speed_min * 0.020000001f, g_explosion_l00_speed_max * 0.020000001f);
    while (i < g_sparkle_count) {
        i++;
        vec_random_direction(scatter, 0.0f, 0.25f);
        FastVecAdd(scatter, scatter, point);
        kind2 = ((int)math_random_int_range(g_sparkle_kind_ranges[1], g_sparkle_kind_ranges[2]) * 5 + 2) / 6;
        random = math_random_int_below(255);
        part_spawn_hero_relative(scatter, velocity, g_sparkle_color_b, kind2, random, 0, g_sparkle_hero_param_b);
    }
}
