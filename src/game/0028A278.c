#include "include_asm.h"
#include "names.h"

extern int D_001A79F8;
extern int D_001B1948;
extern int D_001B194C;
extern int D_001B1950;
extern int D_001B1954;
extern int D_001B1958;
extern int D_001B1928[];
extern void func_0029CBA8(int value);

/* Initialize the pair of handles, then clear both sixteen-byte entries. */
/* Resets the bolt counter display to the player's bolt count and clears its two pop-up rows. */
void func_0028A278(void) {
    int boltCount = gPlayerBolts;
    D_001B1948 = boltCount;
    D_001B194C = boltCount;
    D_001B1950 = 0;
    func_0029CBA8((int)&D_001B1948);
    D_001B1958 = 0;
    D_001B1954 = -1;
    {
        int *row = gBoltCounterState;
        int i = 1;
        do {
            *(unsigned short *)((char *)row + 0xE) = 0;
            *row = 0;
            row += 4;
            i--;
        } while (i >= 0);
    }
}
