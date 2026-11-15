#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef short s16;
extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern char g_weapon_l00_table[];
extern int hero_slot_item_id(int);
typedef struct {
    u8 pad[0x28];
    int v;
} WeaponEntry;

/* Returns an id number for the hero's current weapon or form, or 0 when none applies. */
int hero_get_weapon_or_form_id(char *useWeapon)
{
    char *hero = g_hero_state;

    if (*(u8 *)(hero + 0x22B4) == 1)
        return 0;
    if (useWeapon != 0 && *(u8 *)(hero + 0x22BA) != 0 && *(s16 *)(hero + 0x24EC) == 0) {
        int weaponSlot = hero_slot_item_id(0);
        return ((WeaponEntry *)(g_weapon_l00_table + g_item_slot_to_record[weaponSlot] * 224))->v;
    }
    useWeapon = g_hero_state;
    if (*(int *)(useWeapon + 0x24CC) != 1)
        return *(u8 *)(useWeapon + 0x1492) ? 0x67 : 0;
    return 0x51;
}
