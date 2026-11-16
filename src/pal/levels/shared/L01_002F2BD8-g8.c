#include "include_asm.h"
#include "names.h"
extern int g_hero_l01_control_mode;
extern char g_hud_overlay_timer __attribute__((sda));
extern int g_hud_overlay_result_code __attribute__((sda));
extern int math_fast_float_d(char *);
extern void level_clear_table_entry(int);

/* Ticks the HUD overlay timer while the hero is in normal control, clears table entry 0 when it ends, and returns the overlay result code (PAL). */
int level_tick_timer_get_value_pal(void) {
    if (g_hero_l01_control_mode == 0) {
        if (math_fast_float_d(&g_hud_overlay_timer))
            level_clear_table_entry(0);
    }
    return g_hud_overlay_result_code;
}
