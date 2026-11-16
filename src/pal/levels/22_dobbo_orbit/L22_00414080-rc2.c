#include "include_asm.h"

#include "common.h"
extern s32 ref_L22_00415A48_00(s32 *a, void *b);
extern s32 ref_L22_00415A48_01(s32 a, s32 b);
extern struct { s32 w0; s32 w1; s32 w2; } g_timer_hud_words;

/* Timer trigger: counts down while its state is active and restarts the timer on the trigger event. (PAL) */
void timer_trigger_update_pal(void *moby) {
    s32 *timer;
    void *hud;

    timer = (*(s32 **)((s8 *)(moby) + (0x68)));
    if ((*(u8 *)((s8 *)(moby) + (0x20))) == 0) {
        (*(u8 *)((s8 *)(moby) + (0x20))) = 1U;
        (*(u8 *)((s8 *)(moby) + (0x30))) = 0xFF;
        *timer = 0x5DC;
    }
    if ((*(u8 *)((s8 *)(moby) + (0x20))) == 1) {
        hud = (void *) g_timer_hud_words.w0;
        if ((ref_L22_00415A48_00(timer, moby) != 0) && ((*(s32 *)((s8 *)(hud) + (8))) == 0)) {
            if ((*(s32 *)((s8 *)(hud) + (0xC))) == 0) {
                ref_L22_00415A48_01(0x9FD, 0x54);
                *timer = 0x5DC;
            }
        }
    }
}
