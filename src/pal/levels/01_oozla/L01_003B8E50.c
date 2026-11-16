#include "include_asm.h"

#include "common.h"
extern int math_fast_float_d();
extern int math_random_int_range(int, int);
extern void value_set_and_smooth_pal(u8 *, u8 *, s32, s32, f32);
extern u8 *g_swamp_patrol_positions __attribute__((sda));

/* Clears the measured 0x350 word when it is set, then draws the new duration
   if the old one is still short. */
void swamp_beast_update_timers_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    u16 flags;

    if (*(u32 *)(state + 0x350) != 0) {
        *(u32 *)(state + 0x350) = 0;
        if (*(s32 *)(state + 0x330) < 167) {
            *(u32 *)(state + 0x330) = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
        }
    }
    if (*(u32 *)(state + 0x244) != 1)
        math_fast_float_d(state + 0x330);
    flags = *(u16 *)(moby + 0x96);
    if (flags < 65534)
        *(u16 *)(moby + 0x96) = flags + 1;
    math_fast_float_d(state + 0x32C);
    math_fast_float_d(state + 0x334);
    value_set_and_smooth_pal(moby, state + 0x250, 6, 1, 4.0f);
}


