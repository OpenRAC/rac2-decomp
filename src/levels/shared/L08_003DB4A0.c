#include "common.h"

/* A unit of its own for -mno-split-addresses (config/cflags.txt): the resident words is then
   one assembler operand, which the assembler expands to the retail's absolute lui + load
   through the destination register, never in a delay slot. -G0 splits the address into a
   high-part register of its own; the flag would change the other bodies of the old unit. */

extern s32 D_001A79F0;
extern s16 D_001A7A1A;
extern s32 D_001A7A1C;

/* Two values of the resident word 0x001A79F0 select a shared byte or word. */
/* Returns a setting value that depends on the current mode, or 0 for other modes. */
s32 func_L08_003DB4A0(void)
{
    s32 v = gCurrentMapIndex;

    if (v == 8)
        return D_001A7A1A;
    if (v == 0x13)
        return D_001A7A1C;
    return 0;
}
