#include "include_asm.h"

extern void func_002A7750(char *a0, int a1, int a2);
extern int func_002A9640(char *a0, int a1, int a2);
extern void func_PAL_L00_003281C0(char *a0, int a1, float f12);
extern void func_002E5CF8(int a0, int a1, char *a2);
extern void func_L04_00456860(char *a0, int a1, float f12, float f13, float f14, float f15);
extern void func_0029F338(char *a0);

void func_PAL_L04_0045C388(char *s0)
{
    char *s1 = *(char **)(s0 + 0x68);

    switch (*(unsigned char *)(s0 + 0x20)) {
    case 0:
        func_002A7750(s0, 1, -1);
        break;
    case 1:
        if (func_002A9640(s0, 0x4010000, 0) != 0 && *(int *)s1 == 0)
            func_002A7750(s0, 2, -1);
        *(unsigned char *)(s0 + 0xA8) = 0xFF;
        break;
    case 2:
        func_PAL_L00_003281C0(s0, 1, 0.0f);
        func_002E5CF8(0, 0, s0);
        func_L04_00456860(s0, 0x1E, 0.4f, 4.4f, 1.0f, 0.10000001f);
        func_0029F338(s0);
        break;
    }
}

