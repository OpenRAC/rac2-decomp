#include "common.h"

extern float func_00283CE0(int);
extern float func_002A7940(void);
extern void func_002ACB48(void *, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);
extern int D_L05_001B0FBC __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);

typedef int TI128 __attribute__((mode(TI)));

void func_L05_00418D68(void *a0, void *a1, int a2, int a3, float f12, float f13, float f14)
{
    TI128 buf[2];
    float step;
    float p;
    float q;
    float scale;
    float angle;
    float dir;
    float len;
    int i;

    dir = f12;
    angle = f13;
    len = f14;
    qcopy(&buf[0], a0);
    step = 1.0f / IntToFloat(a2);
    for (i = 0; i < a2; i++) {
        p = IntToFloat(i) * step;
        scale = dir + (angle - dir) * p;
        q = func_002A7940();
        qcopy(&buf[1], &buf[0]);
        func_002ACB48(&buf[1], len);
        func_00281EB8(&buf[1], D_L05_001B0FBC, a3, 1, scale, 0.0f, q);
        FastVecAdd(&buf[0], &buf[0], a1);
    }
}
