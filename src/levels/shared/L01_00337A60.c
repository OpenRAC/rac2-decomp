#include "common.h"

extern s32 func_002A8A50(void *, void *, s32);
extern void func_L01_00311C18(void *, char *, char *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);

/* Copy the edge nearest the point p from a closed polygon of n points, or p itself when inside. */
s32 func_L01_00337A60(void *out, void *p, char *pts, s32 n)
{
    f32 near[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    f32 best = 0.0f;
    f32 len;
    s32 i, j;

    if (func_002A8A50(p, pts, n) == 0) {
        qcopy(out, p);
        return 0;
    }
    for (i = 0; i < n; i++) {
        j = i + 1;
        func_L01_00311C18(near, pts + i * 16, pts + (j % n) * 16, p);
        FastVecSub(d, p, near);
        len = FastVecLength(d);
        if (i == 0 || len < best) {
            best = len;
            qcopy(out, near);
        }
    }
    return 1;
}
