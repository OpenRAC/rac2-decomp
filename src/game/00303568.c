#include "common.h"
extern float D_00222AE0[][4];
extern float func_002A7878(float, float);
extern float func_00283CB8(float);
void func_00303568(char *obj, float *out)
{
    char *rec = *(char **)(obj + 0x68);
    float x = func_002A7878(0.0f, 6.99f);
    int ix = (int)x;
    float y = func_002A7878(0.0f, 6.99f);
    int iy = (int)y;
    int base = *(int *)(rec + 0x40) * 64;
    int index = base + iy * 8 + ix;
    float f, dx, dy;
    out[0] = D_00222AE0[index][0];
    out[1] = D_00222AE0[index][1];
    f = FloatFraction(x);
    dx = D_00222AE0[index + 1][0] - D_00222AE0[index][0];
    dy = D_00222AE0[index + 1][1] - D_00222AE0[index][1];
    out[0] += dx * f;
    out[1] += dy * f;
    f = FloatFraction(y);
    dx = D_00222AE0[base + (iy + 1) * 8 + ix][0] - D_00222AE0[index][0];
    dy = D_00222AE0[base + (iy + 1) * 8 + ix][1] - D_00222AE0[index][1];
    out[0] += dx * f;
    out[1] += dy * f;
    out[2] = D_00222AE0[index][2];
    out[3] = 1.0f;
}
