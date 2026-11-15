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
int func_L00_002EA668(int slotIndex, unsigned short valueA, unsigned short valueB, unsigned short valueC,
                      unsigned short valueD, int param14, int param10) {
    Slot_r002EA668 *slot;
    int i;
    if (slotIndex < 0) {
        for (i = 0; i < 0x20; i++) {
            if ((D_L00_001BCC90[i].f1C & 5) == 0)
                slotIndex = i;
        }
        if (slotIndex < 0)
            return -1;
    }
    slot = &D_L00_001BCC90[slotIndex];
    D_L00_001B1998++;
    slot->f20 = valueA;
    slot->f22 = valueB;
    slot->f24 = valueC;
    slot->f26 = valueD;
    slot->f14 = param14;
    slot->f1C = 5;
    slot->f10 = param10;
    return slotIndex;
}
