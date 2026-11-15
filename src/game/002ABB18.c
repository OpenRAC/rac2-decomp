#include "names.h"
/* Wraps an angle into [-pi, pi): shifts it by pi, takes the fractional part of the turn
   count and scales it back. */
extern float SplitFloatFraction(float x, float *whole);

float math_wrap_angle_to_pi(float x)
{
    float whole;

    x += 3.1415927f;
    x *= 0.15915494f;
    x = SplitFloatFraction(x, &whole);
    x *= 6.2831855f;
    x -= 3.1415927f;
    return x;
}
