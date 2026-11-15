#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* Blends between two points by the amount t, giving exactly the first or second point at 0 and 1. */
void func_L00_003A1F68(TI128 *out, TI128 *first, TI128 *second, float t)
{
    TI128 local;
    if (t == 0.0f) {
        *out = *first;
    } else if (t == 1.0f) {
        *out = *second;
    } else {
        FastVecSub(&local, second, first);
        FastVecScale(&local, &local, t);
        FastVecAdd(out, first, &local);
    }
}
