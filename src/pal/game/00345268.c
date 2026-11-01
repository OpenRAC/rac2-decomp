#include "include_asm.h"

typedef unsigned char u8;
extern void func_003361A8(u8 *);
extern void func_00336968(u8 *);
extern void func_00336968(u8 *);
extern void func_003427B0(u8 *);
extern void func_003366D0(u8 *);

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_PAL_00345268(u8 *a0) {
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


INCLUDE_ASM("asm/pal/game", func_PAL_003452C8);

INCLUDE_ASM("asm/pal/game", func_PAL_003455B0);

INCLUDE_ASM("asm/pal/game", func_PAL_003455D8);

INCLUDE_ASM("asm/pal/game", func_PAL_003455F8);

INCLUDE_ASM("asm/pal/game", func_PAL_00345618);

INCLUDE_ASM("asm/pal/game", func_PAL_00345620);

typedef int s32;
typedef unsigned int u32;
extern void func_003435B0(u8 *, u32);

void func_PAL_00345628(u8 *a0, u32 a1) {
    if (a1 < 4) *(u32 *)(a0 + 0x2C4) = a1;
    *(s32 *)(a0 + 0x1a0) = 0;
}



INCLUDE_ASM("asm/pal/game", func_PAL_003456B0);

