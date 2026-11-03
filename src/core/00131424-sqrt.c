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
extern double func_001310C0(double);
extern int func_001313C8(double) __attribute__((const));
extern int func_00131400(SqrtException *);
extern int *func_00115200(void);

double func_00131424(double x)
{
    SqrtException exc;
    double z;

    z = func_001310C0(x);
    if (D_0013BF10 == -1 || func_001313C8(x))
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
            *func_00115200() = 33;
        else if (!func_00131400(&exc))
            *func_00115200() = 33;
        if (exc.err != 0)
            *func_00115200() = exc.err;
        return exc.retval;
    }
    return z;
}
