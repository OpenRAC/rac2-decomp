#include "common.h"
typedef struct { unsigned char pad[142]; unsigned short f8E; unsigned char rest[80]; } Entry_262570;
extern Entry_262570 D_L00_00262570[];

extern int func_L00_002D3FB0(int);
extern unsigned char D_00139568[];
extern int D_00139688[];

/* Adds ammo to a weapon slot and caps it at the weapon limit. Returns how much did not fit. */
int func_L00_002D3FB8(int slotIndex, int amount)
{
    int idx = ReturnArgument_L00_2(slotIndex);
    int *slotPtr = &gItemAmmoCounts[idx];
    Entry_262570 *entry;
    int newTotal = *slotPtr + amount;

    *slotPtr = newTotal;
    entry = &gWeaponTable_L00[gItemSlotToRecord[idx]];
    if (entry->f8E != 0) {
        int overflow = newTotal - entry->f8E;
        if (overflow <= 0) return 0;
        *slotPtr = entry->f8E;
        return overflow;
    }
    return 0;
}
