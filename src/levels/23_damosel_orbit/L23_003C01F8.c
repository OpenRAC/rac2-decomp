#include "include_asm.h"
#include "names.h"

/* func_L23_003C01F8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI16 __attribute__((mode(TI)));

extern float D_L23_001AFA10 __attribute__((sda));

extern TI16 D_L23_001C0AA0;

extern void func_L23_003BFFC0(char *arg0, int arg1, int arg2, int arg3, int arg4, float arg5);

extern void func_L23_00418650(TI16 *, float);

extern int func_002761F8(TI16 *, TI16 *, int, int, int);

/* Starts the walking animation when needed, and optionally drops the enemy onto the ground below it. */
void func_L23_003C01F8(char *mobyOrProbeEnd, int snapToGround) {
    TI16 probeStart;
    TI16 probeEnd;
    TI16 *probeStartPtr;

    if ((unsigned char)(*(unsigned char *)(mobyOrProbeEnd + 0x43) - 5) >= 2 && *(unsigned char *)(mobyOrProbeEnd + 0x20) != 2)
        PlayAnimOnObjectAndLink(mobyOrProbeEnd, 5, 0, 6, 1, D_L23_001AFA10);
    if (snapToGround != 0) {
        TI16 *posPtr = (TI16 *)(mobyOrProbeEnd + 0x10);

        /* b's address is formed between the two copies, where retail has it. */
        probeStartPtr = &probeStart;
        probeStart = *posPtr;
        mobyOrProbeEnd = (char *)&probeEnd;
        probeEnd = *posPtr;
        ProjectPointOntoPlanetSurface((TI16 *)mobyOrProbeEnd, -2.0f);
        ProjectPointOntoPlanetSurface(probeStartPtr, 0.1f);
        if (CollLine((TI16 *)mobyOrProbeEnd, probeStartPtr, 0x12, 0, 0) != 0)
            *posPtr = D_L23_001C0AA0;
    }
}
