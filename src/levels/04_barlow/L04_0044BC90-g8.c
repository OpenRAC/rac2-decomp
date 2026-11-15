#include "common.h"
typedef int BarlowEffectQuad __attribute__((mode(TI)));
typedef union { BarlowEffectQuad q; float f[4]; } BarlowEffectVector;
extern void func_00282D30(void *, void *, float);
extern char *func_L00_0033E220(void *, void *, unsigned int, int, int, int, int, int, float, float);
extern void func_002A7750(void *, int, int);
extern void *func_002A9640(void *, int, int);
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int, int, unsigned char, void *);
extern void func_L03_002ECF08(void *, void *, void *, void *, void *, int, unsigned char);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_0029F338(void *);
extern float D_L04_001B1830[] SDATA(D_L04_001B1830);
extern float D_L04_001B1828[] SDATA(D_L04_001B1828);
extern float D_L04_001B1820[] SDATA(D_L04_001B1820);
extern int D_L04_001B1850 SDATA(D_L04_001B1850);

/* Launches a burst of effects from the object: it spawns a stream, waits, then fires the main burst and removes itself. */
void func_L04_0044BC90(unsigned char *object)
{
    BarlowEffectVector velocity, lower, upper, minOffset, maxOffset;
    char *state = *(char **)(object + 0x68);
    velocity.q = 0;
    velocity.f[0] = -21.5f;
    switch (object[0x20]) {
    case 0:
        FastVecScale(&velocity, &velocity, *(float *)(object + 0x2c));
        *(char **)(state + 4) = SpawnObjectFollowingEffect(&velocity, object, 0x40208080, -1, 1, -1, 0, -1,
                                                *(float *)(object + 0x2c) * 5250000.0f, *(float *)(object + 0x2c) * 15.0f);
        SetMobyState(object, 1, -1);
        break;
    case 1:
        if (FindOwnedEffectSlot(object, 0x4010000, 0) && !*(int *)state) SetMobyState(object, 2, -1);
        object[0xa8] = 255;
        break;
    case 2:
        ExplodeObjectIntoPieces(object, D_L04_001B1830, D_L04_001B1828, D_L04_001B1820, 65535, 0, D_L04_001B1850, 8, 65535, 255, 0);
        minOffset.q = 0;
        maxOffset.q = 0;
        lower.q = 0;
        upper.q = 0;
        upper.f[0] = lower.f[0] = -15.0f;
        minOffset.f[0] = -10.0f;
        minOffset.f[2] = minOffset.f[1] = -4.0f;
        maxOffset.f[0] = -3.0f;
        maxOffset.f[1] = 5.0f;
        maxOffset.f[2] = 4.0f;
        SpawnParticleBurst(object, &lower, &upper, &minOffset, &maxOffset, 45, 0);
        LocalOffsetToWorld(object, &velocity, -21.5f, 0.0f, 0.0f);
        SpawnExplosion(object + 0x10, 0, 25, 20, 20, 20, 45, 1,
                     *(float *)(object + 0x2c) * 5.0f, 20.0f, 1, 1, 0, 0);
        MarkMobySpawned(object);
        break;
    }
}
