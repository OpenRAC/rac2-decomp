#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef int s32;

extern f32 func_L04_004554F8(f32 value);

/* Periodic light blend: hold at zero, ease in, hold at one, then ease out.
 * Debug line labels preserve the retail division padding. */
f32 func_L04_00455418(char *a0, f32 x)
{
    f32 v = x;
    f32 span = *(f32 *)(a0 + 0xE4);
    f32 lo = *(f32 *)(a0 + 0x10);
    s32 n = (s32)(v / span);

    v = v - (f32)n * span;
    if (v < lo)
        return 0.0f;
    v = v - lo;
    {
        f32 d = *(f32 *)(a0 + 0x14);
        if (v < d) {
            return SmoothStep(v / d);
        }
        v = v - d;
    }
    {
        f32 e = *(f32 *)(a0 + 0x18);
        if (v < e)
            return 1.0f;
        v = v - e;
        return 1.0f - SmoothStep(v / *(f32 *)(a0 + 0x1C));
    }
}
