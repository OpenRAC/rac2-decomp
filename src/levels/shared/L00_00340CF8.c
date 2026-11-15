#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern unsigned char *D_L00_001FEAF0;

/* Spawns a puff particle that is pushed by an extra acceleration as well as its velocity. */
unsigned char *func_L00_00340CF8(Quadword *position, float *velocity, float *acceleration,
                              int flags, int lifetime, float scale) {
    unsigned char *particle = AllocParticle(0x6C);
    unsigned char *motion;
    int frame, shade;
    float *force;
    if (particle) {
        *(Quadword *)(particle + 0x10) = *position;
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = RandomIntBelow(255);
        particle[2] = *D_L00_001FEAF0;
        *(short *)(particle + 0xA) = lifetime;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        force = (float *)(particle + 0x30);
        force[0] = acceleration[0];
        force[1] = acceleration[1];
        force[2] = acceleration[2];
        frame = RandomIntRange(0, 11);
        shade = RandomIntRange(0, 15);
        motion[0xC] = frame | (shade << 4);
        motion[0xD] = RandomIntRange(1, 4) << 4;
        motion[0xE] = lifetime;
        motion[0x1E] = FloatToInt(RandomFloatRange(0.15f, 0.25f) * 128.0f);
        motion[0x1F] = FloatToInt(RandomFloatRange(0.5f, 1.0f) * 128.0f);
        motion[0x1C] = FloatToInt(RandomFloatRange(0.9f, 1.1f) * 10.666667f);
        motion[0x1D] = FloatToInt(RandomFloatRange(0.0f, 0.0125f) * 128.0f);
        motion[0xF] = FloatToInt(scale * 128.0f);
        *(unsigned int *)(particle + 4) = ((unsigned)(shade + 0x70) << 24) | 0x103080;
    }
    return particle;
}
