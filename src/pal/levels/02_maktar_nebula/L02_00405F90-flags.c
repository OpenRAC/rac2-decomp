#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef int s32;
extern char g_sound_state[];
extern int PlayMobySound(int, int, char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);

/* Makes the object wobble and sway a little each frame, and keeps its looping sound playing
   (PAL: 50 Hz wobble steps). */
void sway_apply_wobble_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *sound_record = g_sound_state + *(s32 *)(vars + 0x16C) * 0x70;
    float phase;

    if (*(char **)(sound_record + 0x88) != moby || *(u8 *)(sound_record + 0x74) == 0)
        *(s32 *)(vars + 0x16C) = PlayMobySound(1, 4, moby);
    *(TI128 *)(moby + 0x10) = *(TI128 *)(vars + 0x120);
    *(TI128 *)(moby + 0xF0) = *(TI128 *)(vars + 0x130);
    phase = FastAddRotations(*(float *)(vars + 0x148), 0.010471977f);
    *(float *)(vars + 0x148) = phase;
    *(float *)(moby + 0xF0) += math_fast_sin_or_cos_b(phase) * 0.05f;
    phase = FastAddRotations(*(float *)(vars + 0x144), 0.017453294f);
    *(float *)(vars + 0x144) = phase;
    *(float *)(moby + 0xF4) += math_fast_sin_or_cos_b(phase) * 0.05f;
    phase = FastAddRotations(*(float *)(vars + 0x140), 0.024434613f);
    *(float *)(vars + 0x140) = phase;
    *(float *)(moby + 0x18) += math_fast_sin_or_cos_b(phase) * 0.25f;
}
