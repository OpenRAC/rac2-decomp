#include "common.h"
typedef struct { unsigned char pad[142]; unsigned short f8E; unsigned char rest[80]; } Entry_262570;
extern Entry_262570 g_weapon_l00_table[];

extern int math_l00_return_argument_2(int);
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];

/* Adds ammo to a weapon slot and caps it at the weapon limit. Returns how much did not fit. */
int weapon_add_ammo(int slotIndex, int amount)
{
    int idx = math_l00_return_argument_2(slotIndex);
    int *slotPtr = &g_item_ammo_counts[idx];
    Entry_262570 *entry;
    int newTotal = *slotPtr + amount;

    *slotPtr = newTotal;
    entry = &g_weapon_l00_table[g_item_slot_to_record[idx]];
    if (entry->f8E != 0) {
        int overflow = newTotal - entry->f8E;
        if (overflow <= 0) return 0;
        *slotPtr = entry->f8E;
        return overflow;
    }
    return 0;
}
