#include "include_asm.h"

#include "common.h"
extern void func_002AA548(char *, char *, float, float, float, float);
extern int func_L04_0033CB08(char *, char *, int, int, float, float);
extern void func_00282D30(char *, char *, float);

void func_PAL_L06_0045F1F0(char *a0, char *a1, float f, float g, float h)
{
    char buf[16];
    char *q = a1;

    if (*(float *)(*(char **)(a1 + 0x11C)) - 0.3f < *(float *)(a0 + 0x18)) {
        *(float *)(a1 + 0xC8) -= 0.19600002f;
    }
    qcopy(buf, a0 + 0x10);
    func_002AA548(buf + 8, q + 0xC8, *(float *)(q + 0x128), f, g, h);
    if (func_L04_0033CB08(a0, q + 0xC0, 0x400, 0x10, 1.0f, 0.0f) != 0) {
        func_00282D30(q + 0xC0, q + 0xC0, 0.5f);
    }
}

