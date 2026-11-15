#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
/* Blends between two points by the amount t, giving exactly the first or second point at 0 and 1. */
void vec_lerp_exact(TI128 *out, TI128 *first, TI128 *second, float t)
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
