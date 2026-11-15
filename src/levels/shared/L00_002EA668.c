/* Claims a slot (the given one, or the last free one of 32), counts it and fills it in.
   Own unit: -frac2-gcse-unsplit-edges lets PRE hoist the table's high half above the
   first branch, as retail has it. */
#include "include_asm.h"
#include "common.h"

typedef struct {
    char pad_00[0x10];
    int f10;
    int f14;
    int f18;
    int f1C;
    unsigned short f20;
    unsigned short f22;
    unsigned short f24;
    unsigned short f26;
    char pad_28[8];
} Slot_r002EA668;

extern Slot_r002EA668 D_L00_001BCC90[];
extern int D_L00_001B1998 MACRO_ADDR;

/* Picks a free slot, fills it in and returns its index, or -1 when all are used. */
int part_l00_alloc_effect_slot(int slot_index, unsigned short value_a, unsigned short value_b, unsigned short value_c,
                      unsigned short value_d, int param14, int param10) {
    Slot_r002EA668 *slot;
    int i;
    if (slot_index < 0) {
        for (i = 0; i < 0x20; i++) {
            if ((D_L00_001BCC90[i].f1C & 5) == 0)
                slot_index = i;
        }
        if (slot_index < 0)
            return -1;
    }
    slot = &D_L00_001BCC90[slot_index];
    D_L00_001B1998++;
    slot->f20 = value_a;
    slot->f22 = value_b;
    slot->f24 = value_c;
    slot->f26 = value_d;
    slot->f14 = param14;
    slot->f1C = 5;
    slot->f10 = param10;
    return slot_index;
}
