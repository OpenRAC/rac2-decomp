#include "include_asm.h"
#include "common.h"

/* func_US2_00330BE8, the USA v2.00 copy of func_0032FDD0: the same C, where the
   first axis is negated only while the byte D_US2_001A7A4C is clear, as in
   func_US2_00327AB0. */

extern char D_00189E20[];
extern unsigned char D_US2_001A7A4C MACRO_ADDR;
extern void func_00282C88(float *buf);
extern float func_00282DF0(float *buf);
extern float D_001B284C MACRO_ADDR;

void func_US2_00330BE8(char *obj)
{
    float buf[2];
    char *e = *(char **)(obj + 104);
    float a, b, x;

    if (D_US2_001A7A4C != 0) {
        char *d = D_00189E20;
        *(float *)(e + 84) = *(float *)(d + 8112);
    } else {
        char *d = D_00189E20;
        *(float *)(e + 84) = -*(float *)(d + 8112);
    }
    {
        char *d = D_00189E20;
        a = *(float *)(e + 84);
        b = -*(float *)(d + 8116);
    }
    *(float *)(e + 80) = b;

    if (a > 1.0f) {
        *(float *)(e + 84) = 1.0f;
    } else if (a < -1.0f) {
        *(float *)(e + 84) = -1.0f;
    }

    x = *(float *)(e + 80);
    if (x > 1.0f) {
        *(float *)(e + 80) = 1.0f;
    } else if (x < -1.0f) {
        *(float *)(e + 80) = -1.0f;
    }
    func_00282C88(buf);
    buf[0] = *(float *)(e + 80);
    buf[1] = *(float *)(e + 84);
    D_001B284C = func_00282DF0(buf);
}
