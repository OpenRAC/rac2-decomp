#include "include_asm.h"
#include "names.h"

/* func_L02_00401BF8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef int s32;

extern char D_00188660[];
extern int func_002E5CF8(int, int, char *);
extern float func_00283B98(float, float);
extern float func_00283198(float);

/* Makes the object wobble and sway a little each frame, and keeps its looping sound playing. */
void func_L02_00401BF8(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *soundRecord = gSoundState + *(s32 *)(vars + 0x16C) * 0x70;
    float phase;

    if (*(char **)(soundRecord + 0x88) != moby || *(u8 *)(soundRecord + 0x74) == 0)
        *(s32 *)(vars + 0x16C) = PlayMobySound(1, 4, moby);
    *(TI128 *)(moby + 0x10) = *(TI128 *)(vars + 0x120);
    *(TI128 *)(moby + 0xF0) = *(TI128 *)(vars + 0x130);
    phase = FastAddRotations(*(float *)(vars + 0x148), 0.008726648f);
    *(float *)(vars + 0x148) = phase;
    *(float *)(moby + 0xF0) += FastSinOrCosB(phase) * 0.05f;
    phase = FastAddRotations(*(float *)(vars + 0x144), 0.0145444125f);
    *(float *)(vars + 0x144) = phase;
    *(float *)(moby + 0xF4) += FastSinOrCosB(phase) * 0.05f;
    phase = FastAddRotations(*(float *)(vars + 0x140), 0.020362178f);
    *(float *)(vars + 0x140) = phase;
    *(float *)(moby + 0x18) += FastSinOrCosB(phase) * 0.25f;
}
