/* Retained floor reconstruction: game -O2 -G2 -mastra-quad-saves,
 * 472/500 bytes in USA with the current-RAC1/public-fdlibm scoped word
 * extraction and insertion form. This restores retail's ordered save/read
 * sequence, but retains a 0x70 frame versus 0x60 and a shorter final word merge.
 * The earlier named 64-bit view was 468 bytes; direct parameter word access was
 * 448, no-schedule-insns2 was 456, and the SDK profile was 468 with sd/ld saves.
 * Full scoped INSERT_WORDS and removing its unused integer union member tie.
 * No uninitialized accumulator, artificial mask dependency or padding was used.
 * Both output words are assigned before reading the reconstructed double.
 * Next: independent evidence for the original output representation/profile.
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
    struct { unsigned int low; unsigned int high; } word;
} FloorDouble;

double func_00117650(double value)
{
    int high, low, exponent;
    unsigned int mask, carry;
    do {
        FloorDouble words;
        words.value = value;
        high = words.word.high;
        low = words.word.low;
    } while (0);
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
    do {
        FloorDouble words;
        words.word.high = high;
        words.word.low = low;
        value = words.value;
    } while (0);
    return value;
}
