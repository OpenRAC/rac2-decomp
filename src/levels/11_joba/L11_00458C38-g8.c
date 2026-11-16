#include "common.h"

extern float g_shot_smoke_size SDATA(D_L11_001B1FC8);
extern float g_shot_smoke_random_scale SDATA(D_L11_001B1FCC);
extern int g_shot_smoke_sprite_a SDATA(D_L11_001B1FBC);
extern int g_shot_smoke_sprite_b SDATA(D_L11_001B1FC0);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void part_draw_billboard_sprite(void *, int, float, int, float, int, int);

/* Draws two puffs of smoke at the object, a bigger one and a smaller one with random sizes. */
void joba_shot_spawn_smoke(unsigned char *object)
{
    float size, random_size;
    random_size = math_random_float_range(0.0f, g_shot_smoke_size * g_shot_smoke_random_scale);
    size = g_shot_smoke_size;
    size += random_size;
    part_draw_billboard_sprite(object + 0x10, g_shot_smoke_sprite_a, size, math_random_int_range(80, 96),
                      math_random_angle(), 49, 2);
    size *= 1.2f;
    part_draw_billboard_sprite(object + 0x10, g_shot_smoke_sprite_b, size, math_random_int_range(8, 22),
                      math_random_angle(), 11, 2);
}
