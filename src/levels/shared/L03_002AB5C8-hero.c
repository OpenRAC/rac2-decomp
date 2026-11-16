#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef short s16;
extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern char g_item_l03_record_table[];
extern int hero_slot_item_id(int);
typedef struct {
    u8 pad[0x28];
    int v;
} WeaponEntry;

/* func_L00_002A4E48 without the 0x1492 fallback: 0x51 or 0. */
/* Looks up a number tied to the hero's current gadget, or gives 0x51 in one special mode and 0 otherwise. */
int hero_get_gadget_value(char *object)
{
    char *hero = g_hero_state;

    if (*(u8 *)(hero + 0x22B4) == 1)
        return 0;
    if (object != 0 && *(u8 *)(hero + 0x22BA) != 0 && *(s16 *)(hero + 0x24EC) == 0) {
        int idx = hero_slot_item_id(0);
        return ((WeaponEntry *)(g_item_l03_record_table + g_item_slot_to_record[idx] * 224))->v;
    }
    {
        char *heroBlock = g_hero_state;
        if (*(int *)(heroBlock + 0x24CC) != 1)
            return 0;
    }
    return 0x51;
}
