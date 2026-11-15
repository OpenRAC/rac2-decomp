/* Carried from rac3-decomp (src/boot_elf/text/39AC98.c, func_0039AC98) with rac2's
   offsets; the source's volatile stores are plain here. Starts loading entry A0 of the
   table in D_0014B540 when the load slot (D_001A9330) is free: records the entry, A1 and
   A2 in the slot, and asks func_002B7BC0 for the entry's second part (with func_00294180
   as the callback) when it has one and A3 is 0, else for its first part (func_00294130).
   0 when the entry is empty or the slot busy. */

#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} LoadEntry;

typedef struct {
    u8 pad[0x4B3C];
    s32 base;
    LoadEntry el[0x30];
} LoadTable;

typedef struct {
    u8 pad[0x34];
    s32 f34[3];
} LoadOwners;

extern LoadTable D_0014B540;
extern LoadOwners D_00152CD0;
extern s32 D_001A9330 __attribute__((sda));
extern s32 D_001A9334[] __attribute__((sda));
extern s32 func_002B7BC0();
extern void func_00294130();
extern void func_00294180();

s32 func_002942A0(s32 entryIndex, s32 owner, s32 dest, s32 firstPartOnly) {
    s32 oldSlot;
    if (gCopySetupData.el[entryIndex].f8 != 0) {
        oldSlot = D_001A9330;
        if (oldSlot == -1) {
            D_001A9330 = entryIndex;
            D_001A9334[0] = owner;
            D_001A9334[1] = dest;
            if (owner >= 0) {
                D_00152CD0.f34[owner] = oldSlot;
            }
            if (gCopySetupData.el[entryIndex].f10 != 0 && firstPartOnly == 0) {
                return StartDiscReadWithCallback(dest, gCopySetupData.el[entryIndex].fC + gCopySetupData.base, gCopySetupData.el[entryIndex].f10, ContinueStreamLoad, &D_001A9330);
            }
            return StartDiscReadWithCallback(dest, gCopySetupData.el[entryIndex].f4 + gCopySetupData.base, gCopySetupData.el[entryIndex].f8, ReleaseClassCacheSlot, &D_001A9330);
        }
        return 0;
    }
    return 0;
}
