/* func_PAL_L12_0042A8E0, the PAL copy of func_L12_00425448: the same C, where scale func_002A7820(D_L12_001B20C0, (s32)D_L12_001B20C4). */
#include "common.h"

/* A unit of its own for -mno-split-addresses (config/cflags.txt): the level word at 0x001B20C4
   is then one assembler operand, which the assembler expands to the retail's absolute lui + load
   through the destination register, never in a delay slot. -G0 splits the address into a
   high-part register of its own; the flag would change the other bodies of the old unit. */

extern u8 *D_L12_001B20C4;
extern int func_00282948(void *);
extern s32 func_002A7820(s32, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));

/* Starts the sub-object's timer when it has finished, then tells the engine to
   advance to mode 1.  The gp word at 0x30D0 needs its `sda` declaration (measured). */
void func_PAL_L12_0042A8E0(u8 *a0) {
    u8 *s0 = *(u8 **)(a0 + 0x68);

    if (func_00282948(s0 + 0x2C0) != 0) {
        *(s32 *)(s0 + 0x2C0) = (((int)(func_002A7820(D_L12_001B20C0, (s32)D_L12_001B20C4)) * 5 + 2) / 6);
        func_002E5CF8(1, 0, a0);
    }
}
