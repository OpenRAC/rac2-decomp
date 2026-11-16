#include "include_asm.h"
#include "names.h"
extern int g_game_l00_mode;
extern int g_gauge_popup_timer __attribute__((sda));
extern int g_gauge_popup_result __attribute__((sda));
extern int math_fast_float_d(void *);
extern void level_clear_table_entry(int);

/* Checks for a button press while the gauge pop-up is shown and, if so, asks the pop-up system to close it. */
int gauge_popup_poll_input_us2(void)
{
    if (g_game_l00_mode == 0 && math_fast_float_d(&g_gauge_popup_timer) != 0)
        level_clear_table_entry(1);
    return g_gauge_popup_result;
}
