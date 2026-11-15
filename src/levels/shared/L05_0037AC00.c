#include "names.h"
typedef struct { char pad0[0x14]; int value; char pad18[0x10]; } E;
extern int slot_find_active_in_chain(int);
extern E ref_L05_0037AC00_00[];
/* Returns the value of the active slot of kind 6, or 0. */
int hero_get_shield_value(void) {
    int slot = slot_find_active_in_chain(6);
    if (slot < 0) goto z;
    return ref_L05_0037AC00_00[slot].value;
z:  return 0;
}
