#include "include_asm.h"

#include "common.h"
extern float func_00283B98(float f12, float f13);
extern float func_00283198(float f12);
extern int func_00283D38(int a0, int a1, float f12);
extern float func_002A7878(float f12, float f13);
extern void func_002AEC18(void *a0, int a1);
extern float func_00283B98(float, float);
extern float func_002A7878(float low, float high);

void func_PAL_L01_00322798(void *a0, float *a1, int a2) {
    unsigned char *p = (unsigned char *)a0;
    float r;
    int i;

    if (p[0x23] == 0 && a2 == 0)
        return;

    r = func_00283B98(*a1, 0.17453296f);
    *a1 = r;
    r = func_00283198(r);
    i = func_00283D38(0x8000C020, 0x80008000, (r + 0.5f) * 0.5f);
    if (func_002A7878(0.0f, 1.0f) < 0.05f)
        i = func_00283D38(i, 0x8080FFFF, 0.3f);
    func_002AEC18(a0, i);

    if (a2 != 0) {
        if (p[0x23] < 0x3D)
            p[0x23] = p[0x23] + 3;
        else
            p[0x23] = 0x40;
    } else {
        if (p[0x23] >= 4)
            p[0x23] = p[0x23] - 3;
        else
            p[0x23] = 0;
    }
}

