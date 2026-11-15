#include "include_asm.h"
#include "names.h"

/* func_00336F20's two colour tables are 4 and 2 words at $gp (0x001ADAF8, 0x001ADB08 in the
   boot; D_001ADB10 follows them), hence a unit of its own with -G16 and the assembler's -G16. */

extern unsigned char g_item_slot_to_record[];
typedef struct {
    int enabled;
    unsigned char level;
    unsigned char pad05[0x67];
    int cost;
    unsigned char pad70[0x70];
} ItemRow;
extern ItemRow g_weapon_table[];
extern unsigned int g_item_level_colors[4] __attribute__((sda));
extern unsigned int g_item_short_set_colors[2] __attribute__((sda));
extern int menu_count_chain_entries_after_head(int);
extern int flag_is_byte_set(void);

/* Items 12, 14, 17, 18 and 53, which use the two-entry colour table. */
static __inline__ int itemInShortSet(int item)
{
    int found = 0;
    switch (item) { case 12: case 14: case 17: case 18: case 53: found = 1; }
    return found;
}

static __inline__ int itemCountReached(int item)
{
    if (g_weapon_table[g_item_slot_to_record[item]].enabled) {
        int count = menu_count_chain_entries_after_head(item);
        if (count >= 2 || (count == 1 && itemInShortSet(item))) return 1;
    }
    return 0;
}

static __inline__ int itemLevelReached(int item)
{
    if (g_weapon_table[g_item_slot_to_record[item]].enabled) {
        if (g_weapon_table[g_item_slot_to_record[item]].level == 2
            || (g_weapon_table[g_item_slot_to_record[item]].level == 1 && itemInShortSet(item))) return 1;
    }
    return 0;
}

/* Picks the colours for an item: *first and *second default to 0x55F0C070; *value is the
   colour of the item's level (item 16 from level 2 on uses the table from its start). */
void shop_choose_item_colors(int item, unsigned int *first, unsigned int *second, unsigned int *value)
{
    unsigned int colour;

    *first = 0x55F0C070;
    *second = 0x55F0C070;
    if (itemInShortSet(item)) {
        int index = g_item_slot_to_record[item];
        colour = g_item_short_set_colors[g_weapon_table[index].level];
    } else {
        int index = g_item_slot_to_record[item];
        colour = g_item_level_colors[g_weapon_table[index].level];
    }
    *value = colour;
    if (item == 16) {
        if (g_weapon_table[g_item_slot_to_record[16]].level >= 2)
            *value = g_item_level_colors[g_weapon_table[g_item_slot_to_record[16]].level - 2];
    }
    if (g_weapon_table[g_item_slot_to_record[item]].enabled && menu_count_chain_entries_after_head(item) > 0) {
        if (flag_is_byte_set() && itemCountReached(item)) {
            if (itemLevelReached(item)) {
                *first = 0x60664088;
                *second = 0x606600D8;
            }
        } else {
            ItemRow *row = &g_weapon_table[g_item_slot_to_record[item]];
            if (row->level == 0 && row->cost > 0) {
                *first = 0x6049C1FF;
                *second = 0x60001EFF;
            }
        }
    }
}
