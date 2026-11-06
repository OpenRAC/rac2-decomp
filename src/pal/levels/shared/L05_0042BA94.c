#include "include_asm.h"


extern int func_002A77E0(int);

/* func_PAL_L05_0042BC50, the PAL copy of func_L05_00426270: the same C, where the alpha steps take PAL's 50 Hz scale. */
void func_PAL_L05_0042BC50(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    int *q;
    int i;
    int j;

    p = (float *)obj;
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x10) = -1.0f;
    *(float *)(obj + 0x14) = -2.25f;
    *(float *)(obj + 0x18) = 1.25f;
    *(float *)(obj + 0x1C) = 2.5f;
    q = (int *)(obj + 0x20);
    for (j = 0; j < 4; j++) {
        q[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(obj + 0x30) = 2.4f;
    *(float *)(obj + 0x34) = 3.0f;
    *(float *)(obj + 0x3C) = 2.4f;
    *(float *)(obj + 0x38) = 3.0f;
}

