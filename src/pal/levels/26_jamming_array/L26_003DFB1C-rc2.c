#include "include_asm.h"

#include "common.h"
extern s8 ref_L26_003DC048_00[];
extern void ref_L26_003DC048_01(s8 *);
extern void ref_L26_003DC048_02(s8 *, s8 *);
extern f32 ref_L26_003DC048_03(f32, f32);
extern void ref_L26_003DC048_04(s8 *, s8 *, s32, s8 *, f32);

/* Ticks the creature's part timers and turn angle (PAL), and counts up the 16-bit frame counter at +0x96 until it saturates. */
void creature_tick_timers_pal(s8 *moby) {
    s8 *vars;
    f32 angle;
    u16 counter;

    vars = *(s8 **)(moby + 0x68);
    ref_L26_003DC048_01(vars + 0x220);
    ref_L26_003DC048_01(vars + 0x222);
    ref_L26_003DC048_02(moby, vars + 0x278);
    if (*(u8 *)(moby + 0x95) == 2) {
        angle = ref_L26_003DC048_03(*(f32 *)(vars + 0x27C), 0.25132746f);
        *(f32 *)(vars + 0x27C) = angle;
        ref_L26_003DC048_04(moby, vars + 0x270, 1, ref_L26_003DC048_00, angle);
    } else {
        angle = ref_L26_003DC048_03(*(f32 *)(vars + 0x27C), 0.013962637f);
        *(f32 *)(vars + 0x27C) = angle;
        ref_L26_003DC048_04(moby, vars + 0x270, 0, ref_L26_003DC048_00, angle);
    }
    counter = *(u16 *)(moby + 0x96);
    if (counter <= 0xFFFE) {
        *(u16 *)(moby + 0x96) = counter + 1;
    }
}
