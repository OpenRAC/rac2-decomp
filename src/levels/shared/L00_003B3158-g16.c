#include "include_asm.h"
#include "names.h"

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

/* Spawns a few sparkles near the camera. */
void part_spawn_camera_sparkles(void)
{
    float point[4], velocity[4], scatter[4];
    int i = 0;
    unsigned char kind, random;
    matrix_mul_vec3(point, g_sparkle_camera_offset, g_camera_l00_position + 0x230);
    FastVecAdd(point, point, (float *)g_camera_l00_position);
    kind = math_random_int_range(g_sparkle_kind_min, g_sparkle_kind_ranges[0]);
    random = math_random_int_below(255);
    part_spawn_hero_relative(point, g_default_vector, g_sparkle_color_a, kind, random, 0, g_sparkle_hero_param_a);
    vec_random_direction(velocity, g_explosion_l00_speed_min * (1.0f / 60.0f), g_explosion_l00_speed_max * (1.0f / 60.0f));
    while (i < g_sparkle_count) {
        i++;
        vec_random_direction(scatter, 0.0f, 0.25f);
        FastVecAdd(scatter, scatter, point);
        kind = math_random_int_range(g_sparkle_kind_ranges[1], g_sparkle_kind_ranges[2]);
        random = math_random_int_below(255);
        part_spawn_hero_relative(scatter, velocity, g_sparkle_color_b, kind, random, 0, g_sparkle_hero_param_b);
    }
}

extern float g_two_color_sparkle_speed_min __attribute__((sda));
extern float g_two_color_sparkle_speed_max;
extern float g_two_color_sparkle_param_a __attribute__((sda));
extern float g_two_color_sparkle_param_b;
extern int g_two_color_sparkle_colors[2][2] __attribute__((sda));
extern int g_two_color_sparkle_kind_min __attribute__((sda));
extern int g_two_color_sparkle_kind_ranges[] __attribute__((sda));

/* Spawns two small sparkles at a position, colored by the object's state. */
void part_spawn_two_colored_sparkles(char *object, void *position)
{
    float velocity[4];
    void *first = *(void **)(object + 0x68);
    unsigned char kind = math_random_int_range(g_two_color_sparkle_kind_min, g_two_color_sparkle_kind_ranges[0]);
    int *color = &g_two_color_sparkle_colors[(unsigned char)object[0xbc]][0];
    int *color2;
    unsigned char random = math_random_int_below(255);
    part_spawn_hero_relative(position, first, *color, kind, random, 0, g_two_color_sparkle_param_a);
    vec_random_direction(velocity, g_two_color_sparkle_speed_min * (1.0f / 60.0f), g_two_color_sparkle_speed_max * (1.0f / 60.0f));
    kind = math_random_int_range(g_two_color_sparkle_kind_ranges[1], g_two_color_sparkle_kind_ranges[2]);
    color2 = (int *)((char *)g_two_color_sparkle_colors + (((unsigned char)object[0xbc] << 3) | 4));
    random = math_random_int_below(255);
    part_spawn_hero_relative(position, velocity, *color2, kind, random, 0, g_two_color_sparkle_param_b);
}
