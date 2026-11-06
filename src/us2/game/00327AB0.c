#include "include_asm.h"
#include "common.h"

/* func_US2_00327AB0, the USA v2.00 copy of func_00326CB8: the same C, where the
   first axis is negated only while the byte D_US2_001A7A4C is clear. */

extern char D_00189E20_9[];
extern unsigned char D_US2_001A7A4C MACRO_ADDR;
extern float func_00282C88_1(float *buf);
extern float func_00282DF0(float *buf);

void func_US2_00327AB0(char *obj)
{
    float buf[2];
    char *e = *(char **)(obj + 104);
    float a, b, x;

    if (D_US2_001A7A4C != 0) {
        char *d = D_00189E20_9;
        *(float *)(e + 20) = *(float *)(d + 8112);
    } else {
        char *d = D_00189E20_9;
        *(float *)(e + 20) = -*(float *)(d + 8112);
    }
    {
        char *d = D_00189E20_9;
        a = *(float *)(e + 20);
        b = -*(float *)(d + 8116);
    }
    *(float *)(e + 16) = b;

    if (a > 1.0f) {
        *(float *)(e + 20) = 1.0f;
    } else if (a < -1.0f) {
        *(float *)(e + 20) = -1.0f;
    }

    x = *(float *)(e + 16);
    if (x > 1.0f) {
        *(float *)(e + 16) = 1.0f;
    } else if (x < -1.0f) {
        *(float *)(e + 16) = -1.0f;
    }
    func_00282C88_1(buf);
    buf[0] = *(float *)(e + 16);
    buf[1] = *(float *)(e + 20);
    *(float *)(e + 48) = func_00282DF0(buf);
}
