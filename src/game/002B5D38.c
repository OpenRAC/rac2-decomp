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

/* Pushes the object out of a wall or floor it has moved into and returns 1 if it had to move it. */
int func_002B5D38(char *self, char *ctl)
{
    Vec4Q_002B5D38 V;
    Vec4Q_002B5D38 B;
    Vec4Q_002B5D38 Z;
    int probeKind;
    int hit;
    TI128_002B5D38 zero = 0;
    char *dst;

    Z.q = zero;
    Z.f[2] = *(float *)(ctl + 4) + *(float *)ctl;
    B.q = Z.q;
    FastVecAdd(&V, self + 0x10, &B);
    probeKind = (*(unsigned int *)(ctl + 0x38) & 2) ? 6 : 4;
    hit = TestPointAgainstCollision(&V, probeKind, self, *(float *)ctl);
    if (hit != 0) {
        char *g = gCollisionHit;

        dst = ctl + 0x60;
        *(int *)(ctl + 0x84) = *(int *)(g + 0x18);
        qcopy(dst, g + 0x20);
        if (*(int *)(g + 0x18) != 0 && *(int *)(g + 0x1C) < 0) {
            if (*(float *)(g + 0x38) > V.f[2])
                *(float *)(g + 0x38) = V.f[2];
        }
        qcopy(&V, D_001BAFB0);
        FastVecSub(self + 0x10, &V, &B);
        return 1;
    }
    return 0;
}
