#include "common.h"

extern float D_L20_001B20A0 __attribute__((sda));
extern float IntToFloat(int);

/* The EE ABI gives the integer and float arguments separate register banks. */
/* Gives a value that slides from one number to another as a level counter moves between a start and an end count. */
float level_interpolate_by_counter(int start, float startValue, float endValue, int end)
{
    if (D_L20_001B20A0 <= (float)start)
        return startValue;
    if ((float)end <= D_L20_001B20A0)
        return endValue;
    {
        float first = IntToFloat(start);
        float span = IntToFloat(end) - IntToFloat(start);
        float delta = endValue - startValue;
        /* Keep this source line together: its debug label precedes the subtraction. */
        float numerator = D_L20_001B20A0 - first; float fraction = numerator / span;
        return startValue + delta * fraction;
    }
}
