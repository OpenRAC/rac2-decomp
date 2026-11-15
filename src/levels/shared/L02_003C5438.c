#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_ground_effect(void *, u32, u32, f32, f32, u32, s32, void *, f32, s32);
extern char D_L02_001A8F20[] __attribute__((sda));

/* Spawn one particle and, when both secondary parameters are set, its opposite. */
void SpawnOpposedParticles(void *pos, void *primaryA, void *primaryB, void *secondaryA, void *secondaryB)
{
    TI128 posCopy;
    float scale;
    float zero = 0.0f;
    int sign;

    posCopy = *(TI128 *)pos;
    scale = math_random_float_range(2.0f, 4.0f);
    sign = math_random_int_below(2);
    if (sign == 0)
        sign--;
    part_spawn_ground_effect(&posCopy, (u32)primaryA, (u32)primaryB, scale * 0.3f, scale, 0, sign, D_L02_001A8F20, zero, 0);
    if (secondaryA != 0 && secondaryB != 0)
        part_spawn_ground_effect(&posCopy, (u32)secondaryA, (u32)secondaryB, scale * 0.04f, scale * 0.4f, 1, -sign, D_L02_001A8F20, zero, 0);
}
