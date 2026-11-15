#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void *func_0029EFD0(int id);

extern float func_00283248(float x, float y);

extern float func_00282E20(char *a);

extern void func_002A0F48(char *a);

extern char *func_L09_003364E0(char *object, int a1, u32 a2, int a3, float f12, float f13);


char *func_L09_003A06B0(char *object, char *a1, char *a2, float f12)
{
    char *s1 = CreateMoby(0x3A6);
    char *s0;
    float d;

    if (s1 != 0) {
        *(u8 *)(s1 + 0x30) = 0xFF;
        *(u16 *)(s1 + 0x32) = 0xFF;
        *(u8 *)(s1 + 0x31) = 1;
        *(u8 *)(s1 + 0x20) = 0;
        *(u64 *)(s1 + 0x38) = *(u64 *)(object + 0x38);
        qcopy(s1 + 0x10, a2);
        s0 = *(char **)(s1 + 0x68);
        qcopy(s0, a1);
        *(char **)(s0 + 0x3C) = object;
        *(u32 *)(s0 + 0x38) = 0xF0;
        *(float *)(s0 + 0x40) = f12;
        *(float *)(s1 + 0xF8) = func_00283248(*(float *)a1, *(float *)(a1 + 4));
        d = vec_length_xy(a1);
        *(float *)(s1 + 0xF4) =
            -func_00283248(d, *(float *)(a1 + 8));
        *(char **)(s0 + 0x48) =
            func_L09_003364E0(s1, -1, 0xF0208080, 0x60, 0.1f, 0.01f);
        func_002A0F48(s1);
        *(u8 *)(s1 + 0x31) = 0;
        *(u16 *)(s1 + 0x34) |= 1;
    }
    return s1;
}
