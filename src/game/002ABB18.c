#include "names.h"
/* Wraps an angle into [-pi, pi): shifts it by pi, takes the fractional part of the turn
   count and scales it back. */
extern float func_00283CC8(float x, float *whole);

float func_002ABB18(float x)
{
    float whole;

    x += 3.1415927f;
    x *= 0.15915494f;
    x = SplitFloatFraction(x, &whole);
    x *= 6.2831855f;
    x -= 3.1415927f;
    return x;
}
