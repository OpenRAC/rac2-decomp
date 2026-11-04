/* Public newlib libm/math/e_fmod.c, fdlibm 5.1 (1993-09-24).
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

static const double one = 1.0, Zero[] = { 0.0, -0.0 };

double func_00117848(double x, double y)
{
	s32 n,hx,hy,hz,ix,iy,sx,i;
	u32 lx,ly,lz;

	EXTRACT_WORDS(hx,lx,x);
	EXTRACT_WORDS(hy,ly,y);
	sx = hx&0x80000000;		/* sign of x */
	hx ^=sx;		/* |x| */
	hy &= 0x7fffffff;	/* |y| */

    /* purge off exception values */
	if((hy|ly)==0||(hx>=0x7ff00000)||	/* y=0,or x not finite */
	  ((hy|((ly|-ly)>>31))>0x7ff00000))	/* or y is NaN */
	    return (x*y)/(x*y);
	if(hx<=hy) {
	    if((hx<hy)||(lx<ly)) return x;	/* |x|<|y| return x */
	    if(lx==ly)
		return Zero[(u32)sx>>31];	/* |x|=|y| return x*0*/
	}

    /* determine ix = ilogb(x) */
	if(hx<0x00100000) {	/* subnormal x */
	    if(hx==0) {
		for (ix = -1043, i=lx; i>0; i<<=1) ix -=1;
	    } else {
		for (ix = -1022,i=(hx<<11); i>0; i<<=1) ix -=1;
	    }
	} else ix = (hx>>20)-1023;

    /* determine iy = ilogb(y) */
	if(hy<0x00100000) {	/* subnormal y */
	    if(hy==0) {
		for (iy = -1043, i=ly; i>0; i<<=1) iy -=1;
	    } else {
		for (iy = -1022,i=(hy<<11); i>0; i<<=1) iy -=1;
	    }
	} else iy = (hy>>20)-1023;

    /* set up {hx,lx}, {hy,ly} and align y to x */
	if(ix >= -1022)
	    hx = 0x00100000|(0x000fffff&hx);
	else {		/* subnormal x, shift x to normal */
	    n = -1022-ix;
	    if(n<=31) {
	        hx = (hx<<n)|(lx>>(32-n));
	        lx <<= n;
	    } else {
		hx = lx<<(n-32);
		lx = 0;
	    }
	}
	if(iy >= -1022)
	    hy = 0x00100000|(0x000fffff&hy);
	else {		/* subnormal y, shift y to normal */
	    n = -1022-iy;
	    if(n<=31) {
	        hy = (hy<<n)|(ly>>(32-n));
	        ly <<= n;
	    } else {
		hy = ly<<(n-32);
		ly = 0;
	    }
	}

    /* fix point fmod */
	n = ix - iy;
	while(n--) {
	    hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
	    if(hz<0){hx = hx+hx+(lx>>31); lx = lx+lx;}
	    else {
		if((hz|lz)==0) 		/* return sign(x)*0 */
		    return Zero[(u32)sx>>31];
		hx = hz+hz+(lz>>31); lx = lz+lz;
	    }
	}
	hz=hx-hy;lz=lx-ly; if(lx<ly) hz -= 1;
	if(hz>=0) {hx=hz;lx=lz;}

    /* convert back to floating value and restore the sign */
	if((hx|lx)==0) 			/* return sign(x)*0 */
	    return Zero[(u32)sx>>31];
	while(hx<0x00100000) {		/* normalize x */
	    hx = hx+hx+(lx>>31); lx = lx+lx;
	    iy -= 1;
	}
	if(iy>= -1022) {	/* normalize output */
	    hx = ((hx-0x00100000)|((iy+1023)<<20));
	    INSERT_WORDS(x,hx|sx,lx);
	} else {		/* subnormal output */
	    n = -1022 - iy;
	    if(n<=20) {
		lx = (lx>>n)|((u32)hx<<(32-n));
		hx >>= n;
	    } else if (n<=31) {
		lx = (hx<<(32-n))|(lx>>n); hx = sx;
	    } else {
		lx = hx>>(n-32); hx = sx;
	    }
	    INSERT_WORDS(x,hx|sx,lx);
	    x *= one;		/* create necessary signal */
	}
	return x;		/* exact output */
}
