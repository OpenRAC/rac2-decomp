#include "common.h"

extern f32 FastAddRotations(f32, f32);
extern s32 flag_set_first_pending(u8 *);
extern void PlayMobySound(s32, s32, u8 *);
/* Integer and FP argument banks retain their own order on EE. */
extern void math_approach_target_with_direction_mode(f32 *, f32, u8 *, f32, f32, f32, s32);
extern void moby_set_state(u8 *, s32, s32);

/* Turns the object back and forth between two angles, pausing at each end for a couple of seconds, with a turning sound. */
void swinging_update(u8 *moby) {
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
        if (flag_set_first_pending(moby))
            PlayMobySound(0, 0, moby);
        math_approach_target_with_direction_mode((f32 *)(moby + 0xF0), *(f32 *)vars, vars + 4, 0.00087266474f, 0.00087266474f,
                      0.10471977f, 0);
        ticks = *(u16 *)(moby + 0x96);
        if (ticks < 0x79) {
            nextTicks = ticks + 1;
            break;
        }
        moby_set_state(moby, 3, -1);
        *(u16 *)(moby + 0x96) = 0;
        return;
    case 3:
        if (flag_set_first_pending(moby))
            PlayMobySound(0, 0, moby);
        math_approach_target_with_direction_mode((f32 *)(moby + 0xF0), *(f32 *)(vars + 8), vars + 4, 0.00087266474f,
                      0.00087266474f, 0.10471977f, 0);
        ticks = *(u16 *)(moby + 0x96);
        if (ticks < 0x79) {
            nextTicks = ticks + 1;
            break;
        }
        moby_set_state(moby, 1, -1);
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
