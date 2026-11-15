#include "common.h"

extern f32 func_00283B98(f32, f32);
extern s32 func_002B3868(u8 *);
extern void func_002E5CF8(s32, s32, u8 *);
/* Integer and FP argument banks retain their own order on EE. */
extern void func_002AAA00(f32 *, f32, u8 *, f32, f32, f32, s32);
extern void func_002A7750(u8 *, s32, s32);

/* Turns the object back and forth between two angles, pausing at each end for a couple of seconds, with a turning sound. */
void func_L13_003EFD58(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u16 ticks;
    s32 nextTicks;
    u32 state = moby[0x20];

    switch (state) {
    case 0:
        moby[0x30] = 0xFF;
        *(f32 *)(vars + 8) = *(f32 *)(moby + 0xF0);
        *(f32 *)vars = FastAddRotations(*(f32 *)(moby + 0xF0), 0.78539824f);
        moby[0x20] = 1;
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 1:
        if (SetFirstPendingFlag(moby))
            PlayMobySound(0, 0, moby);
        ApproachTargetWithDirectionMode((f32 *)(moby + 0xF0), *(f32 *)vars, vars + 4, 0.00087266474f, 0.00087266474f,
                      0.10471977f, 0);
        ticks = *(u16 *)(moby + 0x96);
        if (ticks < 0x79) {
            nextTicks = ticks + 1;
            break;
        }
        SetMobyState(moby, 3, -1);
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 3:
        if (SetFirstPendingFlag(moby))
            PlayMobySound(0, 0, moby);
        ApproachTargetWithDirectionMode((f32 *)(moby + 0xF0), *(f32 *)(vars + 8), vars + 4, 0.00087266474f,
                      0.00087266474f, 0.10471977f, 0);
        ticks = *(u16 *)(moby + 0x96);
        if (ticks < 0x79) {
            nextTicks = ticks + 1;
            break;
        }
        SetMobyState(moby, 1, -1);
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 2:
    case 4:
        return;
    default:
        return;
    }
    *(u16 *)(moby + 0x96) = nextTicks;
}
