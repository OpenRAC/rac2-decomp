#include "include_asm.h"
#include "common.h"

extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern unsigned char *D_001F26C4;
extern void func_002C7AE8(char *a0);

char *func_002C7970(void *a0, float *a1, int a2, int a3, int a4, int a5, int a6, int a7, float f0, float f1, float f2)
{
    char *p = func_002B9030(0x61);
    char *s;

    if (p != 0) {
        qcopy(p + 0x10, a0);
        *(int *)(p + 4) = (a5 << 24) | a3;
        p[9] = func_00283CF0(4.0f) + 0x40;
        p[1] = 0;
        *(float *)(p + 0xC) = f0;
        p[3] = 0x48;
        p[8] = func_002A77E0(0xFF);
        p[2] = D_001F26C4[a7];
        *(short *)(p + 0xA) = a2;
        s = p + 0x20;
        *(float *)s = a1[0];
        *(float *)(s + 4) = a1[1];
        *(float *)(s + 8) = a1[2];
        *(float *)(s + 0xC) = f2;
        s[0x15] = a4;
        *(float *)(s + 0x10) = (f1 - f0) / func_00283CE0(a2);
        s[0x14] = (a6 - a5) / a2;
        *(void **)(s + 0x1C) = (void *)func_002C7AE8;
    }
    return p;
}
