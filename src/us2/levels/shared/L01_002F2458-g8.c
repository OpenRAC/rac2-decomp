#include "include_asm.h"
#include "names.h"
extern int g_hero_l01_control_mode;
extern char g_hud_overlay_timer __attribute__((sda));
extern int g_hud_overlay_result_code __attribute__((sda));
extern int math_fast_float_d(char *);
extern void level_clear_table_entry(int);

int level_tick_timer_get_value_us2(void) {
    if (g_hero_l01_control_mode == 0) {
        if (math_fast_float_d(&g_hud_overlay_timer))
            level_clear_table_entry(0);
    }
    return g_hud_overlay_result_code;
}
