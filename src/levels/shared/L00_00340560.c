#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern unsigned char *D_L00_001FEAE8;

/* Spawns a puff particle with a grey shade, drifting along the given velocity. */
unsigned char *func_L00_00340560(Quadword *position, float *velocity, int flags, int lifetime, float scale) {
    unsigned char *particle = AllocParticle(0x6A);
    unsigned char *motion;
    int shade;
    if (particle) {
        *(Quadword *)(particle + 0x10) = *position;
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = RandomIntBelow(255);
        particle[2] = *D_L00_001FEAE8;
        *(short *)(particle + 0xA) = lifetime;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        shade = RandomIntRange(15, 31);
        *(int *)(motion + 0xC) = (shade << 16) + (shade << 8) + shade;
        motion[0x10] = RandomIntRange(1, 4);
        motion[0x11] = lifetime;
        motion[0x13] = 0;
        motion[0x12] = RandomIntRange(95, 127);
        *(float *)(motion + 0x14) = RandomFloatRange(0.0625f, 0.125f) * 210000.0f;
        *(float *)(motion + 0x18) = RandomFloatRange(0.5f, 0.6f) * 210000.0f;
        *(float *)(motion + 0x1C) = scale;
        *(int *)(particle + 4) = ((unsigned)motion[0x12] << 24) | 0x103080;
    }
    return particle;
}
