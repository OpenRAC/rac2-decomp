/* func_L05_00421860, in a unit of its own (default flags). Retail's allocation in the two
   counter blocks follows from the two callees returning a value (the unused $v0 at the call)
   and from each block taking the counter table in a pointer of its own. */
#include "common.h"

/* The 0x28-byte slots of D_L05_002A1800 (L05_0037AC80.c names the same fields). */
typedef struct {
    int state, next, pad08[2];
    int limit;
    int value;
    int pad18[4];
} L05Slot40_00421860;

extern L05Slot40_00421860 D_L05_002A1800[];
extern int D_L05_00221D10[] MACRO_ADDR;
extern int func_002ED8A0(int);
extern char *func_L05_0041C118(char *);
extern char *func_L05_0041D498(char *);

/* Runs one of two spawners, depending on whether slot 1 is missing or its value still equals
   its limit, and counts the spawn in the game's counters (its own one and the total). */
void func_L05_00421860(char *object)
{
    int slot = FindLastUsedChainEntry(1);

    if (slot < 0 || D_L05_002A1800[slot].value == D_L05_002A1800[slot].limit) {
        int *counts;

        SpawnHomingPickup(object);
        counts = D_L05_00221D10;
        counts[0x5C / 4]++;
        counts[0x70 / 4]++;
    } else {
        int *counts;

        SpawnHomingPickupVariant(object);
        counts = D_L05_00221D10;
        counts[0x64 / 4]++;
        counts[0x70 / 4]++;
    }
}
