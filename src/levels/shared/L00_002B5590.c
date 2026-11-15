/* func_L00_002B5590 (92 bytes, 27 levels): copies a vector next to a zero one, has
   func_L00_002D3798 fill the zero one, and combines the two with FastVecDot. The
   zero store is qzero_nc: retail builds the second slot's address again after it. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void func_L00_002D3798(TI128 *, TI128 *, float);
extern void func_00282DB0(TI128 *, TI128 *);

void func_L00_002B5590(TI128 *p)
{
    TI128 buf[2];
    TI128 *a;
    TI128 *b;

    a = &buf[0];
    buf[0] = *p;
    qzero_nc(&buf[1]);
    b = &buf[1];
    func_L00_002D3798(b, b, 1.0f);
    FastVecDot(a, b);
}
