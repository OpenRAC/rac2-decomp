#include "names.h"
/* func_PAL_L00_003BAFE0, the PAL copy of func_L00_003B74A8: the same C, where expr 0.016666668f becomes 0.020000001f; scale func_002A7820(D_L00_001AFB5C[1], D_L00_001AFB5C[2]); wrap func_002A7820(D_L00_001AFB58, D_L00_001AFB5C[0]) (((int. */

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(float *, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern float g_two_color_sparkle_speed_min __attribute__((sda));
extern float g_two_color_sparkle_speed_max;
extern float g_two_color_sparkle_param_a __attribute__((sda));
extern float g_two_color_sparkle_param_b;
extern int g_two_color_sparkle_colors[2][2] __attribute__((sda));
extern int g_two_color_sparkle_kind_min __attribute__((sda));
extern int g_two_color_sparkle_kind_ranges[] __attribute__((sda));

void func_PAL_L00_003BAFE0(char *object, void *position)
{
    float velocity[4];
    void *first = *(void **)(object + 0x68);
    unsigned char kind = (((int)(math_random_int_range(g_two_color_sparkle_kind_min, g_two_color_sparkle_kind_ranges[0])) * 5 + 2) / 6);
    int *color = &g_two_color_sparkle_colors[(unsigned char)object[0xbc]][0];
    int *color2;
    unsigned char random = math_random_int_below(255);
    part_spawn_hero_relative(position, first, *color, kind, random, 0, g_two_color_sparkle_param_a);
    vec_random_direction(velocity, g_two_color_sparkle_speed_min * (0.020000001f), g_two_color_sparkle_speed_max * (0.020000001f));
    kind = (((int)(math_random_int_range(g_two_color_sparkle_kind_ranges[1], g_two_color_sparkle_kind_ranges[2])) * 5 + 2) / 6);
    color2 = (int *)((char *)g_two_color_sparkle_colors + (((unsigned char)object[0xbc] << 3) | 4));
    random = math_random_int_below(255);
    part_spawn_hero_relative(position, velocity, *color2, kind, random, 0, g_two_color_sparkle_param_b);
}
