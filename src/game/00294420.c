#include "common.h"


struct Slot { int w; int rest[4]; };
struct Table1 { char pad[19264]; struct Slot slots[48]; };
struct Table2 { char pad[52]; int slots[4]; };
extern struct Table1 g_copy_setup_data;
extern struct Table2 g_load_slots;
extern int load_is_class_cached(int);
extern void load_class_into_cache_slot(int, int);

typedef struct { char pad[20]; int value; char rest[200]; } CacheRecord;
extern CacheRecord g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[0x22C8]; int cur; char pad2[0x22E4 - 0x22CC]; int primary; } CacheHero;
extern CacheHero g_hero_state;
extern short g_sequence_active_flag;
extern int g_menu_choice_table __attribute__((sda));
extern int g_current_item_slot __attribute__((sda));

/* Loads the given item into a cache slot that the hero is not using right now. */
void LoadClassIntoFreeCacheSlot(int value)
{
    int primary_value, second_value, i, slot_a, slot_b;

    if (load_is_class_cached(value))
        return;
    if (g_sequence_active_flag)
        return;
    i = 0;
    {
        CacheHero *hero = &g_hero_state;
        int primary_index = hero->primary;
        int second_index = g_menu_choice_table;
        CacheRecord *rec = &g_weapon_table[g_item_slot_to_record[primary_index]];
        CacheRecord *rec2 = &g_weapon_table[g_item_slot_to_record[second_index]];

        primary_value = rec->value;
        second_value = rec2->value;
    }
    if (second_value == primary_value) {
        CacheRecord *rec = &g_weapon_table[g_item_slot_to_record[g_current_item_slot]];

        second_value = rec->value;
    }
    slot_b = -1;
    if (primary_value == value)
        primary_value = -1;
    if (second_value == value)
        second_value = -1;
    slot_a = -1;
    for (; i < 3; i++) {
        struct Table2 *cache = &g_load_slots;
        /* A cache slot may be -1. Its word belongs to the preceding part of
           the complete table owner, not to slots[-1]. */
        int slot_value = *(int *)((char *)&g_copy_setup_data + (0x4B40 + cache->slots[i] * 20));

        if (primary_value == slot_value)
            slot_a = i;
        if (second_value == slot_value)
            slot_b = i;
    }
    for (i = 0; i == slot_a || i == slot_b; i++)
        ;
    {
        CacheHero *hero = &g_hero_state;
        int cur = hero->cur;

        if (cur) {
            struct Table2 *cache = &g_load_slots;
            int slot_id = cache->slots[i];

            if (slot_id != -1) {
                struct Table1 *toc = &g_copy_setup_data;
                CacheRecord *rec = &g_weapon_table[g_item_slot_to_record[cur]];

                if (rec->value == toc->slots[slot_id].w)
                    hero->cur = 0;
            }
        }
    }
    load_class_into_cache_slot(value, i);
}
