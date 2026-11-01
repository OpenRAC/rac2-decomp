#include "include_asm.h"

#include "common.h"
extern char *D_L00_001B8E10;
extern char *D_L00_001B8E10;

/* Stores one float and two scaled by an arcsecond-sized constant into the block at +32. */
void func_PAL_L00_00429FC8(float a, float b, float c)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 32;

        *(float *)(r + 44) = a;
        *(float *)(r + 52) = b * 6.981318e-06f;
        *(float *)(r + 56) = c * 6.981318e-06f;
    }
}

