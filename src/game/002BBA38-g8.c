#include "include_asm.h"
#include "names.h"

extern int math_fast_float_d(void *);
extern void part_kill(void *);
extern float FastAddRotations(float, float);
extern int FloatToInt(float);
extern int g_particle_fade_lifetime __attribute__((sda));

/* Fades a particle in at the start and out at the end of its life and tints it. Removes it when the time is up. */
void part_update_fade_in_out(char *particle)
{
    char *motion = particle + 32;
    int alpha;
    unsigned int alphaShifted;
    int tint;
    if (math_fast_float_d(motion)) {
        part_kill(particle);
    } else {
        *(float *)(motion + 12) = FastAddRotations(*(float *)(motion + 12), *(float *)(motion + 8));
        particle[8] = FloatToInt(*(float *)(motion + 12) * 40.7436637878418f) - 128;
        if (*(int *)(particle + 32) > g_particle_fade_lifetime * 3 / 4)
            alpha = *(int *)(motion + 16) * (g_particle_fade_lifetime - *(int *)(particle + 32)) / (g_particle_fade_lifetime / 4);
        else if (*(int *)(particle + 32) < g_particle_fade_lifetime / 4)
            alpha = *(int *)(motion + 16) * *(int *)(particle + 32) / (g_particle_fade_lifetime / 4);
        else
            alpha = *(int *)(motion + 16);
        alphaShifted = (unsigned int)alpha << 24;
        switch ((unsigned char)particle[3]) {
        case 72:
            tint = alphaShifted + 0x004f4f4f;
            break;
        default:
            tint = alphaShifted + 0x007f7f7f;
            break;
        }
        *(int *)(particle + 4) = tint;
    }
}
