#include "include_asm.h"

extern void func_00282CF0(float *out, const float *a, const float *b);
extern void func_L02_00333480(char *arg0, char *arg1, void *arg2);

void func_PAL_L02_00335630(char *arg0, char *arg1) {
    int tmp[4];

    func_00282CF0((float *)tmp, (const float *)arg1, (const float *)(arg0 + 0x10));
    func_L02_00333480(arg0, arg1, tmp);
}

