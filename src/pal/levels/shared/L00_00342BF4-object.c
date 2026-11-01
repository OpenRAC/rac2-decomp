#include "include_asm.h"

#include "common.h"
extern int func_00283CF0(float f);
extern int func_00283D38(int a, int b, float f);
extern float func_002A7878(float a, float b);
extern char *func_002B9030(int kind);
extern int func_002A77E0(int a);
extern int func_002A7820(int a, int b);
extern char *D_L00_001FEAF4;

/* Create a type-0x6D object with two vector records and a packed identifier. */
char *func_PAL_L00_003436B0(char *a0, char *a1, int a2, float f)
{
    char *s1 = func_002B9030(0x6D);
    char *s0;
    float f2;

    if (s1) {
        qcopy(s1 + 0x10, a0);
        s0 = s1 + 0x20;
        {
            int value = func_00283CF0(4.0f) + 0x40;
            *(unsigned char *)(s1 + 3) = a2;
            *(unsigned char *)(s1 + 1) = 0;
            *(unsigned char *)(s1 + 9) = value;
        }
        *(unsigned char *)(s1 + 8) = func_002A77E0(0xFF);
        *(unsigned char *)(s1 + 2) = *(unsigned char *)D_L00_001FEAF4;
        *(unsigned short *)(s1 + 0xA) = ((s32)(func_002A7820(5, 0x32)) * 5 + 2) / 6;
        qcopy(s0, a1);
        *(float *)(s1 + 0xC) = f * 525000.0f;
        *(unsigned int *)(s0 + 0x10) = func_002A7820(0x40, 0x80);
        f2 = func_002A7878(0.0f, 0.5f);
        *(unsigned int *)(s1 + 4) = func_00283D38(0x103080, 0, f2) |
                                    (*(unsigned int *)(s0 + 0x10) << 24);
    }
    return s1;
}
