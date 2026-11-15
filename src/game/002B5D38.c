/* func_002B5D38: -frac2-zero-ti-por gives retail's por zero vector; the two copies from
 * the resident blocks are qcopy(); the block at 0x1BAF80 is read through one local base,
 * as retail holds it in $a3. */
#include "common.h"

typedef int TI128_002B5D38 __attribute__((mode(TI)));
typedef union { TI128_002B5D38 q; float f[4]; } Vec4Q_002B5D38;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern char D_001BAF80[];
extern char D_001BAFB0[];

int func_002B5D38(char *obj, char *moby)
{
    Vec4Q_002B5D38 V;
    Vec4Q_002B5D38 B;
    Vec4Q_002B5D38 Z;
    int mode;
    int r;
    TI128_002B5D38 zero = 0;
    char *dst;

    Z.q = zero;
    Z.f[2] = *(float *)(moby + 4) + *(float *)moby;
    B.q = Z.q;
    FastVecAdd(&V, obj + 0x10, &B);
    mode = (*(unsigned int *)(moby + 0x38) & 2) ? 6 : 4;
    r = func_00277258(&V, mode, obj, *(float *)moby);
    if (r != 0) {
        char *g = D_001BAF80;

        dst = moby + 0x60;
        *(int *)(moby + 0x84) = *(int *)(g + 0x18);
        qcopy(dst, g + 0x20);
        if (*(int *)(g + 0x18) != 0 && *(int *)(g + 0x1C) < 0) {
            if (*(float *)(g + 0x38) > V.f[2])
                *(float *)(g + 0x38) = V.f[2];
        }
        qcopy(&V, D_001BAFB0);
        FastVecSub(obj + 0x10, &V, &B);
        return 1;
    }
    return 0;
}
