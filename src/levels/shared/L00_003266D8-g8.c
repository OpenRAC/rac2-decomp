#include "names.h"
typedef int s32;

extern s32 g_input_block_flag;
extern s32 g_pad_press_window;
extern s32 g_hit_streak_state;
extern s32 ref_L00_003266D8_00 __attribute__((sda));
extern s32 ref_L00_003266D8_01 __attribute__((sda));
extern s32 g_hit_streak_enabled __attribute__((sda));
extern s32 g_hit_streak_hud_slot __attribute__((sda));
extern unsigned char g_hit_streak_hud_data_a[];
extern unsigned char g_hit_streak_hud_data_b[];
extern unsigned char g_hit_streak_hud_data_c[];
extern s32 hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
extern s32 level_raise_record_peak(s32, s32);

/* Counts down the hit streak timers each frame and shows or hides the streak effect while the streak is active. */
void hero_update_hit_streak_effect(void) {
    if (g_input_block_flag == 0) {
        s32 count = g_pad_press_window + 1;

        ref_L00_003266D8_00 = count;
        if (count > 10)
            ref_L00_003266D8_00 = 10;
    } else {
        g_pad_press_window = 0;
    }
    if (g_hit_streak_state != 0) {
        ref_L00_003266D8_01 = g_hit_streak_state - 1;
        if (ref_L00_003266D8_01 == 0)
            g_input_block_flag = 0;
    }
    if (g_input_block_flag == 0 || g_hit_streak_enabled == 0) {
        g_hit_streak_hud_slot = -1;
    } else {
        if (g_hit_streak_hud_slot == -1)
            g_hit_streak_hud_slot = hud_set_slot_contents(12, 0, g_hit_streak_hud_data_a, g_hit_streak_hud_data_b,
                                           g_hit_streak_hud_data_c, 0, 0);
        else
            level_raise_record_peak(g_hit_streak_hud_slot, 10);
    }
}
