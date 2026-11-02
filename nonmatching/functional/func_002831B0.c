/* functional: high. Plain floats in place of the VU0 sqrt; the square root is taken of an absolute value, as the VU does. */
#include "common.h"

extern float D_001AC3C0[4];         /* polynomial coefficients */

/* Arc-sine style approximation: for x = |f| the polynomial c0 + c1*x + c2*x^2 + c3*x^3 times
   sqrt(1 - x), taken from pi/2, with the sign of the input put back. */
float func_002831B0(float f)
{
    float sign = 1.0f;
    float x = f, x2, x3, acc, root;

    if (f < 0.0f) {
        sign = -1.0f;
        x = -f;
    }
    {
        float d = 1.0f - x;
        root = __builtin_sqrtf(d < 0.0f ? -d : d);
    }
    x2 = x * x;
    x3 = x * x2;
    acc = D_001AC3C0[0] + 0.0f;
    acc = acc + x * D_001AC3C0[1];
    acc = acc + x2 * D_001AC3C0[2];
    acc = acc + x3 * D_001AC3C0[3];
    return sign * (1.57079637f - acc * root);
}
