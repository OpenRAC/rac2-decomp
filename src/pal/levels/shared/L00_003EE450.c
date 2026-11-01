#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003EE450);

extern int D_L00_001A8F00 __attribute__((sda));
extern void func_L00_002E54E0(float value);
extern float func_00282C48(float value);

void func_PAL_L00_003EE6E0(char *p)
{
    float v;
    float x;
    float a;
    float b;
    float c;
    int *q;

    if (*(unsigned char *)(p + 0x20) == 0) {
        *(unsigned short *)(p + 0x32) = 0xAF0;
        *(unsigned char *)(p + 0x30) = 0xFF;
        *(unsigned char *)(p + 0x20) = 1;
        func_L00_002E54E0(3000.0f);
    }
    if (*(unsigned char *)(p + 0x20) != 1)
        return;
    if (D_L00_001A8F00 == 2)
        return;

    v = *(float *)(p + 0x14);
    v = v - 2.0000002f;
    *(float *)(p + 0x14) = v;
    x = func_00282C48(v);

    a = 3000.0f - x;
    b = 750.0f - a;
    c = 1.0f - b * (1.0f / 750.0f);
    if (c > 3.0f)
        c = 3.0f;
    if (c < 0.0f)
        c = 0.0f;

    q = *(int **)(p + 0x24);
    *(float *)(p + 0x2C) = *(float *)((char *)q + 0x24) * c;
    if (*(float *)(p + 0x14) <= -3000.0f)
        *(float *)(p + 0x14) = 3000.0f;
}


