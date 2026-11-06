#include "include_asm.h"

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_L11_00441978(s32 a0, int a1);
extern void func_00282A60(char *a0, int a1, int a2);
extern void func_PAL_L11_0044EDC0(char *self, TI128 *pos);
extern void func_0029F978(char *a0, int a1, char *a2);
extern void func_002A7A00(void *a0, float f12, float f13);
extern void func_PAL_002B15D8(char *a0, int a1, void *a2, float f12, float f13, float f14,
                              float f15, int a3);
extern void func_PAL_L02_004009A0(char *a0, int a1, int a2);
extern void func_L01_003E9CF8(char *a0, int a1, char *a2);
void func_L11_00449878(char *a0);

/* func_PAL_L11_0044F420, the PAL copy of func_L11_00449970: the same C, where 1/60 and 0.05 become
   0.02 and 0.06 and the object's flag bit 0x1000 (halfword +0x34) is also cleared.
   The moby's death path: clears the spawn flags, hands the last position to the scene
   manager, resets the 0x2B0 rig and leaves the object in its dead state. */
void func_PAL_L11_0044F420(char *a0, int a1, int a2)
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
        func_PAL_L11_0044EDC0(a0, &tmp);
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
        func_002A7A00((char *)&tmp, 0.020000001f, 0.060000002f);
        func_PAL_002B15D8(a0, 0x20, (char *)&tmp, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(u16 *)(a0 + 0x34) &= ~0x1000;
    *(s32 *)(a0 + 0x98) = 0;
    if (a1 == 0)
        func_PAL_L02_004009A0(a0, 0, -1);
    if (a2 == 0)
        func_L01_003E9CF8(a0, 0, (char *)func_L11_00449878);
    else
        func_L11_00449878(a0);
}
