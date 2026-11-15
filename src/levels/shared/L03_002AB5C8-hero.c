#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef short s16;
extern char D_00189E20[];
extern u8 D_00139568[];
extern char D_L03_00266DA0[];
extern int func_L00_002ADEA0(int);
typedef struct {
    u8 pad[0x28];
    int v;
} WeaponEntry;

/* func_L00_002A4E48 without the 0x1492 fallback: 0x51 or 0. */
/* Looks up a number tied to the hero's current gadget, or gives 0x51 in one special mode and 0 otherwise. */
int func_L03_002AB5C8(char *object)
{
    char *hero = gHeroState;

    if (*(u8 *)(hero + 0x22B4) == 1)
        return 0;
    if (object != 0 && *(u8 *)(hero + 0x22BA) != 0 && *(s16 *)(hero + 0x24EC) == 0) {
        int idx = hero_slot_item_id(0);
        return ((WeaponEntry *)(D_L03_00266DA0 + gItemSlotToRecord[idx] * 224))->v;
    }
    {
        char *heroBlock = gHeroState;
        if (*(int *)(heroBlock + 0x24CC) != 1)
            return 0;
    }
    return 0x51;
}
