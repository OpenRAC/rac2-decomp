#include "names.h"
/* func_L02_003FE768: the boss health bar (shared by Maktar and Joba).
 * Own -G8 unit. Each screen edge is rounded into t and converted in a one-pass group
 * (docs/build/compiler-notes.md, source methods shared with RAC1): the group's loop notes keep
 * the D_001A7B90 mode load after the conversions, as retail schedules it. Without the
 * groups the load is hoisted across them (0 of 2 places).
 */
#include "common.h"
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern int FloatToInt(float);
extern int math_lerp_int_fraction(int, int, float);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern int g_boss_bar_left __attribute__((sda));
extern int g_boss_bar_right[] __attribute__((sda));
extern int g_boss_bar_top[] __attribute__((sda));
extern int g_boss_bar_bottom[] __attribute__((sda));
extern int g_boss_bar_height_offset __attribute__((sda));
extern int g_boss_bar_low_color __attribute__((sda));
extern int g_boss_bar_mid_color[] __attribute__((sda));
extern int g_boss_bar_high_color[] __attribute__((sda));
extern float g_hud_label_scale[] __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));

/* Draws the boss health bar. The bar gets shorter as health drops and changes colour from green toward red. */
void hud_draw_boss_health_bar(float fraction)
{
    int width;
    int color;
    int top;
    int bottom;
    int left;
    int right;
    float t;
    VU1_addGSregister(0x42, 0x8000000044ULL);
    if (fraction < 0.0f)
        fraction = 0.0f;
    width = FloatToInt((float)(g_boss_bar_right[0] - g_boss_bar_left) * fraction);
    if (fraction > 0.5f)
        color = math_lerp_int_fraction(g_boss_bar_mid_color[0], g_boss_bar_low_color, fraction + fraction - 1.0f);
    else
        color = math_lerp_int_fraction(g_boss_bar_high_color[0], g_boss_bar_mid_color[0], fraction + fraction);
    t = (float)g_boss_bar_top[0] * g_hud_label_scale[0] + 0.5f;
    do {
        top = t;
    } while (0);
    if (g_is_pal_video[0])
        top -= g_boss_bar_height_offset;
    left = g_boss_bar_left;
    right = left + width;
    t = (float)g_boss_bar_bottom[0] * g_hud_label_scale[0] + 0.5f;
    do {
        bottom = t;
    } while (0);
    if (g_is_pal_video[0])
        bottom -= g_boss_bar_height_offset;
    AppendScreenRectPacket(left, top, right, bottom, color, 0);
}
