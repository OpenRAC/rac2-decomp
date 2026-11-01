#include "include_asm.h"

typedef unsigned char u8;
extern void func_003361A8(u8 *);
extern void func_00336968(u8 *);
extern void func_00336968(u8 *);
extern void func_003427B0(u8 *);
extern void func_003366D0(u8 *);

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_US2_00344110(u8 *a0) {
    func_003361A8(a0);
    func_003361A8(a0 + 76);
    func_003361A8(a0 + 152);
    func_003366D0(a0 + 228);
    func_00336968(a0 + 432);
    func_00336968(a0 + 520);
    func_00336968(a0 + 608);
    func_003427B0(a0 + 712);
    return a0;
}


INCLUDE_ASM("asm/us2/game", func_US2_00344170);

INCLUDE_ASM("asm/us2/game", func_US2_00344458);

INCLUDE_ASM("asm/us2/game", func_US2_00344480);

INCLUDE_ASM("asm/us2/game", func_US2_003444A0);

INCLUDE_ASM("asm/us2/game", func_US2_003444C0);

INCLUDE_ASM("asm/us2/game", func_US2_003444C8);

typedef int s32;
typedef unsigned int u32;
extern void func_003435B0(u8 *, u32);

void func_US2_003444D0(u8 *a0, u32 a1) {
    if (a1 < 4) *(u32 *)(a0 + 0x2C4) = a1;
    *(s32 *)(a0 + 0x1a0) = 0;
}




