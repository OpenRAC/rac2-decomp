#include "include_asm.h"
#include "names.h"

/* Round x to a decimal place count: scale = 10^a0, then round(x * scale) / scale.
   -g for the nop pair before div.s. */
extern int func_00283CF0(float x);

float func_002AEAE0(int places, float x)
{
    int scaleInt = 1;
    float scale;
    int rounded;
    if (places > 0) {
        do {
            scaleInt *= 10;
        } while (--places != 0);
    }
    scale = (float)scaleInt;
    x += 1.0f / (scale + scale);
    rounded = FloatToInt(x * scale);
    x = (float)rounded;
    return x / scale;
}
