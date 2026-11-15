#include "names.h"
typedef int L30TI128 __attribute__((mode(TI)));

extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_002A9640(char *, int, int);

/* Moves a sliding object between its rest position and its moved position when triggered, and puts it back when its animation ends. */
void func_L30_003DA040(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(L30TI128 *)(vars + 0x100) = *(L30TI128 *)(moby + 0x10);
        SetMobyState(moby, 1, -1);
        if (*(unsigned char *)(moby + 0x43) != 1) {
            StartAnimationBlended(moby, 1, 0, 1);
        }
        *(float *)(moby + 0x48) = 0.0f;
        break;
    case 1:
        if (FindOwnedEffectSlot(moby, 0x10000, 0) != 0) {
            SetMobyState(moby, 2, -1);
            if (*(unsigned char *)(moby + 0x43) != 1) {
                StartAnimationBlended(moby, 1, 0, 1);
            }
            *(float *)(moby + 0x48) = 1.0f;
        }
        break;
    case 2:
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            *(L30TI128 *)(moby + 0x10) = *(L30TI128 *)(vars + 0x100);
            SetMobyState(moby, 1, -1);
            if (*(unsigned char *)(moby + 0x43) != 0) {
                StartAnimationBlended(moby, 0, 0, 1);
            }
            *(float *)(moby + 0x48) = 0.0f;
        }
        break;
    }
    *(unsigned char *)(moby + 0xA8) = 0xFF;
}
