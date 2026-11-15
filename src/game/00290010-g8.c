#include "common.h"

/* A unit of its own so that the call to func_00290628 goes through its symbol: PAL and USA v2.00 have has
   that function as assembly at an address of its own, and a call within one object can only
   reach the object's own copy. */

extern int g_gauge_popup_blend __attribute__((sda));
extern int g_gauge_popup_mode __attribute__((sda));
extern float g_gauge_popup_amount __attribute__((sda));
extern int g_gauge_popup_color_a __attribute__((sda));
extern int g_gauge_popup_color_b __attribute__((sda));
extern int gauge_popup_poll_input(void);
extern int gauge_popup_draw(void);
extern void level_set_table_entry(int (*)(void), int (*)(void), int);
extern float math_step_int_toward_target(int *, int, int);

/* Shows the gauge pop-up in the given mode with two bar colours and a fill amount. */
void gauge_popup_show(int mode, int first, int second, float amount)
{
    if (g_gauge_popup_blend == 0 || (g_gauge_popup_mode != 2 && mode == 2)) {
        g_gauge_popup_mode = mode;
        level_set_table_entry(gauge_popup_poll_input, gauge_popup_draw, 1);
    }
    if (mode == g_gauge_popup_mode) {
        g_gauge_popup_color_a = first;
        g_gauge_popup_color_b = second;
        g_gauge_popup_amount = amount;
        math_step_int_toward_target(&g_gauge_popup_blend, 10, 2);
    }
}
