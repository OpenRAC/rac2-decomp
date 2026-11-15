#include "common.h"
extern s32 D_L08_001B29DC[] MACRO_ADDR;
extern s32 func_002A8508(s32, s32);
extern s32 func_002A8600(s32 *, s32, s32, s32);

/* Counts the entries in two lists, stores the total, and returns which slot the first found entry is in (-1 if none). */
s32 func_L08_003F6568(s32 unused, u8 *obj)
{
    s32 total;
    s32 found;
    s32 slot = -1;
    total = CountMobysInGroupNotInState(*(s32 *)(obj + 0x134), -1);
    total += CountMobysInGroupNotInState(*(s32 *)(obj + 0x138), -1);
    *(u8 *)(obj + 0x131) = total;
    found = 0;
    if (GetFirstMobyInGroup(&found, *(s32 *)(obj + 0x134), 1, 1) == 0 || GetFirstMobyInGroup(&found, *(s32 *)(obj + 0x138), 1, 1) == 0) {
        slot = (found - D_L08_001B29DC[0]) >> 8;
    }
    return slot;
}
