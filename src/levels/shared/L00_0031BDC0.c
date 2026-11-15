#include "include_asm.h"
#include "names.h"

/* func_L00_0031BDC0 is a unit of its own: it needs -ffast-math, the flag that lets the
   fold turn the clamp into the retail's `max.s` and `min.s` (the float MIN/MAX class of
   docs/build/compiler-notes.md). The flag changes every other body of a shared unit, so the
   function lives here alone. */

typedef float f32;

extern void func_00282CF0(f32 *, const f32 *, const f32 *);

extern f32 func_00282DB0(const f32 *, const f32 *);

extern void func_00282D30(f32 *, const f32 *, f32);

extern void func_00282CC0(f32 *, const f32 *, const f32 *);

/* Projects the first vector on the segment the second one draws, clamps the ratio
   between zero and one and moves the result onto the destination vector. */
f32 func_L00_0031BDC0(f32 *result, const f32 *point, const f32 *segStart, const f32 *segEnd)
{
    f32 toStart[4];
    f32 segment[4];
    f32 ratio;

    FastVecSub(toStart, segStart, point);
    FastVecSub(segment, segEnd, point);
    ratio = FastVecDot(toStart, segment) / FastVecDot(toStart, toStart);
    ratio = (ratio > 0.0f) ? ratio : 0.0f;
    ratio = (ratio < 1.0f) ? ratio : 1.0f;
    FastVecScale(toStart, toStart, ratio);
    FastVecAdd(result, point, toStart);
    return ratio;
}
