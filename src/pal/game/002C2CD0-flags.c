#include "include_asm.h"

#include "common.h"
extern void Fa2a84657_FUN_00282D48(float *tmp, char *v, float k);
extern void Fa2a84657_FUN_00282CD8(float *tmp, char *a, char *v);
extern int Fa2a84657_FUN_00282978(char *field);
extern void Fa2a84657_FUN_002B9180(unsigned char *p);

/* func_002C1FC0 is defined in 002BF6F0-g8.c. */

void func_PAL_002C2D90(unsigned char *p)
{
    float tmp[4];
    char *v;
    int n;

    v = (char *)p + 32;
    Fa2a84657_FUN_00282D48(tmp, v, 9.4999998807907104492188e-01f);
    *(float *)(v + 8) = *(float *)(v + 8) + 0.002f;
    Fa2a84657_FUN_00282CD8(tmp, (char *)p + 16, v);

    n = *(int *)(p + 4) + (int)0xFE000000;
    *(int *)(p + 4) = n;
    if (((unsigned)(n & 0xFF000000) - 1) > 0x5EFFFFFFu || Fa2a84657_FUN_00282978((char *)p + 10) != 0) {
        Fa2a84657_FUN_002B9180(p);
    } else {
        float f0;
        float f1;

        f1 = *(float *)(p + 12);
        f0 = 2.1000000000000000000000e+05f - f1;
        f0 = f0 * 7.0000000298023223876953e-02f;
        f1 = f1 + f0;
        *(float *)(p + 12) = f1;
        p[8] = p[8] + 1;
    }
}
