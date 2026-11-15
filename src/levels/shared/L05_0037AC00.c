#include "names.h"
typedef struct { char pad0[0x14]; int value; char pad18[0x10]; } E;
extern int func_L05_0037AA88(int);
extern E ref_L05_0037AC00_00[];
/* Returns the value of the active slot of kind 6, or 0. */
int func_L05_0037AC00(void) {
    int slot = FindActiveSlotInChain(6);
    if (slot < 0) goto z;
    return ref_L05_0037AC00_00[slot].value;
z:  return 0;
}
