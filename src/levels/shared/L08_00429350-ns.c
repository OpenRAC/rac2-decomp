#include "include_asm.h"
#include "names.h"
typedef signed int s32;

extern s32 D_L08_001B39A0[];
extern s32 D_L08_001B39E0[];
extern s32 D_L08_001B39F0[];
extern s32 D_L08_001B3A30[];
extern void func_00291450(s32 slotKey);

/* Releases a slot in a table of three when it belongs to the given key, and lets go of its two handles. */
/* Frees the one of the three slots whose 0x1B3A30 word still names A0. */
s32 func_L08_00429350(s32 slotKey)
{
    s32 *pHandleA, *pHandleB, *pActive, *pOwner;
    s32 i;
    s32 handle;
    i = 0;
    pActive = gBeamSlotState;
    pHandleA = D_L08_001B39E0;
    pHandleB = D_L08_001B39F0;
    pOwner = gBeamSlotKey;
    for (; i < 3; i++) {
        if (*pOwner == slotKey) {
            handle = *pHandleA;
            *pActive = 0;
            *pOwner = 0;
            if (handle != -1) {
                FreePointLight(handle);
                *pHandleA = -1;
            }
            handle = *pHandleB;
            if (handle != -1) {
                FreePointLight(handle);
                *pHandleB = -1;
            }
            return 1;
        }
        pHandleB++;
        pHandleA++;
        pActive++;
        pOwner++;
    }
    return 0;
}

