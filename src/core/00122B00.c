/* Adapted from public GNU GCC fp-bit.c (_fpmul_parts and dpmul, double configuration).
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

extern void func_00122760(double *, DoubleParts *);
extern double func_00122630(DoubleParts *);
extern DoubleParts D_00141810;   /* fp-bit.c's function-static `thenan` */

static __inline__ int double_parts_iszero(DoubleParts *p) { return p->kind == 2; }
static __inline__ int double_parts_isnan(DoubleParts *p) { return p->kind == 0 || p->kind == 1; }
static __inline__ int double_parts_isinf(DoubleParts *p) { return p->kind == 4; }

static __inline__ DoubleParts *dp_mul_parts(DoubleParts *a, DoubleParts *b,
                                            DoubleParts *tmp) {
    unsigned long long low = 0;
    unsigned long long high = 0;

    if (double_parts_isnan(a)) { a->sign = a->sign != b->sign; return a; }
    if (double_parts_isnan(b)) { b->sign = a->sign != b->sign; return b; }
    if (double_parts_isinf(a)) {
        if (double_parts_iszero(b)) return &gDoublePartsNaN;
        a->sign = a->sign != b->sign; return a;
    }
    if (double_parts_isinf(b)) {
        if (double_parts_iszero(a)) return &gDoublePartsNaN;
        b->sign = a->sign != b->sign; return b;
    }
    if (double_parts_iszero(a)) { a->sign = a->sign != b->sign; return a; }
    if (double_parts_iszero(b)) { b->sign = a->sign != b->sign; return b; }

    {
        unsigned long long nl = a->fraction.ll & 0xffffffff;
        unsigned long long nh = a->fraction.ll >> 32;
        unsigned long long ml = b->fraction.ll & 0xffffffff;
        unsigned long long mh = b->fraction.ll >> 32;
        unsigned long long pp_ll = ml * nl;
        unsigned long long pp_hl = mh * nl;
        unsigned long long pp_lh = ml * nh;
        unsigned long long pp_hh = mh * nh;
        unsigned long long res2 = 0;
        unsigned long long res0 = 0;
        unsigned long long ps_hh__ = pp_hl + pp_lh;

        if (ps_hh__ < pp_hl) res2 += 0x100000000LL;
        pp_hl = (ps_hh__ << 32) & 0xffffffff00000000LL;
        res0 = pp_ll + pp_hl;
        if (res0 < pp_ll) res2++;
        res2 += ((ps_hh__ >> 32) & 0xffffffffL) + pp_hh;
        high = res2;
        low = res0;
    }

    tmp->exponent = a->exponent + b->exponent;
    tmp->sign = a->sign != b->sign;
    tmp->exponent += 4;

    while (high >= (unsigned long long)(1LL << 61)) {
        tmp->exponent++;
        if (high & 1) { low >>= 1; low |= 0x8000000000000000LL; }
        high >>= 1;
    }
    while (high < (unsigned long long)(1LL << 60)) {
        tmp->exponent--;
        high <<= 1;
        if (low & 0x8000000000000000LL) high |= 1;
        low <<= 1;
    }
    if ((high & 0xff) == 0x80) {
        if (high & (1 << 8))
            high += 0x7f + 1;
        else if (low)
            high += 0x7f + 1;
    }
    tmp->fraction.ll = high;
    tmp->kind = 3;
    return tmp;
}

/* Multiplies two doubles using software math. */
double func_00122B00(double first, double second) {
    DoubleParts a, b, tmp;
    DoubleParts *res;

    UnpackDouble(&first, &a);
    UnpackDouble(&second, &b);
    res = dp_mul_parts(&a, &b, &tmp);
    return PackDouble(res);
}
