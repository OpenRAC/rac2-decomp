/* Carried from rac3-decomp (src/frontbin/3AA9D8.c, func_003AACC0): the same instructions.
   Writes func_0034EE78(t, 0, p[8], p[0xC], 1) to *out. */

#include "common.h"

extern f32 func_0034EE78(f32, f32, f32, f32, f32);

/* Evaluates a curve at time t using two values stored in the object and saves the result. */
void func_00335C10(u8 *curve, f32 *out, f32 t) {
    *out = EvaluateCubicHermite(t, 0.0f, *(f32 *)(curve + 8), *(f32 *)(curve + 0xC), 1.0f);
}
