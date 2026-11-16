#include "include_asm.h"
#include "common.h"

extern char g_hero_button_hold_timers[];
extern char g_pad_state[];
extern int g_input_block_flag __attribute__((section(".sdata")));
extern s32 FastDecTimer(s32);
extern void level_set_flag_d_true(void);

/* Counts down the hero's button-hold timers and starts the special action when the button is pressed again in time. */
void hero_update_button_hold_timers(void)
{
    char *hero;
    char *pad;
    u64 timer;

    FastDecTimer(g_hero_button_hold_timers);
    FastDecTimer(g_hero_button_hold_timers + 2);
    hero = g_hero_button_hold_timers - 0x24F8;
    if (0x37 == *(int *)(hero + 0x2294))
        return;
    if (*(u8 *)(hero + 0x22BC) != 0)
        return;
    if (g_input_block_flag != 0)
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
