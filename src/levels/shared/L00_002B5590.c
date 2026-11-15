/* func_L00_002B5590 (92 bytes, 27 levels): copies a vector next to a zero one, has
   func_L00_002D3798 fill the zero one, and combines the two with func_00282DB0. The
   zero store is qzero_nc: retail builds the second slot's address again after it. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void func_L00_002D3798(TI128 *, TI128 *, float);
extern void func_00282DB0(TI128 *, TI128 *);

/* Compares a vector with the hero forward direction and returns how much it points that way. */
void func_L00_002B5590(TI128 *vec)
{
    TI128 buf[2];
    TI128 *copy;
    TI128 *result;

    copy = &buf[0];
    buf[0] = *vec;
    qzero_nc(&buf[1]);
    result = &buf[1];
    OffsetPointBySideDirection(result, result, 1.0f);
    FastVecDot(copy, result);
}
