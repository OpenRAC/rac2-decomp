#include "common.h"
#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_L11_00441978(s32 a0, int a1);
extern void func_L11_00449330(char *self, TI128 *pos);
extern void func_L11_00449878(char *a0);
extern void func_00282A60(char *a0, int a1, int a2);
extern void func_0029F978(char *a0, int a1, char *a2);
extern void func_002A7A00(void *a0, float f12, float f13);
extern void func_002B0A68(char *a0, int a1, void *a2, float f12, float f13, float f14,
                        float f15, int a3);
extern void func_L02_003FC248(char *a0, int a1, int a2);
extern void func_L01_003E9CF8(char *a0, int a1, char *a2);

/* func_US2_L11_0044B398, the USA v2.00 copy of func_L11_00449970: the same C, and it also clears
   the 0x1000 flag of the halfword at 0x34. */
void func_US2_L11_0044B398(char *a0, int a1, int a2)
{
    char *s1 = *(char **)(a0 + 0x68);
    char *s0;
    TI128 tmp;
    float f0;

    *(s32 *)(s1 + 0x20) = 0;
    if (*(s16 *)(s1 + 0x366) == 1)
        func_L11_00441978(*(s32 *)(a0 + 0xB8), 0xD98);
    *(s16 *)(s1 + 0x366) = 0;
    *(s32 *)(s1 + 0x350) = 0;
    if (*(s32 *)(s1 + 0x354) != 0) {
        tmp = *(TI128 *)((char *)(long)*(s32 *)(s1 + 0x354) + 0x10);
        func_L11_00449330(a0, &tmp);
    }
    if (*(u8 *)(s1 + 0x2B1) == 0) {
        s0 = s1 + 0x2B0;
        func_00282A60(s0, 0, 0x40);
        func_0029F978(a0, 3, s0);
        f0 = 1.0e-4f;
        *(u8 *)(s1 + 0x2B2) = 1;
        *(f32 *)(s1 + 0x2D8) = f0;
        *(f32 *)(s1 + 0x2D4) = f0;
        *(f32 *)(s1 + 0x2D0) = f0;
        func_002A7A00((char *)&tmp, 1.0f / 60.0f, 0.0500000045f);
        func_002B0A68(a0, 0x20, (char *)&tmp, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(s32 *)(a0 + 0x98) = 0;
    *(u16 *)(a0 + 0x34) &= 0xEFFF;
    if (a1 == 0)
        func_L02_003FC248(a0, 0, -1);
    if (a2 == 0)
        func_L01_003E9CF8(a0, 0, (char *)func_L11_00449878);
    else
        func_L11_00449878(a0);
}
