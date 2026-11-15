#include "common.h"

/* Adapted from public newlib libm/math/w_sqrt.c (SSXModding's b595ded snapshot).
 *
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 */
typedef struct {
    int type;
    char *name;
    double arg1, arg2, retval;
    int err;
} SqrtException;

extern int D_0013BF10;
extern char D_0013BF28[];
extern double math_sqrt_double(double);
extern int math_is_finite_double(double) __attribute__((const));
extern int math_handle_sqrt_error(SqrtException *);
extern int *libc_get_state_record(void);

/* math_square root that also sets the error code when given a negative number. */
double math_sqrt_with_errno(double x)
{
    SqrtException exc;
    double z;

    z = math_sqrt_double(x);
    if (D_0013BF10 == -1 || math_is_finite_double(x))
        return z;
    if (x < 0.0) {
        exc.type = 1;
        exc.name = D_0013BF28;
        exc.err = 0;
        exc.arg1 = exc.arg2 = x;
        if (D_0013BF10 == 0)
            exc.retval = 0.0;
        else
            exc.retval = 0.0 / 0.0;
        if (D_0013BF10 == 2)
            *libc_get_state_record() = 33;
        else if (!math_handle_sqrt_error(&exc))
            *libc_get_state_record() = 33;
        if (exc.err != 0)
            *libc_get_state_record() = exc.err;
        return exc.retval;
    }
    return z;
}
