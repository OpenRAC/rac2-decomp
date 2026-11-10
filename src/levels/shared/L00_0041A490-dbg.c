#include "include_asm.h"

/* func_L00_0041A490 is a unit of its own: it needs the debug profile (-g, config/cflags.txt).
   The line labels cc1 emits with -g ($LM) are code labels, and a code label right in front of
   a `div.s` is what the assembler's division floor needs to add retail's two nops before the
   division (docs/build/compiler-notes.md, the division-erratum section). The float division is
   therefore a statement of its own, so the label lands on the `div.s`. */

typedef int s32;
typedef float f32;

extern f32 func_00283CE0(s32);

extern int func_00283CF0(f32);

/* Rounds a value up to the next multiple of sixteen; an already aligned value is returned
   unchanged. */
s32 func_L00_0041A490(s32 value)
{
    s32 divisor = 16;
    f32 fdiv;
    f32 q;

    if (value % divisor != 0) {
        q = func_00283CE0(value);
        fdiv = (f32)divisor;
        q = q / fdiv;
        value = (func_00283CF0(q) + 1) << 4;
    }
    return value;
}
