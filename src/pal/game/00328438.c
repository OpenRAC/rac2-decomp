#include "include_asm.h"
#include "common.h"

extern char D_00189E20_9[];
extern unsigned char D_PAL_001A7ACC MACRO_ADDR;
extern float func_00282C88_1(float *buf);
extern float func_00282DF0(float *buf);

/* func_PAL_00328438, the PAL copy of func_00326CB8: the same C, where the first value is negated
   only when the byte D_PAL_001A7ACC is zero. */
void func_PAL_00328438(char *obj)
{
    float buf[2];
    char *d;
    char *h;
    char *e = *(char **)(obj + 104);

    if (D_PAL_001A7ACC != 0) {
        d = D_00189E20_9;
        *(float *)(e + 20) = *(float *)(d + 8112);
    } else {
        d = D_00189E20_9;
        *(float *)(e + 20) = -*(float *)(d + 8112);
    }
    h = D_00189E20_9;
    *(float *)(e + 16) = -*(float *)(h + 8116);

    if (*(float *)(e + 20) > 1.0f) {
        *(float *)(e + 20) = 1.0f;
    } else if (*(float *)(e + 20) < -1.0f) {
        *(float *)(e + 20) = -1.0f;
    }

    if (*(float *)(e + 16) > 1.0f) {
        *(float *)(e + 16) = 1.0f;
    } else if (*(float *)(e + 16) < -1.0f) {
        *(float *)(e + 16) = -1.0f;
    }
    func_00282C88_1(buf);
    buf[0] = *(float *)(e + 16);
    buf[1] = *(float *)(e + 20);
    *(float *)(e + 48) = func_00282DF0(buf);
}
