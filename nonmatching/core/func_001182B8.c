/* Retained log10 reconstruction: game -O2 -G2 -mastra-quad-saves,
 * 420/424 bytes in USA. Public fdlibm e_log10.c identifies the complete
 * subnormal scaling, exponent rebias, log call and three exact coefficients.
 * The old screen's unidentified decimal-helper inference is superseded.
 * Canonical software-double calls preserve the measured evaluation order.
 * The negative-input zero result and stored negative infinity are independently
 * measured retail paths. Word merge, prologue scheduling and saved-register
 * allocation differ; one-view explicit bit merge worsens to 396 bytes.
 * The union is initialized before each read and the high-word replacement
 * retains its initialized low word. No false return or synthetic dependency.
 * Current RAC1 scoped word macros were independently tried:432 bytes. They
 * restore the initial non-finite label nop but do not resolve saved-register
 * assignment or the raw-word representation. Best420-byte body retained.
 * Next: independently evidenced original double-word view and local lifetimes.
 */
/* Adapted from public fdlibm e_log10.c, version 5.1 (1993-09-24):
 * https://github.com/mirror/newlib-cygwin/blob/master/newlib/libm/math/e_log10.c
 *
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 *
 * Retail returns zero for a negative input, and its stored negative infinity
 * for either zero sign. Preserve those observed paths rather than assuming
 * the donor's exception-generating expressions survive unchanged.
 */
#include "common.h"
extern double func_00122A40(double, double), func_00122B00(double, double);
extern double func_00123078(int), func_00117CA0(double);
extern const double D_0013A480[];

typedef union {
    double value;
    long long bits;
    struct { unsigned int low; int high; } word;
} Log10Double;

double func_001182B8(double value)
{
    Log10Double shape;
    long long bits;
    int high, exponent = 0, sign;
    unsigned int low;
    double y, logarithm, z;
    shape.value = value;
    bits = shape.bits;
    high = (int)(bits >> 32);
    low = (unsigned int)bits;
    if (high <= 0x000fffff) {
        if (((high & 0x7fffffff) | low) == 0) return D_0013A480[0];
        if (high < 0) return 0.0;
        exponent -= 54;
        value = func_00122B00(value, 1.8014398509481984e16);
        shape.value = value;
        bits = shape.bits;
        high = (int)(bits >> 32);
    }
    if (high > 0x7fefffff) return func_00122A40(value, value);
    exponent += (high >> 20) - 1023;
    sign = (unsigned int)exponent >> 31;
    high = (high & 0x000fffff) | ((0x3ff - sign) << 20);
    y = func_00123078(exponent + sign);
    shape.value = value;
    shape.word.high = high;
    value = shape.value;
    logarithm = func_00117CA0(value);
    z = func_00122B00(y, 3.69423907715893078616e-13);
    z = func_00122A40(z, func_00122B00(logarithm, 4.34294481903251816668e-1));
    return func_00122A40(z, func_00122B00(y, 3.01029995663611771306e-1));
}
