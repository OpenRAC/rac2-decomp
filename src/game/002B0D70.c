#include "common.h"

/* A unit of its own so that the call to func_002B0DB8 goes through its symbol: USA v2.00 has has
   that function as assembly at an address of its own, and a call within one object can only
   reach the object's own copy. */

extern s32 func_002B0D60(void);
extern int func_002B0DB8(void);

/* Counts how many more items than the saved starting amount are filled, keeping the result between 0 and 40. */
int func_002B0D70(void) {
    int count = CountFilledSlotsInTable();
    int diff = count - GetSavedBaselineCount();
    if (diff < 0) diff = 0;
    if (diff > 40) diff = 40;
    return diff;
}
