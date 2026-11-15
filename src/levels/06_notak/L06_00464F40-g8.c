#include "common.h"

extern int func_003A0948(int, int, char *);
extern void *func_00312D58(float *, float);
extern void func_L02_0031E9E8(float *, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern char *func_002BFB38(float *, float *, int, int);
extern float D_L06_001B37CC __attribute__((sda));

/* Makes a big burst of debris and particles flying outward when the machine crashes to the ground. */
void func_L06_00464F40(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4];
    float spawn[4];
    int n = 5;
    int i;
    char *particle;

    func_003A0948(2, 0, self);
    qcopy(pos, self + 0x10);
    D_L06_001B37CC = pos[2];
    SpawnScaledEffectMoby(pos, 11.25f);
    for (i = 0x59; i >= 0; i--) {
        RandomPlanarOffset(vel, n * 0.03333333507180214f);
        vel[2] = n * 0.01666666753590107f * RandomFloatRange(2.0f, 3.5f);
        spawn[0] = *(float *)(self + 0x10) + vel[0] * 8.0f;
        spawn[1] = *(float *)(self + 0x14) + vel[1] * 8.0f;
        spawn[2] = D_L06_001B37CC - RandomFloatRange(0.0f, 0.2f);
        particle = SpawnSparkParticle_002BFB38(spawn, vel, RandomIntBelow(2), n * RandomIntRange(0x5A, 0x78));
        if (particle != 0)
            *(float *)(particle + 0xC) = *(float *)(particle + 0xC) * RandomFloatRange(4.0f, 6.0f);
    }
}
