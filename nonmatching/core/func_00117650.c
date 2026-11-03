/* Retained third-pass floor reconstruction: 472/500 bytes, 0/1 in each
 * of USA v1.01, USA v2.00 and PAL. Profile:
 * -O2 -G2 -ffunction-sections -mastra-quad-saves
 * -Wa,--r5900-unsigned32-mask=sn
 * Native public newlib arithmetic and its exact scoped EXTRACT_WORDS and
 * INSERT_WORDS remain below. The 0x70 frame still differs from retail's 0x60;
 * the final merge folds away retail's two masked word updates. Its complete
 * emitted constant section is 16 bytes rather than the measured local huge
 * constant alone. The published SET_HIGH_WORD/SET_LOW_WORD alternative also
 * measured 472 bytes, with different scheduling/allocation and no improvement.
 * This is not an exact-code tie. Earlier retained compiler/profile trials and
 * output-union ties were not repeated. Both union words are assigned before
 * its double is read; no undefined accumulator or added stack padding.
 * Reopen with independent evidence for the original word/object lifetime.
 */
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

#define INSERT_WORDS(d,ix0,ix1)					\
do {								\
  ieee_double_shape_type iw_u;					\
  iw_u.parts.msw = (ix0);					\
  iw_u.parts.lsw = (ix1);					\
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
