#include "include_asm.h"

/* func_US2_L05_00422780, the v2.00 copy of func_L05_004209D8: the same C, where the item strings
   0x31C9 and 0x31DE become 0x305F and 0x3074, and the second arm first calls func_L00_0032B280(10). */

typedef signed int s32;

typedef unsigned char u8;

extern s32 func_003062A0(u8 *a0);

extern void func_002FF9F8(s32 a0);

extern s32 func_0030CBA8(s32 a0);

extern void func_00326198(s32 a0, s32 a1);

extern void func_0037B210(void);

extern void func_L00_0032B280(unsigned int value);

extern void func_L05_0041FC60(u8 *a0);

extern s32 D_L05_001B13E4 __attribute__((sda));

void func_US2_L05_00422780(u8 *a0, s32 a1)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (func_003062A0(p + 0x48) == 0) {
        if (a1 == 1)
            func_00326198(func_0030CBA8(0x305F), -1);
        else if (a1 == 3) {
            func_L00_0032B280(0xA);
            func_00326198(func_0030CBA8(0x3074), -1);
        }
    } else {
        /* The two stores are written against the retail order: 0x48 first. */
        *(s32 *)(p + 0x48) = 0x96;
        *(s32 *)(p + 0x44) = 0x1C20;
        func_002FF9F8(0x1E);
        func_L05_0041FC60(a0);
        func_0037B210();
        D_L05_001B13E4 = 0;
    }
}
