#include "names.h"
/* Own unit: the hero block is declared in .data here, which the neighbours in
   L19_002A88C8.c do not share. */
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; } Hero19;
extern char D_00189E20[] __attribute__((section(".data")));
extern unsigned char D_00139568[];
extern unsigned char D_L19_00265870[];
extern int func_L00_002ADEA0(int);

/* the hero's animation id for its current state: 13 in state 4, the 0xE0-byte table entry's
   value for the selected slot when enabled and idle, 81 in mode 1, else 0 */
/* Chooses which animation the hero should play right now. */
int func_L19_002A88C8(int enabled)
{
    unsigned char *entry;

    if (((Hero19 *)gHeroState)->b[0x22B4] == 4)
        return 13;
    if (enabled && ((Hero19 *)gHeroState)->b[0x22BA] && ((Hero19 *)gHeroState)->h[0x24EC / 2] == 0) {
        entry = D_L19_00265870 + gItemSlotToRecord[hero_slot_item_id(0)] * 0xE0;
        return *(int *)(entry + 0x28);
    }
    if (((Hero19 *)gHeroState)->i[0x24CC / 4] == 1)
        return 81;
    return 0;
}
