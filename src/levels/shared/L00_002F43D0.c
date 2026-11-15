#include "common.h"

/* A unit of its own for -mno-split-addresses (config/cflags.txt): the resident byte is then
   one assembler operand, which the assembler expands to the retail's absolute lui + load
   through the destination register, never in a delay slot. -G0 splits the address into a
   high-part register of its own; the flag would change the other bodies of the old unit. */

extern u8 D_001A7A0A;

/* Resident byte, below the level's own region so the same address holds in every program. */
unsigned char level_get_resident_byte(void)
{
    return D_001A7A0A;
}
