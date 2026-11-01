#include "include_asm.h"

#include "common.h"
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
extern void Fc3cb9262_FUN_00282CC0(char *a, char *b, char *c);
extern int Fc3cb9262_FUN_00283CF0(float f);
extern int Fc3cb9262_FUN_00282978(char *a);
extern void Fc3cb9262_FUN_002B9180(char *a);

void func_PAL_002C8298(char *a0)
{
    V4_Fc3cb9262 buf;
    char *s0 = a0 + 32;
    float f0;
    float f1;
    float f2;

    f1 = *(float *)(s0 + 16) + 1.0000000474974513053894e-03f;
    f2 = *(float *)(s0 + 8) - 0.0043200003f;
    *(float *)(s0 + 16) = f1;
    *(float *)(s0 + 8) = f2;
    f0 = *(float *)(s0 + 20) * f1 * 2.1000000000000000000000e+05f;
    buf = *(V4_Fc3cb9262 *)s0;
    *(float *)(a0 + 12) = f0;
    Fc3cb9262_FUN_00282CC0(a0 + 16, a0 + 16, (char *)&buf);
    *(int *)(a0 + 4) = (Fc3cb9262_FUN_00283CF0((float)*(short *)(a0 + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + *(unsigned char *)(s0 + 24);
    if (Fc3cb9262_FUN_00282978(a0 + 10) != 0)
        Fc3cb9262_FUN_002B9180(a0);
}
