#include "names.h"
typedef struct { char pad0[0x10]; int limit; char pad14[0x14]; } E;
extern int slot_find_active_in_chain(int);
extern E D_002A1800[];
/* Returns the limit of the active slot of kind 6, or 0. */
int hero_get_shield_limit(void) {
    int slot = slot_find_active_in_chain(6);
    if (slot < 0) goto z;
    return D_002A1800[slot].limit;
z:  return 0;
}
