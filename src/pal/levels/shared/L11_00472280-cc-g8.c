#include "names.h"
/* func_PAL_L11_00472280, the PAL copy of func_L11_0046C118: the same C, where wrap D_L11_001B2604 (({e}) * 1.2f). */

/* Level 11's own data: the addresses are the ones in level 11, and every other
 * level that holds this function reads its own copy of them. */
extern float g_trail_l11_uv_scroll __attribute__((sda));
extern float g_trail_scroll_step __attribute__((sda));
extern int g_trail_int_param_a __attribute__((sda));
extern int g_trail_int_param_b __attribute__((sda));
extern float g_trail_width_scale __attribute__((sda));
extern float g_trail_float_param_a __attribute__((sda));
extern float g_trail_float_param_d __attribute__((sda));
extern int g_trail_int_param_c __attribute__((sda));
extern int g_trail_int_param_d __attribute__((sda));
extern float g_trail_float_param_b __attribute__((sda));
extern float g_trail_float_param_c __attribute__((sda));
extern float g_trail_float_param_e __attribute__((sda));

/* The level's table of entries: addressed absolutely, never $gp-relative. */
extern char g_ribbon_row_table[] __attribute__((nosda));

extern void DrawScrollingRibbonWithHaloAlpha(int a0, int a1, int a2, int a3, float f12, float f13, float f14);

/* Clamps the level's timer and hands two table entries to the level's helper:
 * the first at the table's head, the second one record further on. */
void func_PAL_L11_00472280(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);
    float v;

    v = g_trail_l11_uv_scroll - ((g_trail_scroll_step) * 1.2f);
    g_trail_l11_uv_scroll = v;
    if (v <= -8.0f) {
        g_trail_l11_uv_scroll = v + 8.0f;
    }
    DrawScrollingRibbonWithHaloAlpha(*(int *)(s2 + 0x38) * 640 + (int)g_ribbon_row_table,
                      g_trail_int_param_a, g_trail_int_param_b, *(int *)(s2 + 0x2C) - 2,
                      g_trail_width_scale, g_trail_float_param_a, g_trail_float_param_d);
    DrawScrollingRibbonWithHaloAlpha(*(int *)(s2 + 0x38) * 640 + (int)(g_ribbon_row_table + 0x140),
                      g_trail_int_param_c, g_trail_int_param_d, *(int *)(s2 + 0x2C),
                      g_trail_float_param_b, g_trail_float_param_c, g_trail_float_param_e);
}
