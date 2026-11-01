#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L12_0042C130);


typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001A8FF0 __attribute__((sda));
extern void func_00282978(s32);
extern void func_002AEC48(s32, s32, s32, f32, f32);
extern void func_PAL_002B14F8(s32, s32, s32, s32, f32);

/* func_L12_00424078 is defined in L12_00424078-g8.c. */

/* func_L12_00426C08 is defined in L12_00426C08-g8.c. */

/* func_L12_004277F0 is defined in L12_004277F0-g8.c. */


void func_PAL_L12_0042D258(s32 a0) {
    s32 s1 = a0;
    s32 s0 = *(u32 *)(s1 + 0x68);

    func_00282978(s0 + 0x330);
    func_00282978(s0 + 0x332);
    if (*(u16 *)(s1 + 0x96) <= 0xFFFE)
        *(u16 *)(s1 + 0x96) = *(u16 *)(s1 + 0x96) + 1;
    s0 = s0 + 0x280;
    func_002AEC48(s1, s0, 0, 0.0432f, 0.43200004f);
    func_PAL_002B14F8(s1, s0, 0, 1, 1.8f);
}

