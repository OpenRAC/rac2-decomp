#include "include_asm.h"
#include "names.h"

extern int g_game_l00_mode;
extern int g_gauge_popup_timer __attribute__((sda));
extern int g_gauge_popup_result __attribute__((sda));
extern int math_fast_float_d(void *);
extern void level_clear_table_entry(int);
/* Checks for a button press while the gauge pop-up is shown and, if so, asks the pop-up system to close it. */
int gauge_popup_poll_input(void)
{
    if (g_game_l00_mode == 0 && math_fast_float_d(&g_gauge_popup_timer) != 0)
        level_clear_table_entry(1);
    return g_gauge_popup_result;
}

extern int g_gauge_popup_blend __attribute__((sda));
extern int g_gauge_popup_mode __attribute__((sda));
extern float g_gauge_popup_amount __attribute__((sda));
extern int g_gauge_popup_color_a __attribute__((sda));
extern int g_gauge_popup_color_b __attribute__((sda));
extern int gauge_popup_draw(void);
extern int level_set_table_entry(int (*)(void), int (*)(void), int);
extern float math_step_int_toward_target(int *, int, int);
