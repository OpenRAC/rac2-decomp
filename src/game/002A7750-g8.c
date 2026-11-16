#include "include_asm.h"
#include "names.h"
extern int g_ping_pong_counter_a __attribute__((sda));
extern int g_ping_pong_counter_b __attribute__((sda));
extern int FastTweenColor(int, int, float);

/* Blends between two values, ping-ponging back and forth over a span of steps with a shared counter. */
int math_ping_pong_blend_values(int first, int second, int span, int mode, int reset)
{
    int *counter = &g_ping_pong_counter_b;
    int phase;
    float amount;
    if (mode == 0) counter = &g_ping_pong_counter_a;
    ++*counter;
    if (reset)
        *counter = 0;
    phase = *counter % (span * 2);
    if (phase >= span)
        amount = 1.0f - (float)(phase - span) / (float)span;
    else
        amount = (float)phase / (float)span;
    return FastTweenColor(second, first, amount);
}
