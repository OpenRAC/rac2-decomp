#include "names.h"
/* The retail's single-precision minimum, 8 bytes: jr $ra ; MIN.S $f0,$f12,$f13.
   MIN_EXPR on floats only exists under -ffast-math, and -O1 keeps both
   operands in their argument registers (see func_L00_002EE050). */
/* Returns the smaller of two numbers. */
float math_fmin(float a, float b) {
    return b < a ? b : a;
}
