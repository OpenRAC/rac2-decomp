/* Adapted from public GCC 2.95.2 gcc/config/fp-bit.c, double configuration:
 * https://github.com/gcc-mirror/gcc/blob/17b916df3d859b72736d537f6c2a98b2d76decf8/gcc/config/fp-bit.c
 * RAC2 adaptation updated on 21 October 2026. This distribution uses the GPLv3
 * text in ../../LICENSE under the upstream "or later" permission.
 * The existing retained pack_d body is renamed func_00122630; measured layouts,
 * rounding operations and the local classification helpers are retained.
 * Preserve the original copyright, GPL permissions, exceptions and credits below.
 */
/* This is a software floating point library which can be used instead of
   the floating point routines in libgcc1.c for targets without hardware
   floating point.
 Copyright (C) 1994, 1995, 1996, 1997, 1998 Free Software Foundation, Inc.

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file with other programs, and to distribute
those programs without any restriction coming from the use of this
file.  (The General Public License restrictions do apply in other
respects; for example, they cover modification of the file, and
distribution when not linked into another program.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

/* This implements IEEE 754 format arithmetic, but does not provide a
   mechanism for setting the rounding mode, or for generating or handling
   exceptions.

   The original code by Steve Chamberlain, hacked by Mark Eichin and Jim
   Wilson, all of Cygnus Support.  */

#include "double_parts.h"

typedef float DFtype __attribute__ ((mode (DF)));

typedef unsigned int UHItype __attribute__ ((mode (HI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));

typedef UDItype fractype;
typedef USItype halffractype;
typedef DFtype FLO_type;

typedef enum
{
  CLASS_SNAN,
  CLASS_QNAN,
  CLASS_ZERO,
  CLASS_NUMBER,
  CLASS_INFINITY
} fp_class_type;

typedef DoubleParts fp_number_type;

typedef union
{
  FLO_type value;
  fractype value_raw;

  struct
    {
      fractype fraction:52  __attribute__ ((packed));
      unsigned int exp: 11  __attribute__ ((packed));
      unsigned int sign:1 __attribute__ ((packed));
    }
  bits;
}
FLO_union_type;

static __inline__ int fp_pack_isnan(fp_number_type *number) {
    return number->kind == CLASS_SNAN || number->kind == CLASS_QNAN;
}
static __inline__ int fp_pack_isinf(fp_number_type *number) {
    return number->kind == CLASS_INFINITY;
}
static __inline__ int fp_pack_iszero(fp_number_type *number) {
    return number->kind == CLASS_ZERO;
}

/* Packs an unpacked software float (class, sign, exponent, fraction) into an IEEE double,
   handling NaN, infinity, zero and denormals. */
FLO_type func_00122630(fp_number_type *src) {
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (fp_pack_isnan(src)) {
        exp = 2047;
        fraction |= 0x8000000000000LL;
    } else if (fp_pack_isinf(src)) {
        exp = 2047;
        fraction = 0;
    } else if (fp_pack_iszero(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->exponent < -1022) {
            int shift = -1022 - src->exponent;
            exp = 0;
            if (shift > 56)
                fraction = 0;
            else
                fraction >>= shift;
            fraction >>= 8;
        } else if (src->exponent > 1023) {
            exp = 2047;
            fraction = 0;
        } else {
            exp = src->exponent + 1023;
            if ((fraction & 255) == 128) {
                if (fraction & 256)
                    fraction += 128;
            } else {
                fraction += 127;
            }
            if (fraction >= ((fractype)1 << 61)) {
                fraction >>= 1;
                exp += 1;
            }
            fraction >>= 8;
        }
    }
    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}
