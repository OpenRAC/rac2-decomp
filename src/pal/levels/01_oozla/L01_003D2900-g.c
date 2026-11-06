#include "common.h"

/* func_PAL_L01_003D2900, the PAL copy of func_L01_003CE7D8: the same C, with the
   damping scaled by 1.2 for 50 Hz. */

extern float func_00282C48(float a0);

/* Damped follow step: blends the velocity at a1 toward the spring term, then
   advances the position at a0 and passes the remaining offset to func_00282C48. */
float func_PAL_L01_003D2900(f32 *a0, f32 *a1, f32 f12, f32 f13, f32 f14, f32 f15)
{
    f32 f0, f1, f2;

    f0 = 1.0f;
    f15 = f15 * f15;
    f2 = 1.2f;
    f1 = *a1;
    f14 = 1.0f - f14;
    f14 = f14 - 1.0f;
    f14 = f14 * f2;
    f14 = f14 + 1.0f;
    f1 = f1 * f14;
    *a1 = f1;
    f2 = *a0;
    f0 = f2 - f12;
    f0 = f0 * f0;
    if (!(f0 > f15)) {
    } else {
        f0 = f15;
    }
    f0 = f0 * f13;
    f0 = f0 / f15;
    if (f12 < f2)
        *a1 = f1 - f0;
    else
        *a1 = f1 + f0;
    f1 = *a1;
    f0 = *a0;
    f0 = f0 + f1;
    f12 = f12 - f0;
    *a0 = f0;
    return func_00282C48(f12);
}
