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
extern int D_L02_001B1330 __attribute__((sda));
extern int D_L02_001B1338[] __attribute__((sda));
extern int D_L02_001B1334[] __attribute__((sda));
extern int D_L02_001B133C[] __attribute__((sda));
extern int D_L02_001B1340 __attribute__((sda));
extern int D_L02_001B1348 __attribute__((sda));
extern int D_L02_001B134C[] __attribute__((sda));
extern int D_L02_001B1350[] __attribute__((sda));
extern float D_L02_001B3E04[] __attribute__((sda));
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
    width = FloatToInt((float)(D_L02_001B1338[0] - D_L02_001B1330) * fraction);
    if (fraction > 0.5f)
        color = math_lerp_int_fraction(D_L02_001B134C[0], D_L02_001B1348, fraction + fraction - 1.0f);
    else
        color = math_lerp_int_fraction(D_L02_001B1350[0], D_L02_001B134C[0], fraction + fraction);
    t = (float)D_L02_001B1334[0] * D_L02_001B3E04[0] + 0.5f;
    do {
        top = t;
    } while (0);
    if (g_is_pal_video[0])
        top -= D_L02_001B1340;
    left = D_L02_001B1330;
    right = left + width;
    t = (float)D_L02_001B133C[0] * D_L02_001B3E04[0] + 0.5f;
    do {
        bottom = t;
    } while (0);
    if (g_is_pal_video[0])
        bottom -= D_L02_001B1340;
    AppendScreenRectPacket(left, top, right, bottom, color, 0);
}
