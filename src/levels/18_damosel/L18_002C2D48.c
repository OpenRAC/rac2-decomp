#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern char D_0026BCF0[];
extern int func_002CB1C8(int);

typedef struct {
    u8 pad[0x28];
    int v;
} WeaponEntry;

/* Screen-id lookup: a finished player mode wins, then a running screen whose two
   gates are clear returns the armed item's word, otherwise the health/state pair
   picks the fallback id. */
/* Looks up which id to use for the current screen from the hero state. */
int hero_get_screen_id(char *hero)
{
    char *heroBase = g_hero_state;

    if (*(u8 *)(heroBase + 0x22B4) == 4)
        return 0xD;
    if (hero != 0 && *(u8 *)(heroBase + 0x22BA) != 0 && *(s16 *)(heroBase + 0x24EC) == 0) {
        int weaponIndex = func_002CB1C8(0);
        return ((WeaponEntry *)(D_0026BCF0 + g_item_slot_to_record[weaponIndex] * 224))->v;
    }
    hero = g_hero_state;
    if (*(int *)(hero + 0x24CC) != 1)
        return *(u8 *)(hero + 0x1492) ? 0x67 : 0;
    return 0x51;
}

/* func_L18_002CA350 is defined in L18_002C2D48-reset.c. */
