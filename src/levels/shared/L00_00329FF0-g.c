#include "include_asm.h"

/* func_L00_00329FF0 is a unit of its own: it is built with -g, whose line label in front of
   the `div.s` makes the assembler pad that division with retail's two nops (the
   division-floor class of docs/build/compiler-notes.md). The division has to be a statement of
   its own for the label to land on it, and the integer divisor has to be converted on a
   line of its own too, so that the conversion lands between the call and the division. */

typedef int s32;

typedef float f32;

extern f32 func_00283CE0(s32);

extern int func_00283CF0(f32);

/* Adjust a non-aligned value through the integer/float conversion helpers. */
s32 func_L00_00329FF0(s32 value) {
    s32 divisor = 16;

    if (value % divisor != 0) {
        f32 q;
        f32 d;

        q = func_00283CE0(value);
        d = (f32)divisor;
        q = q / d;
        value = (func_00283CF0(q) + 1) << 4;
    }
    return value;
}
