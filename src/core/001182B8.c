/* Public newlib libm/math/e_log10.c, fdlibm 5.1 (1993-09-24).
 * The scoped word macros are fdlibm.h's original little-endian forms.
 * Native double expressions retain the compiler's soft-float lowering.
 */

/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */

#include "common.h"

typedef union {
    double value;
    struct {
        u32 lsw;
        u32 msw;
    } parts;
} ieee_double_shape_type;

#define EXTRACT_WORDS(ix0,ix1,d)				\
do {								\
  ieee_double_shape_type ew_u;					\
  ew_u.value = (d);						\
  (ix0) = ew_u.parts.msw;					\
  (ix1) = ew_u.parts.lsw;					\
} while (0)

#define GET_HIGH_WORD(i,d)					\
do {								\
  ieee_double_shape_type gh_u;					\
  gh_u.value = (d);						\
  (i) = gh_u.parts.msw;						\
} while (0)

#define SET_HIGH_WORD(d,v)					\
do {								\
  ieee_double_shape_type sh_u;					\
  sh_u.value = (d);						\
  sh_u.parts.msw = (v);						\
  (d) = sh_u.value;						\
} while (0)

extern double func_00117CA0(double);

/* The two54 and zero operands are immediate expressions in this module;
 * only these three coefficients occupy its resident constant storage. */
static const double
ivln10 = 4.34294481903251816668e-01, /* 3FDBCB7B 1526E50E */
log10_2hi = 3.01029995663611771306e-01, /* 3FD34413 509F6000 */
log10_2lo = 3.69423907715893078616e-13; /* 3D59FEF3 11F12B36 */

double func_001182B8(double x)
{
	double y,z;
	s32 i,k,hx;
	u32 lx;

	EXTRACT_WORDS(hx,lx,x);

        k=0;
        if (hx < 0x00100000) {                  /* x < 2**-1022  */
            if (((hx&0x7fffffff)|lx)==0)
                return -1.80143985094819840000e+16/0.0; /* log(+-0)=-inf */
            if (hx<0) return (x-x)/0.0;         /* original exception expression */
            k -= 54; x *= 1.80143985094819840000e+16; /* scale subnormal x */
	    GET_HIGH_WORD(hx,x);
        }
	if (hx >= 0x7ff00000) return x+x;
	k += (hx>>20)-1023;
	i  = ((u32)k&0x80000000)>>31;
        hx = (hx&0x000fffff)|((0x3ff-i)<<20);
        y  = (double)(k+i);
	SET_HIGH_WORD(x,hx);
	z  = y*log10_2lo + ivln10*func_00117CA0(x);
	return  z+y*log10_2hi;
}
