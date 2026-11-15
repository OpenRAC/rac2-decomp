#include "common.h"

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);

void func_L04_0040A090(int n, int (*pts)[2], float (*dirs)[4], float *lens, float *starts, float *total)
{
    float d[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float len;
    int i;
    int j;

    *total = 0.0f;
    for (i = 0; i < n - 1; i = j) {
        j = i + 1;
        a[0] = pts[i][0];
        a[1] = pts[i][1];
        a[2] = 0.0f;
        b[0] = pts[j][0];
        b[1] = pts[j][1];
        b[2] = 0.0f;
        FastVecSub(d, b, a);
        len = FastVecLength(d);
        lens[i] = len;
        starts[i] = *total;
        *total = *total + len;
        FastVecScale(dirs[i], d, 1.0f / len);
    }
}
