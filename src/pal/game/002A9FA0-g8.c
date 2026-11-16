#include "names.h"
/* func_PAL_002A9FA0, the PAL copy of func_002A9588: the same C, with span scaled to 50 Hz at each use. */
extern int g_ping_pong_counter_a __attribute__((sda));
extern int g_ping_pong_counter_b __attribute__((sda));
extern int FastTweenColor(int, int, float);

/* Blends two colors back and forth over a time span using a shared counter (PAL: span scaled to 50 Hz). */
int math_ping_pong_blend_values_pal(int first, int second, int span, int mode, int reset)
{
    int *counter = &g_ping_pong_counter_b;
    int phase;
    float amount;
    if (mode == 0) counter = &g_ping_pong_counter_a;
    ++*counter;
    if (reset)
        *counter = 0;
    phase = *counter % (((span * 2) * 5 + 2) / 6);
    if (phase >= (span * 5 + 2) / 6)
        amount = 1.0f - (float)(phase - (span * 5 + 2) / 6) / (float)((span * 5 + 2) / 6);
    else
        amount = (float)phase / (float)((span * 5 + 2) / 6);
    return FastTweenColor(second, first, amount);
}
