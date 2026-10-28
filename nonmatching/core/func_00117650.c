/* Retained floor reconstruction: game -O2 -G2 -mastra-quad-saves,
 * 468/500 bytes in USA. The public fdlibm identity is now established by
 * its 20/52 fraction split, huge+x checks, sign-preserving subunit cases,
 * carry handling and x+x non-finite path. The original object SDK profile
 * also produces468 bytes with sd/ld saves, so it does not supply the missing
 * quad-save or final word-merge shape. The original screen's dtoa-only
 * inference is superseded. Plain/bitfield output unions tie; direct parameter
 * word access is 448 bytes with stack traffic, and no-schedule-insns2 is
 * 456 bytes. The frame, save scheduling and final word merge remain different.
 * All input bits come from the initialized argument and both output words
 * are assigned. No uninitialized accumulator or synthetic mask dependency.
 * Next: independently evidenced original double-word representation/profile.
 */
/* Adapted from public fdlibm s_floor.c, version 5.1 (1993-09-24):
 * https://github.com/mirror/newlib-cygwin/blob/master/newlib/libm/math/s_floor.c
 *
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 *
 * RAC2 uses canonical software-double calls and its measured constant storage.
 */
#include "common.h"
extern double func_00122A40(double, double);
extern int func_00123028(double, double);
extern const double D_0013A3E8[];

typedef union {
    double value;
    long long bits;
    struct { unsigned int low; int high; } word;
} FloorDouble;

double func_00117650(double value)
{
    FloorDouble input, output;
    long long bits;
    int high, low, exponent;
    unsigned int mask, carry;
    input.value = value;
    bits = input.bits;
    high = (int)(bits >> 32);
    low = (int)bits;
    exponent = ((high >> 20) & 0x7ff) - 0x3ff;
    if (exponent < 20) {
        if (exponent < 0) {
            if (func_00123028(func_00122A40(value, D_0013A3E8[0]), 0.0) > 0) {
                if (high >= 0) high = low = 0;
                else if (((high & 0x7fffffff) | low) != 0) {
                    high = 0xbff00000;
                    low = 0;
                }
            }
        } else {
            mask = 0x000fffff >> exponent;
            if (((high & mask) | low) == 0) return value;
            if (func_00123028(func_00122A40(value, D_0013A3E8[0]), 0.0) > 0) {
                if (high < 0) high += 0x00100000 >> exponent;
                high &= ~mask;
                low = 0;
            }
        }
    } else if (exponent > 51) {
        if (exponent == 0x400) return func_00122A40(value, value);
        return value;
    } else {
        mask = 0xffffffffu >> (exponent - 20);
        if (((unsigned int)low & mask) == 0) return value;
        if (func_00123028(func_00122A40(value, D_0013A3E8[0]), 0.0) > 0) {
            if (high < 0) {
                if (exponent == 20) high++;
                else {
                    carry = (unsigned int)low + (1 << (52 - exponent));
                    if (carry < (unsigned int)low) high++;
                    low = carry;
                }
            }
            low &= ~mask;
        }
    }
    output.word.high = high;
    output.word.low = low;
    return output.value;
}
