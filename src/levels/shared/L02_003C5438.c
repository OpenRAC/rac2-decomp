#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002C2210(void *, u32, u32, f32, f32, u32, s32, void *, f32, s32);
extern char D_L02_001A8F20[] __attribute__((sda));

/* Spawn one particle and, when both secondary parameters are set, its opposite. */
void func_L02_003C5438(void *pos, void *primaryA, void *primaryB, void *secondaryA, void *secondaryB)
{
    TI128 posCopy;
    float scale;
    float zero = 0.0f;
    int sign;

    posCopy = *(TI128 *)pos;
    scale = RandomFloatRange(2.0f, 4.0f);
    sign = RandomIntBelow(2);
    if (sign == 0)
        sign--;
    SpawnGroundEffectParticle(&posCopy, (u32)primaryA, (u32)primaryB, scale * 0.3f, scale, 0, sign, D_L02_001A8F20, zero, 0);
    if (secondaryA != 0 && secondaryB != 0)
        SpawnGroundEffectParticle(&posCopy, (u32)secondaryA, (u32)secondaryB, scale * 0.04f, scale * 0.4f, 1, -sign, D_L02_001A8F20, zero, 0);
}
