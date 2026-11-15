#include "common.h"


struct Slot { int w; int rest[4]; };
struct Table1 { char pad[19264]; struct Slot slots[48]; };
struct Table2 { char pad[52]; int slots[4]; };
extern struct Table1 g_copy_setup_data;
extern struct Table2 D_00152CD0;
extern int load_is_class_cached(int);
extern void load_class_into_cache_slot(int, int);

typedef struct { char pad[20]; int value; char rest[200]; } CacheRecord;
extern CacheRecord g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[0x22C8]; int cur; char pad2[0x22E4 - 0x22CC]; int primary; } CacheHero;
extern CacheHero g_hero_state;
extern short D_001A63AC;
extern int D_001A7398 __attribute__((sda));
extern int D_001A7A04 __attribute__((sda));

/* Loads the given item into a cache slot that the hero is not using right now. */
void LoadClassIntoFreeCacheSlot(int value)
{
    int primaryValue, secondValue, i, slotA, slotB;

    if (load_is_class_cached(value))
        return;
    if (D_001A63AC)
        return;
    i = 0;
    {
        CacheHero *hero = &g_hero_state;
        int primaryIndex = hero->primary;
        int secondIndex = D_001A7398;
        CacheRecord *rec = &g_weapon_table[g_item_slot_to_record[primaryIndex]];
        CacheRecord *rec2 = &g_weapon_table[g_item_slot_to_record[secondIndex]];

        primaryValue = rec->value;
        secondValue = rec2->value;
    }
    if (secondValue == primaryValue) {
        CacheRecord *rec = &g_weapon_table[g_item_slot_to_record[D_001A7A04]];

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
        int slotValue = *(int *)((char *)&g_copy_setup_data + (0x4B40 + cache->slots[i] * 20));

        if (primaryValue == slotValue)
            slotA = i;
        if (secondValue == slotValue)
            slotB = i;
    }
    for (i = 0; i == slotA || i == slotB; i++)
        ;
    {
        CacheHero *hero = &g_hero_state;
        int cur = hero->cur;

        if (cur) {
            struct Table2 *cache = &D_00152CD0;
            int slotId = cache->slots[i];

            if (slotId != -1) {
                struct Table1 *toc = &g_copy_setup_data;
                CacheRecord *rec = &g_weapon_table[g_item_slot_to_record[cur]];

                if (rec->value == toc->slots[slotId].w)
                    hero->cur = 0;
            }
        }
    }
    load_class_into_cache_slot(value, i);
}
