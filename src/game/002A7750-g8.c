#include "include_asm.h"
#include "names.h"
extern int D_L00_001AA1D4 __attribute__((sda));
extern int D_L00_001AA1D8 __attribute__((sda));
extern int func_00283D38(int, int, float);

/* Blends between two values, ping-ponging back and forth over a span of steps with a shared counter. */
int func_002A9588(int first, int second, int span, int mode, int reset)
{
    int *counter = &D_L00_001AA1D8;
    int phase;
    float amount;
    if (mode == 0) counter = &D_L00_001AA1D4;
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
