#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

extern char D_00189E20[];
extern u8 D_00139568[];
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
int func_L18_002C2D48(char *hero)
{
    char *heroBase = gHeroState;

    if (*(u8 *)(heroBase + 0x22B4) == 4)
        return 0xD;
    if (hero != 0 && *(u8 *)(heroBase + 0x22BA) != 0 && *(s16 *)(heroBase + 0x24EC) == 0) {
        int weaponIndex = func_002CB1C8(0);
        return ((WeaponEntry *)(D_0026BCF0 + gItemSlotToRecord[weaponIndex] * 224))->v;
    }
    hero = gHeroState;
    if (*(int *)(hero + 0x24CC) != 1)
        return *(u8 *)(hero + 0x1492) ? 0x67 : 0;
    return 0x51;
}

/* func_L18_002CA350 is defined in L18_002C2D48-reset.c. */
