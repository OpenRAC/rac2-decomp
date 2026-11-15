#include "include_asm.h"
#include "common.h"

extern char *part_alloc(int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern int math_random_int_below(int);
extern unsigned char *D_001F26C4;
extern void part_update_fading_drift_alt(char *a0);

/* Creates a fading, drifting particle that moves along a set direction with gravity. Returns the new particle, or null if none are free. */
char *part_spawn_fading_drift(void *position, float *velocity, int lifetime, int color, int spinSpeed, int startAlpha, int endAlpha, int kind, float startSize, float endSize, float gravity)
{
    char *particle = part_alloc(0x61);
    char *motion;

    if (particle != 0) {
        qcopy(particle + 0x10, position);
        *(int *)(particle + 4) = (startAlpha << 24) | color;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[1] = 0;
        *(float *)(particle + 0xC) = startSize;
        particle[3] = 0x48;
        particle[8] = math_random_int_below(0xFF);
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
        *(void **)(motion + 0x1C) = (void *)part_update_fading_drift_alt;
    }
    return particle;
}
