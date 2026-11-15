#include "common.h"


struct Slot { int w; int rest[4]; };
struct Table1 { char pad[19264]; struct Slot slots[48]; };
struct Table2 { char pad[52]; int slots[4]; };
extern struct Table1 D_0014B540;
extern struct Table2 D_00152CD0;
extern int func_00294630(int);
extern void func_00294398(int, int);

typedef struct { char pad[20]; int value; char rest[200]; } CacheRecord;
extern CacheRecord D_00239BA0[];
extern unsigned char D_00139568[];
typedef struct { char pad[0x22C8]; int cur; char pad2[0x22E4 - 0x22CC]; int primary; } CacheHero;
extern CacheHero D_00189E20;
extern short D_001A63AC;
extern int D_001A7398 __attribute__((sda));
extern int D_001A7A04 __attribute__((sda));

/* Loads the given item into a cache slot that the hero is not using right now. */
void func_00294420(int value)
{
    int primaryValue, secondValue, i, slotA, slotB;

    if (IsClassCached(value))
        return;
    if (D_001A63AC)
        return;
    i = 0;
    {
        CacheHero *hero = &gHeroState;
        int primaryIndex = hero->primary;
        int secondIndex = D_001A7398;
        CacheRecord *rec = &gWeaponTable_00239BA0[gItemSlotToRecord[primaryIndex]];
        CacheRecord *rec2 = &gWeaponTable_00239BA0[gItemSlotToRecord[secondIndex]];

        primaryValue = rec->value;
        secondValue = rec2->value;
    }
    if (secondValue == primaryValue) {
        CacheRecord *rec = &gWeaponTable_00239BA0[gItemSlotToRecord[D_001A7A04]];

        secondValue = rec->value;
    }
    slotB = -1;
    if (primaryValue == value)
        primaryValue = -1;
    if (secondValue == value)
        secondValue = -1;
    slotA = -1;
    for (; i < 3; i++) {
        struct Table2 *cache = &D_00152CD0;
        /* A cache slot may be -1. Its word belongs to the preceding part of
           the complete table owner, not to slots[-1]. */
        int slotValue = *(int *)((char *)&gCopySetupData + (0x4B40 + cache->slots[i] * 20));

        if (primaryValue == slotValue)
            slotA = i;
        if (secondValue == slotValue)
            slotB = i;
    }
    for (i = 0; i == slotA || i == slotB; i++)
        ;
    {
        CacheHero *hero = &gHeroState;
        int cur = hero->cur;

        if (cur) {
            struct Table2 *cache = &D_00152CD0;
            int slotId = cache->slots[i];

            if (slotId != -1) {
                struct Table1 *toc = &gCopySetupData;
                CacheRecord *rec = &gWeaponTable_00239BA0[gItemSlotToRecord[cur]];

                if (rec->value == toc->slots[slotId].w)
                    hero->cur = 0;
            }
        }
    }
    LoadClassIntoCacheSlot(value, i);
}
