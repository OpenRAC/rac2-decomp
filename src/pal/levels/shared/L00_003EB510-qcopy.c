#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int size);
extern float func_002A7878(float lo, float hi);
extern int func_002FED90(char *object, int a, float b, float c, float d);
extern void func_002A0F48(char *object);

char *func_PAL_L00_003EB8F0(int a0, TI128 *a1, TI128 *a2)
{
    char *p;
    char *s0;
    float r;
    float lo;
    float hi;

    p = func_0029EFD0(0xC07);
    if (p != 0) {
        short v = 0xFF;

        s0 = *(char **)(p + 0x68);
        *(short *)(p + 0x32) = v;
        *(char *)(p + 0x30) = v;
        *(char *)(p + 0x20) = 0;
        *(TI128 *)(p + 0x10) = *a1;
        *(TI128 *)s0 = *a2;
        *(float *)(p + 0x2C) = 0.01f;
        lo = 0.062831864f;
        hi = 0.12566373f;
        r = func_002A7878(lo, hi);
        *(float *)(s0 + 0x10) = r;
        r = func_002A7878(lo, hi);
        *(float *)(s0 + 0x14) = r;
        *(int *)(s0 + 0x30) = a0;
        *(int *)(s0 + 0x18) = 0;
        *(int *)(s0 + 0x34) = func_002FED90(p, 0, 1.0f, 1.0f, 1.0f);
        func_002A0F48(p);
    }
    return p;
}
