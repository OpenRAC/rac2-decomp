#include "include_asm.h"

#include "common.h"
#define NULL 0
extern void *ref_L10_004176C0_00();
extern void ref_L10_004176C0_01(s32, s32, s8 *, s32);
extern void ref_L10_004176C0_02(s8 *, s32, s32, f32, s32, f32, f32, f32, s32, s32, s32);
extern s32 ref_L10_004176C0_03(s32, s32);

/* Plays the carried flash on the boss when its timer has run out, then sets a new random timer (PAL copy of hrugis_play_carried_flash, 50 Hz timings). */
void hrugis_play_carried_flash_pal(s8 *moby) {
    s8 *vars;
    s8 *carried;

    vars = *(s8 **)(moby + 0x68);
    carried = (s8 *)ref_L10_004176C0_00();
    if (carried != NULL && *(s32 *)(carried + 0x120) != 0 && *(s32 *)(vars + 0x2E4) == 0) {
        ref_L10_004176C0_01(0, 0, moby, 0xF86);
        ref_L10_004176C0_02(moby, 0x6000FF00, 1, 0.5f, 0, 2.0f, 0.9f, 1.3f, 0x1E, 2, *(s32 *)(vars + 0x2C0));
        ref_L10_004176C0_02(moby, 0x6000FF00, 1, 0.5f, 0, 2.0f, 0.9f, 1.3f, 0x1E, 2, *(s32 *)(vars + 0x2C4));
        *(s32 *)(vars + 0x2E4) = ((s32)(ref_L10_004176C0_03(0x32, 0x78)) * 5 + 2) / 6;
    }
}
