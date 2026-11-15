/* Adapted from public GNU GCC fp-bit.c (_fpadd_parts, double configuration).
 * https://github.com/gcc-mirror/gcc/blob/17b916df3d859b72736d537f6c2a98b2d76decf8/gcc/config/fp-bit.c
 * RAC2 adaptation updated on 21 October 2026. This distribution uses the GPLv3
 * text in ../../LICENSE under the upstream "or later" permission.
 * The record is shared with the existing double packer and its callers.
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
#include "names.h"

typedef float DFtype __attribute__ ((mode (DF)));

typedef int DItype __attribute__ ((mode (DI)));

typedef unsigned int UHItype __attribute__ ((mode (HI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));

typedef UDItype fractype;
typedef USItype halffractype;
typedef DItype intfrac;

#define NGARDS 8
#define FRACBITS 52
#define FRAC_NBITS 64

#define IMPLICIT_1 (1LL << (FRACBITS + NGARDS))
#define IMPLICIT_2 (1LL << (FRACBITS + 1 + NGARDS))

/* Preserve the sticky-bit when shifting fractions to the right.  */
#define LSHIFT(a) { a = (a & 1) | (a >> 1); }

typedef enum
{
  CLASS_SNAN,
  CLASS_QNAN,
  CLASS_ZERO,
  CLASS_NUMBER,
  CLASS_INFINITY
} fp_class_type;

typedef DoubleParts fp_number_type;

extern fp_number_type D_00141810;

static __inline__ fp_number_type *nan_parts(void) {
    return &gDoublePartsNaN;
}

static __inline__ int fp_isnan(fp_number_type *number) {
    return number->kind == CLASS_SNAN || number->kind == CLASS_QNAN;
}

static __inline__ int fp_isinf(fp_number_type *number) {
    return number->kind == CLASS_INFINITY;
}

static __inline__ int fp_iszero(fp_number_type *number) {
    return number->kind == CLASS_ZERO;
}

/* Adds two unpacked doubles and gives back the unpacked sum, handling zero, infinity and not-a-number. */
fp_number_type *func_00122800(fp_number_type *a, fp_number_type *b,
                              fp_number_type *tmp) {
  intfrac tfraction;

  /* Put commonly used fields in local variables.  */
  int a_normal_exp;
  int b_normal_exp;
  fractype a_fraction;
  fractype b_fraction;

  if (fp_isnan (a))
    {
      return a;
    }
  if (fp_isnan (b))
    {
      return b;
    }
  if (fp_isinf (a))
    {
      /* Adding infinities with opposite signs yields a NaN.  */
      if (fp_isinf (b) && a->sign != b->sign)
	return nan_parts ();
      return a;
    }
  if (fp_isinf (b))
    {
      return b;
    }
  if (fp_iszero (b))
    {
      if (fp_iszero (a))
	{
	  *tmp = *a;
	  tmp->sign = a->sign & b->sign;
	  return tmp;
	}
      return a;
    }
  if (fp_iszero (a))
    {
      return b;
    }

  /* Got two numbers. shift the smaller and increment the exponent till
     they're the same */
  {
    int diff;

    a_normal_exp = a->exponent;
    b_normal_exp = b->exponent;
    a_fraction = a->fraction.ll;
    b_fraction = b->fraction.ll;

    diff = a_normal_exp - b_normal_exp;

    if (diff < 0)
      diff = -diff;
    if (diff < FRAC_NBITS)
      {
	/* ??? This does shifts one bit at a time.  Optimize.  */
	while (a_normal_exp > b_normal_exp)
	  {
	    b_normal_exp++;
	    LSHIFT (b_fraction);
	  }
	while (b_normal_exp > a_normal_exp)
	  {
	    a_normal_exp++;
	    LSHIFT (a_fraction);
	  }
      }
    else
      {
	/* Somethings's up.. choose the biggest */
	if (a_normal_exp > b_normal_exp)
	  {
	    b_normal_exp = a_normal_exp;
	    b_fraction = 0;
	  }
	else
	  {
	    a_normal_exp = b_normal_exp;
	    a_fraction = 0;
	  }
      }
  }

  if (a->sign != b->sign)
    {
      if (a->sign)
	{
	  tfraction = -a_fraction + b_fraction;
	}
      else
	{
	  tfraction = a_fraction - b_fraction;
	}
      if (tfraction >= 0)
	{
	  tmp->sign = 0;
	  tmp->exponent = a_normal_exp;
	  tmp->fraction.ll = tfraction;
	}
      else
	{
	  tmp->sign = 1;
	  tmp->exponent = a_normal_exp;
	  tmp->fraction.ll = -tfraction;
	}
      /* and renormalize it */

      while (tmp->fraction.ll < IMPLICIT_1 && tmp->fraction.ll)
	{
	  tmp->fraction.ll <<= 1;
	  tmp->exponent--;
	}
    }
  else
    {
      tmp->sign = a->sign;
      tmp->exponent = a_normal_exp;
      tmp->fraction.ll = a_fraction + b_fraction;
    }
  tmp->kind = CLASS_NUMBER;
  /* Now the fraction is added, we have to shift down to renormalize the
     number */

  if (tmp->fraction.ll >= IMPLICIT_2)
    {
      LSHIFT (tmp->fraction.ll);
      tmp->exponent++;
    }
  return tmp;

}
