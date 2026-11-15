#include "names.h"
/* Carried from rac3-decomp (src/frontbin/3AA9D8.c, func_003AACC0): the same instructions.
   Writes func_0034EE78(t, 0, p[8], p[0xC], 1) to *out. */

#include "common.h"

extern f32 math_eval_cubic_hermite(f32, f32, f32, f32, f32);

/* Evaluates a curve at time t using two values stored in the object and saves the result. */
void math_evaluate_curve_to_output(u8 *curve, f32 *out, f32 t) {
    *out = math_eval_cubic_hermite(t, 0.0f, *(f32 *)(curve + 8), *(f32 *)(curve + 0xC), 1.0f);
}
