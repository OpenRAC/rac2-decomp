#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } GridPoint;
extern float D_00222AE0[][4];
extern int func_002ACBC8(void *, int);
extern int func_002A8A50(void *, void *, int);
int func_00303E20(char *obj, GridPoint *point, int *column, int *row)
{
    char *rec = *(char **)(obj + 0x68);
    GridPoint corners[4];
    int i, j, base;
    float top;
    if (*(int *)(rec + 0x44) == -1)
        return 0;
    if (!IsPointInCuboid(point, *(int *)(rec + 0x44)))
        return 0;
    top = *(float *)(rec + 0x70) + *(float *)(rec + 4);
    if (top + *(float *)(rec + 0x34) < point->f[2])
        return 0;
    if (point->f[2] < top - *(float *)(rec + 0x34) - 1.2f)
        return 0;
    {
        int k;
        float *x = (float *)(rec + 0x50);
        float *y = (float *)(rec + 0x60);
        for (k = 0; k < 4; k++) {
            qcopy_nc(&corners[k], point);
            corners[k].f[0] = x[k];
            corners[k].f[1] = y[k];
        }
    }
    if (func_002A8A50(point, corners, 4))
        return 0;
    base = *(int *)(rec + 0x40) * 64;
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 7; i++) {
            float height;
            int current = base + j * 8 + i;
            int next = base + (j + 1) * 8 + i;
            corners[0].f[0] = D_00222AE0[current][0];
            corners[1].f[0] = D_00222AE0[current + 1][0];
            corners[2].f[0] = D_00222AE0[next + 1][0];
            corners[3].f[0] = D_00222AE0[next][0];
            corners[0].f[1] = D_00222AE0[current][1];
            corners[1].f[1] = D_00222AE0[current + 1][1];
            corners[2].f[1] = D_00222AE0[next + 1][1];
            corners[3].f[1] = D_00222AE0[next][1];
            if (func_002A8A50(point, corners, 4))
                continue;
            height = (D_00222AE0[current][2] +
                      D_00222AE0[current + 1][2] +
                      D_00222AE0[next + 1][2] +
                      D_00222AE0[next][2]) * 0.25f;
            if (point->f[2] <= height && height - 1.2f <= point->f[2]) {
                if (column) *column = i;
                if (row) *row = j;
                return 1;
            }
        }
    }
    return 0;
}
