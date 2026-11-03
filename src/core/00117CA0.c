/* Public newlib e_log.c; fdlibm word macros are written out below. */
#include "common.h"

/* libm e_log.c (__ieee754_log), verbatim as newlib carries it
 * (ee/newlib/libm/math/e_log.c):
 *
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 *
 * The do { } while (0) blocks are fdlibm's own EXTRACT_WORDS,
 * GET_HIGH_WORD and SET_HIGH_WORD macros, written out (libm/common/fdlibm.h,
 * little-endian arm), as func_001310C0 (e_sqrt.c) does. */

typedef union {
    f64 value;
    struct {
        u32 lsw;
        u32 msw;
    } parts;
} log_ieee_double_shape_type;

static const f64
ln2_hi  =  6.93147180369123816490e-01,	/* 3fe62e42 fee00000 */
ln2_lo  =  1.90821492927058770002e-10,	/* 3dea39ef 35793c76 */
two54   =  1.80143985094819840000e+16,  /* 43500000 00000000 */
Lg1 = 6.666666666666735130e-01,  /* 3FE55555 55555593 */
Lg2 = 3.999999999940941908e-01,  /* 3FD99999 9997FA04 */
Lg3 = 2.857142874366239149e-01,  /* 3FD24924 94229359 */
Lg4 = 2.222219843214978396e-01,  /* 3FCC71C5 1D8E78AF */
Lg5 = 1.818357216161805012e-01,  /* 3FC74664 96CB03DE */
Lg6 = 1.531383769920937332e-01,  /* 3FC39A09 D078C69F */
Lg7 = 1.479819860511658591e-01;  /* 3FC2F112 DF3E5244 */

static const f64 zero   =  0.0;

f64 func_00117CA0(f64 x) {
	f64 hfsq,f,s,z,R,w,t1,t2,dk;
	s32 k,hx,i,j;
	u32 lx;

	do {
	    log_ieee_double_shape_type ew_u;
	    ew_u.value = (x);
	    (hx) = ew_u.parts.msw;
	    (lx) = ew_u.parts.lsw;
	} while (0);

	k=0;
	if (hx < 0x00100000) {			/* x < 2**-1022  */
	    if (((hx&0x7fffffff)|lx)==0)
		return -two54/zero;		/* log(+-0)=-inf */
	    if (hx<0) return (x-x)/zero;	/* log(-#) = NaN */
	    k -= 54; x *= two54; /* subnormal number, scale up x */
	    do {
		log_ieee_double_shape_type gh_u;
		gh_u.value = (x);
		(hx) = gh_u.parts.msw;
	    } while (0);
	}
	if (hx >= 0x7ff00000) return x+x;
	k += (hx>>20)-1023;
	hx &= 0x000fffff;
	i = (hx+0x95f64)&0x100000;
	do {	/* normalize x or x/2 */
	    log_ieee_double_shape_type sh_u;
	    sh_u.value = (x);
	    sh_u.parts.msw = (hx|(i^0x3ff00000));
	    (x) = sh_u.value;
	} while (0);
	k += (i>>20);
	f = x-1.0;
	if((0x000fffff&(2+hx))<3) {	/* |f| < 2**-20 */
	    if(f==zero) if(k==0) return zero;  else {dk=(double)k;
				 return dk*ln2_hi+dk*ln2_lo;}
	    R = f*f*(0.5-0.33333333333333333*f);
	    if(k==0) return f-R; else {dk=(double)k;
                     return dk*ln2_hi-((R-dk*ln2_lo)-f);}
	}
	s = f/(2.0+f);
	dk = (double)k;
	z = s*s;
	i = hx-0x6147a;
	w = z*z;
	j = 0x6b851-hx;
	t1= w*(Lg2+w*(Lg4+w*Lg6));
	t2= z*(Lg1+w*(Lg3+w*(Lg5+w*Lg7)));
	i |= j;
	R = t2+t1;
	if(i>0) {
	    hfsq=0.5*f*f;
	    if(k==0) return f-(hfsq-s*(hfsq+R)); else
		     return dk*ln2_hi-((hfsq-(s*(hfsq+R)+dk*ln2_lo))-f);
	} else {
	    if(k==0) return f-s*(f-R); else
		     return dk*ln2_hi-((s*(f-R)-dk*ln2_lo)-f);
	}
}
