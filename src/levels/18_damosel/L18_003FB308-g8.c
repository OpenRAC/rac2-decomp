#include "common.h"

extern int D_L18_001B0580 __attribute__((sda));
extern float D_L18_001B0584 __attribute__((sda));
extern int D_L18_001B0588 __attribute__((sda));
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A7750(u8 *, int, int);
extern int func_002B3868(u8 *);
extern void func_002E5DA0(int, int, u8 *, int);
extern void func_L18_003FB620(u8 *);

/* Slides the object out and back by a fixed step each frame, moving a linked object
   with it, and sprays particles while it moves out. */
void func_L18_003FB308(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        qcopy_nc(vars, moby + 0x10);
        vec_scale_to_length(vars + 0x10, moby + 0xC0, D_L18_001B0584 / D_L18_001B0580);
        SetMobyState(moby, 1, -1);
        *(int *)(vars + 0x20) = 0;
        break;
    case 1: {
        if (*(int *)(vars + 0x20) >= 2) {
            FastVecSub(moby + 0x10, moby + 0x10, vars + 0x10);
            FastVecAdd(gMobyTable_L18[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         gMobyTable_L18[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         vars + 0x10);
            --*(int *)(vars + 0x20);
        } else if (*(int *)(vars + 0x20) > 0) {
            qcopy_nc(moby + 0x10, vars);
            qcopy_nc((u8 *)((*(int *)(vars + 0x24) << 8) +
                           (int)gMobyTable_L18[0] + 0x10), vars);
            --*(int *)(vars + 0x20);
        }
        break;
    }
    case 2:
        if (SetFirstPendingFlag(moby))
            PlaySoundFromClassBank(0, 0, moby, 0x1152);
        if (*(int *)(vars + 0x20) < D_L18_001B0580) {
            FastVecAdd(moby + 0x10, moby + 0x10, vars + 0x10);
            FastVecSub(gMobyTable_L18[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         gMobyTable_L18[0] + (*(int *)(vars + 0x24) << 8) + 0x10,
                         vars + 0x10);
            ++*(int *)(vars + 0x20);
        }
        if (*(int *)(vars + 0x28))
            SpawnTrailParticles(moby);
        if (D_L18_001B0588 < *(u16 *)(moby + 0x96))
            SetMobyState(moby, 1, -1);
        break;
    }
    if (*(u16 *)(moby + 0x96) <= 0xFFFEu)
        ++*(u16 *)(moby + 0x96);
}
