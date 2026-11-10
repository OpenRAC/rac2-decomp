#include "include_asm.h"

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
f32 func_L00_0031BDC0(f32 *dst, const f32 *a1, const f32 *a2, const f32 *a3)
{
    f32 buf1[4];
    f32 buf2[4];
    f32 t;

    func_00282CF0(buf1, a2, a1);
    func_00282CF0(buf2, a3, a1);
    t = func_00282DB0(buf1, buf2) / func_00282DB0(buf1, buf1);
    t = (t > 0.0f) ? t : 0.0f;
    t = (t < 1.0f) ? t : 1.0f;
    func_00282D30(buf1, buf1, t);
    func_00282CC0(dst, a1, buf1);
    return t;
}
