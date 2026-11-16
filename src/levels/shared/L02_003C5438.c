#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_ground_effect(void *, u32, u32, f32, f32, u32, s32, void *, f32, s32);
extern char g_zero_l02_vector[] __attribute__((sda));

/* Spawn one particle and, when both secondary parameters are set, its opposite. */
void SpawnOpposedParticles(void *pos, void *primary_a, void *primary_b, void *secondary_a, void *secondary_b)
{
    TI128 pos_copy;
    float scale;
    float zero = 0.0f;
    int sign;

    pos_copy = *(TI128 *)pos;
    scale = math_random_float_range(2.0f, 4.0f);
    sign = math_random_int_below(2);
    if (sign == 0)
        sign--;
    part_spawn_ground_effect(&pos_copy, (u32)primary_a, (u32)primary_b, scale * 0.3f, scale, 0, sign, g_zero_l02_vector, zero, 0);
    if (secondary_a != 0 && secondary_b != 0)
        part_spawn_ground_effect(&pos_copy, (u32)secondary_a, (u32)secondary_b, scale * 0.04f, scale * 0.4f, 1, -sign, g_zero_l02_vector, zero, 0);
}
