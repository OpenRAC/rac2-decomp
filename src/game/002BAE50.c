#include "include_asm.h"
#include "common.h"

extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern unsigned char **D_001F2550[];

char *func_002BAE50(void *a0, void *a1, unsigned int a2, int a3, int a4, int a5, int a6, int a7)
{
    char *o = func_002B9030(4);
    char *p;
    char *q;

    if (o != 0) {
        qcopy(o + 0x10, a0);
        *(unsigned int *)(o + 4) = a2;
        *(char *)(o + 9) = FloatToInt(4.0f) - 0x60;
        *(char *)(o + 3) = a7 ? 0x48 : 0x44;
        *(char *)(o + 1) = 0;
        *(char *)(o + 2) = **(unsigned char **)D_001F2550;
        *(char *)(o + 8) = func_001163B0();
        *(int *)(o + 0xC) = 0;
        q = o + 0x20;
        qcopy(o + 0x10, a0);
        qcopy(q, a1);
        *(short *)(o + 0xA) = a4;
        *(int *)(q + 0x1C) = a4;
        *(int *)(q + 0x10) = a2;
        *(int *)(q + 0x14) = a3;
        *(short *)(q + 0x18) = a6;
        *(short *)(q + 0x1A) = a5;
    }
    return o;
}
