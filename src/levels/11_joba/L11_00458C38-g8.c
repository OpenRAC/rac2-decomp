#include "common.h"

extern float D_L11_001B1FC8 SDATA(D_L11_001B1FC8);
extern float D_L11_001B1FCC SDATA(D_L11_001B1FCC);
extern int D_L11_001B1FBC SDATA(D_L11_001B1FBC);
extern int D_L11_001B1FC0 SDATA(D_L11_001B1FC0);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_L11_00458DF0(void *, int, float, int, float, int, int);

/* Draws two puffs of smoke at the object, a bigger one and a smaller one with random sizes. */
void func_L11_00458C38(unsigned char *object)
{
    float size, random_size;
    random_size = RandomFloatRange(0.0f, D_L11_001B1FC8 * D_L11_001B1FCC);
    size = D_L11_001B1FC8;
    size += random_size;
    DrawBillboardSpriteAtPosition(object + 0x10, D_L11_001B1FBC, size, RandomIntRange(80, 96),
                      RandomAngle(), 49, 2);
    size *= 1.2f;
    DrawBillboardSpriteAtPosition(object + 0x10, D_L11_001B1FC0, size, RandomIntRange(8, 22),
                      RandomAngle(), 11, 2);
}
