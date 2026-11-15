#include "common.h"

/* A unit of its own for -mno-split-addresses (config/cflags.txt): the resident byte is then
   one assembler operand, which the assembler expands to the retail's absolute lui + load
   through the destination register, never in a delay slot. -G0 splits the address into a
   high-part register of its own; the flag would change the other bodies of the old unit. */

extern u8 D_001A7B26;
extern void func_0029F338(void *a0);

/* Marks the object at 0x68 busy and notifies the owner once the 0xBC flag is clear. */
/* Keeps the object around until it is triggered or the level is over, then removes it. */
void func_L01_003D2C38(u8 *moby)
{
    u8 *mobyAlias = moby;

    *(u32 *)(*(u8 **)(mobyAlias + 0x68) + 0x5C) |= 1;
    if (*(u8 *)(mobyAlias + 0xBC) != 0 || D_001A7B26 != 0)
        MarkMobySpawned(mobyAlias);
}
