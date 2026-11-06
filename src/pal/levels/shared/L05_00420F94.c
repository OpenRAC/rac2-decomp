#include "include_asm.h"


#include "common.h"

extern int func_002A77E0(int x);

/* func_PAL_L05_004211C0, the PAL copy of func_L05_0041C410: four random floats, four fixed ones,
   then the fade table at +0x20 scaled to 50 Hz, which turns its loop into a count-up one. */
void func_PAL_L05_004211C0(char *self)
{
    float *p = *(float **)(self + 104);
    float *q = p;
    int *w;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *q = (float)func_002A77E0(255);
        q++;
    }

    p[4] = -1.0000000000000000000000e+00f;
    p[5] = -2.2500000000000000000000e+00f;
    p[6] = 1.2500000000000000000000e+00f;
    p[7] = 2.5000000000000000000000e+00f;

    w = (int *)(p + 8);
    for (j = 0; j < 4; j++)
    {
        w[j] = ((s32)(j * 64 + 63) * 5 + 2) / 6;
    }

    p[12] = 3.0f;
    p[13] = 3.7f;
    p[15] = 3.0f;
    p[14] = 3.7f;
}

