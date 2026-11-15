#include "names.h"
/* func_0028CC98: -G8 unit. The table whose address is taken and the word cleared last
 * are sized sda objects ($gp), the two words at 0x1B18D0 an incomplete sda array (the
 * assembler's macro stores through $at); the stores are in the order whose schedule
 * gives retail's constant registers. */
extern int D_001A8DD8[2] __attribute__((sda));
extern int D_001A8D48 __attribute__((sda));
extern int D_001B18D0[] __attribute__((sda));

/* Resets the round weapon-select menu: eight slots, first page, and the panel size. */
void func_0028CC98(void *menu)
{
    gRadialSlotCount[0] = 8;
    gRadialSlotCount[1] = (int)D_001A8DD8;
    *(short *)((char *)menu + 0x48) = 0;
    *(short *)((char *)menu + 0x4A) = 0;
    *(int *)((char *)menu + 0x58) = 0xD2;
    *(int *)((char *)menu + 0x5C) = 0xC8;
    *(int *)((char *)menu + 0x74) = -2;
    *(int *)((char *)menu + 0x78) = 0x1E;
    gRadialMenuPageIndex = 0;
}
