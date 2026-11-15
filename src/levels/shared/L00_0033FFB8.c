#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern unsigned char *D_L00_001FEAD8;

/* Spawns a small spinning particle at a position, moving with the given velocity. */
unsigned char *func_L00_0033FFB8(Quadword *position, Quadword *velocity, int lifetime) {
    unsigned char *particle = AllocParticle(0x66);
    unsigned char *motion;
    if (particle) {
        motion = particle + 0x20;
        particle[9] = FloatToInt(2.0f) + 0x40;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = *D_L00_001FEAD8;
        *(float *)(particle + 0xC) = RandomFloatRange(0.03f, 0.175f) * 210000.0f;
        particle[8] = RandomIntBelow(255);
        *(short *)(particle + 0xA) = lifetime;
        *(Quadword *)(particle + 0x10) = *position;
        *(Quadword *)motion = *velocity;
        *(float *)(motion + 0xC) = RandomFloatRange(4.6f, 8.6f) * 0.00027777778f;
        *(float *)(motion + 0x18) = *(float *)(particle + 0xC) * 2.0f;
        *(short *)(motion + 0x16) = RandomIntRange(0, 3);
        *(short *)(motion + 0x14) = lifetime / 2;
        *(float *)(motion + 0x1C) = RandomAngle();
    }
    return particle;
}
