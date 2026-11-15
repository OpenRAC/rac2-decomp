#include "common.h"
typedef unsigned int DebrisQuad __attribute__((mode(TI)));
typedef union { DebrisQuad q; float f[4]; } DebrisVector;
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* EE integer and floating-point argument banks retain their measured order. */
extern void func_L00_003263D0(void *, void *, float, int, int, void *, float, float, unsigned int, float, int);
/* Throws a number of debris pieces outward in a ring around the object. */
void func_L04_00456860(unsigned char *moby, int count, float low, float high, float radius, float speed)
{
    DebrisVector position;
    DebrisVector velocity;
    float angle;
    position.q = 0;
    velocity.q = 0;
    if (count > 0) {
        int remaining = count;
        do {
            angle = RandomFloatRange(-3.1415927f, 3.1415927f);
            position.f[0] = radius * FastSinOrCosA(angle);
            position.f[1] = radius * FastSinOrCosB(angle);
            position.f[2] = RandomFloatRange(0.0f, 1.0f);
            vec_scale_to_length(&velocity, &position, RandomFloatRange(speed * 0.75f, speed * 1.25f));
            position.f[2] = RandomFloatRange(low, high);
            FastVecAdd(&position, moby + 0x10, &position);
            SpawnTintedEffects(moby, &position, 0.0f, 1, 1, &velocity, 0.0f, 1.0f, 0x80402000, 3.5f, 0);
        } while (--remaining);
    }
}
