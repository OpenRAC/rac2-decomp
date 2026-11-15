#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern unsigned char *D_L00_001FEAEC;

/* Spawns a dark puff particle that drifts along the given velocity and slowly changes size. */
unsigned char *func_L00_00340898(Quadword *position, float *velocity, int flags, int lifetime, float scale) {
    unsigned char *particle = AllocParticle(0x6B);
    unsigned char *motion;
    int shade;
    if (particle) {
        *(Quadword *)(particle + 0x10) = *position;
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = RandomIntBelow(255);
        particle[2] = *D_L00_001FEAEC;
        *(short *)(particle + 0xA) = lifetime;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        shade = RandomIntRange(15, 11);
        *(int *)(motion + 0xC) = (shade << 16) + (shade << 8) + shade;
        motion[0x10] = RandomIntRange(1, 4);
        motion[0x11] = lifetime;
        motion[0x13] = 0;
        motion[0x12] = RandomIntRange(95, 127);
        *(float *)(motion + 0x18) = RandomFloatRange(0.125f, 0.15f) * 105000.0f;
        *(float *)(motion + 0x1C) = RandomFloatRange(0.25f, 0.5f) * 210000.0f;
        motion[0x14] = FloatToInt(scale * 128.0f);
        motion[0x15] = FloatToInt(RandomFloatRange(0.9f, 1.1f) * 10.666667f);
        motion[0x16] = FloatToInt(RandomFloatRange(0.0f, 0.0125f) * 128.0f);
        motion[0x17] = 0;
        *(int *)(particle + 4) = ((unsigned)motion[0x12] << 24) | 0x103080;
    }
    return particle;
}
