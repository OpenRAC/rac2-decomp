#include "include_asm.h"
#include "common.h"

extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern unsigned char *D_001F26C4;
extern void func_002C7AE8(char *a0);

/* Creates a fading, drifting particle that moves along a set direction with gravity. Returns the new particle, or null if none are free. */
char *func_002C7970(void *position, float *velocity, int lifetime, int color, int spinSpeed, int startAlpha, int endAlpha, int kind, float startSize, float endSize, float gravity)
{
    char *particle = AllocParticle(0x61);
    char *motion;

    if (particle != 0) {
        qcopy(particle + 0x10, position);
        *(int *)(particle + 4) = (startAlpha << 24) | color;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[1] = 0;
        *(float *)(particle + 0xC) = startSize;
        particle[3] = 0x48;
        particle[8] = RandomIntBelow(0xFF);
        particle[2] = D_001F26C4[kind];
        *(short *)(particle + 0xA) = lifetime;
        motion = particle + 0x20;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        *(float *)(motion + 0xC) = gravity;
        motion[0x15] = spinSpeed;
        *(float *)(motion + 0x10) = (endSize - startSize) / IntToFloat(lifetime);
        motion[0x14] = (endAlpha - startAlpha) / lifetime;
        *(void **)(motion + 0x1C) = (void *)UpdateFadingDriftParticle_002C7AE8;
    }
    return particle;
}
