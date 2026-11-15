#include "include_asm.h"
#include "names.h"

/* Round x to a decimal place count: scale = 10^a0, then round(x * scale) / scale.
   -g for the nop pair before div.s. */
extern int FloatToInt(float x);

float math_round_to_decimal_places(int places, float x)
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
