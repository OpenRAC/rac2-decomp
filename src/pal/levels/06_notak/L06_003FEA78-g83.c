#include "include_asm.h"
#include "names.h"

extern void anim_start_immediate(char *, int, int);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int PlayMobySound(int, int, char *);
extern char *g_moby_l06_table __attribute__((nosda));
extern float g_oscillation_speed __attribute__((sda));

/* Makes an object bob up and down on a sine wave, with a sound at each end of the swing; it waits while its parent object is busy (PAL: 50 Hz timings). */
void oscillating_height_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    int advance;
    char *parent;
    float wave;
    if (state == 0)
        return;
    if (*(unsigned char *)(object + 0x20) == 0) {
        anim_start_immediate(object, 0, 0);
        *(int *)(object + 0x48) = 0;
        *(float *)(state + 0xc) = *(float *)(state + 4);
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(state + 8) = *(float *)(object + 0x18);
    }
    advance = 1;
    if (*(int *)state > 0) {
        parent = g_moby_l06_table + (*(int *)state << 8);
        if (parent != 0 && *(unsigned char *)(*(char **)(parent + 0x68) + 0x14) != 0)
            advance = 0;
    }
    if (FastDiffRots(*(float *)(state + 0xc), 0.0f) < g_oscillation_speed * 0.0003490659f ||
        FastDiffRots(*(float *)(state + 0xc), 3.14159297943115234375f) < g_oscillation_speed * 0.0003490659f)
        PlayMobySound(0, 0, object);
    if (advance)
        *(float *)(state + 0xc) = FastAddRotations(*(float *)(state + 0xc), g_oscillation_speed * 0.0003490659f);
    wave = math_fast_sin_or_cos_b(*(float *)(state + 0xc));
    *(float *)(object + 0x18) = (*(float *)(state + 8) - 2.0f) + (wave + wave);
}
