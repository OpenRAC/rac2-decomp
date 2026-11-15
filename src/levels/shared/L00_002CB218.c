#include "include_asm.h"
#include "common.h"

extern char D_0018C318[];
extern char g_pad_state[];
extern int D_L00_001A8FB4 __attribute__((section(".sdata")));
extern s32 FastDecTimer(s32);
extern void level_set_flag_d_true(void);

/* Counts down the hero's button-hold timers and starts the special action when the button is pressed again in time. */
void hero_update_button_hold_timers(void)
{
    char *hero;
    char *pad;
    u64 timer;

    FastDecTimer(D_0018C318);
    FastDecTimer(D_0018C318 + 2);
    hero = D_0018C318 - 0x24F8;
    if (0x37 == *(int *)(hero + 0x2294))
        return;
    if (*(u8 *)(hero + 0x22BC) != 0)
        return;
    if (D_L00_001A8FB4 != 0)
        return;
    pad = g_pad_state;
    if (*(int *)(pad + 0x1A4) & 0x10)
        *(short *)(hero + 0x24F8) = 20;
    timer = *(u32 *)(hero + 0x24F8);
    if (timer == 0)
        return;
    if (*(int *)(pad + 0x1B8) & 0x10) {
        if (*(short *)(hero + 0x24FA) == 0) {
            *(short *)(hero + 0x24FA) = 20;
            return;
        }
        *(int *)(hero + 0x2538) = 1;
        level_set_flag_d_true();
    }
}
