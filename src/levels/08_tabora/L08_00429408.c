#include "common.h"

extern s32 D_L08_001B39A0[] MACRO_ADDR;
extern s32 D_L08_001B39E0[] MACRO_ADDR;
extern s32 D_L08_001B39F0[] MACRO_ADDR;
extern s32 D_L08_001B3A30[] MACRO_ADDR;
extern void func_00291450(s32);

/* clears slot a0's two state words and releases its two handles (-1 = none) */
void func_L08_00429408(s32 slot)
{
    gBeamSlotState[slot] = 0;
    gBeamSlotKey[slot] = 0;
    if (D_L08_001B39E0[slot] != -1) {
        FreePointLight(D_L08_001B39E0[slot]);
        D_L08_001B39E0[slot] = -1;
    }
    if (D_L08_001B39F0[slot] != -1) {
        FreePointLight(D_L08_001B39F0[slot]);
        D_L08_001B39F0[slot] = -1;
    }
}
