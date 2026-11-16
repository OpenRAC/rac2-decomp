#include "include_asm.h"
#include "names.h"

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

extern void DrawScrollingRibbonWithHaloAlpha(int moby, int a1, int a2, int a3, float f12, float f13, float f14);

/* Clamps the level's timer and hands two table entries to the level's helper:
 * the first at the table's head, the second one record further on. */
void DrawObjectRibbonPair(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float scroll;

    scroll = g_trail_l11_uv_scroll - g_trail_scroll_step;
    g_trail_l11_uv_scroll = scroll;
    if (scroll <= -8.0f) {
        g_trail_l11_uv_scroll = scroll + 8.0f;
    }
    DrawScrollingRibbonWithHaloAlpha(*(int *)(vars + 0x38) * 640 + (int)g_ribbon_row_table,
                      g_trail_int_param_a, g_trail_int_param_b, *(int *)(vars + 0x2C) - 2,
                      g_trail_width_scale, g_trail_float_param_a, g_trail_float_param_d);
    DrawScrollingRibbonWithHaloAlpha(*(int *)(vars + 0x38) * 640 + (int)(g_ribbon_row_table + 0x140),
                      g_trail_int_param_c, g_trail_int_param_d, *(int *)(vars + 0x2C),
                      g_trail_float_param_b, g_trail_float_param_c, g_trail_float_param_e);
}
