/* Public newlib libm/math/s_floor.c, fdlibm 5.1 (1993-09-24).
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

/* fdlibm's INSERT_WORDS writes each half through the shape union. The
 * game's code keeps both masks, so its compiler must have held them as
 * CONST_DOUBLEs, which combine leaves alone. This cc1 has a 64-bit
 * HOST_WIDE_INT, so combine tries
 * the high mask's load with `iw |= hi` and `iw &= msw_mask`, takes iw's known
 * bits from the insn before the earliest of the three, and deletes both masks
 * if that insn is `iw &= lsw_mask`. The union's bit-field stores always put it
 * there, so the stores are written out with both masks loaded first, which
 * moves the high mask's load ahead of `iw &= lsw_mask`.
 * `iw` is uninitialised like the union it stands for: each store keeps the
 * other half and both halves get written, so no unset bit reaches the result. */
typedef union {
    double value;
    unsigned long long word;
} ieee_double_word_type;

#define INSERT_WORDS(d,ix0,ix1)					\
do {								\
  ieee_double_word_type iw_u;					\
  unsigned long long iw, lo;					\
  unsigned long long hi = (unsigned long long)(u32)(ix0) << 32;	\
  unsigned long long lsw_mask = 0x00000000ffffffffULL;		\
  unsigned long long msw_mask = 0xffffffff00000000ULL;		\
  iw &= lsw_mask;						\
  iw |= hi;							\
  lo = (u32)(ix1);						\
  iw &= msw_mask;						\
  iw |= lo;							\
  iw_u.word = iw;						\
  (d) = iw_u.value;						\
} while (0)

static const double huge = 1.0e300;

double func_00117650(double x)
{
	s32 i0,i1,j0;
	u32 i,j;
	EXTRACT_WORDS(i0,i1,x);
	j0 = ((i0>>20)&0x7ff)-0x3ff;
	if(j0<20) {
	    if(j0<0) { 	/* raise inexact if x != 0 */
		if(huge+x>0.0) {/* return 0*sign(x) if |x|<1 */
		    if(i0>=0) {i0=i1=0;}
		    else if(((i0&0x7fffffff)|i1)!=0)
			{ i0=0xbff00000;i1=0;}
		}
	    } else {
		i = (0x000fffff)>>j0;
		if(((i0&i)|i1)==0) return x; /* x is integral */
		if(huge+x>0.0) {	/* raise inexact flag */
		    if(i0<0) i0 += (0x00100000)>>j0;
		    i0 &= (~i); i1=0;
		}
	    }
	} else if (j0>51) {
	    if(j0==0x400) return x+x;	/* inf or NaN */
	    else return x;		/* x is integral */
	} else {
	    i = ((u32)(0xffffffff))>>(j0-20);
	    if((i1&i)==0) return x;	/* x is integral */
	    if(huge+x>0.0) { 		/* raise inexact flag */
		if(i0<0) {
		    if(j0==20) i0+=1;
		    else {
			j = i1+(1<<(52-j0));
			if(j<i1) i0 +=1 ; 	/* got a carry */
			i1=j;
		    }
		}
		i1 &= (~i);
	    }
	}
	INSERT_WORDS(x,i0,i1);
	return x;
}
