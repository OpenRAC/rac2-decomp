#include "common.h"
extern float D_L01_001B2F48 __attribute__((sda));
extern float func_002A89A8(void *, int, float);
extern void *func_00312D58(void *, float);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002C19D8(void *, void *, int, float, float);
extern void func_002BFB38(void *, void *, int, int);
/* Makes a water splash at the object: a few big ripples and many small droplets that fly up. */
void func_L01_003A6028(char *object)
{
    float center[4], velocity[4], position[4];
    float angle, radius;
    int i, j, type, lifetime;
    int scale = 2;

    qcopy(center, (object + 0x10));
    center[2] = D_L01_001B2F48 = ProbeGroundHeightBelow(object + 0x10, 0, 0.5f);
    SpawnScaledEffectMoby(center, 4.5f);
    for (i = 4; i >= 0; --i) {
        velocity[0] = *(float *)(object + 0x10) + scale * RandomFloatRange(-0.3f, 0.3f);
        velocity[1] = *(float *)(object + 0x14) + scale * RandomFloatRange(-0.3f, 0.3f);
        velocity[2] = D_L01_001B2F48;
        SpawnDriftingParticle_002C19D8(velocity, &D_L01_001B2F48, -1, scale * RandomFloatRange(0.3f, 0.6f), 5250.0f);
    }
    for (j = 39; j >= 0; --j) {
        angle = RandomAngle();
        radius = scale * RandomFloatRange(0.0f, 0.0500000045f);
        velocity[0] = FastSinOrCosA(angle) * radius;
        velocity[1] = FastSinOrCosB(angle) * radius;
        velocity[2] = scale * RandomFloatRange(0.033333335f, 0.083333336f);
        position[0] = *(float *)(object + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(object + 0x14) + velocity[0] * 8.0f;
        position[2] = D_L01_001B2F48 - RandomFloatRange(0.0f, 0.2f);
        type = RandomIntBelow(2);
        lifetime = RandomIntRange(90, 120);
        SpawnSparkParticle_002BFB38(position, velocity, type, scale * lifetime);
    }
}
