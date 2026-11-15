#include "names.h"
/* The retail's two-argument float maximum, 8 bytes at 27 places:
   jr $ra ; 0x460D6028 - the R5900 single-precision MAX.S (COP1 format S,
   funct 0x28; the group's other members are ADDA.S 0x18, MADD.S 0x1C and
   MIN.S 0x29).  The compiler emits `max.s` only for a comparison folded into
   a MAX_EXPR, which -ffast-math enables, and at -O1 the reload keeps both
   operands in their argument registers; at -O2 it merges the output with the
   first operand and copies it into $f0, which gives 12 bytes instead of 8.
   The profile of this unit is therefore -O1 -ffast-math
   (config/cflags.txt); the other bodies of L00_002E5918.c need -O2. */
/* Returns the larger of two numbers. */
float math_max_float(float a, float b) {
    return b > a ? b : a;
}
