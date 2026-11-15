#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef short s16;
extern char D_00189E20[];
extern u8 D_00139568[];
extern char D_L00_00262570[];
extern int func_L00_002ADEA0(int);
typedef struct {
    u8 pad[0x28];
    int v;
} WeaponEntry;

/* Returns an id number for the hero's current weapon or form, or 0 when none applies. */
int func_L00_002A4E48(char *useWeapon)
{
    char *hero = gHeroState;

    if (*(u8 *)(hero + 0x22B4) == 1)
        return 0;
    if (useWeapon != 0 && *(u8 *)(hero + 0x22BA) != 0 && *(s16 *)(hero + 0x24EC) == 0) {
        int weaponSlot = hero_slot_item_id(0);
        return ((WeaponEntry *)(gWeaponTable_L00 + gItemSlotToRecord[weaponSlot] * 224))->v;
    }
    useWeapon = gHeroState;
    if (*(int *)(useWeapon + 0x24CC) != 1)
        return *(u8 *)(useWeapon + 0x1492) ? 0x67 : 0;
    return 0x51;
}
