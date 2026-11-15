#include "common.h"

extern s32 D_L08_001B39A0[] MACRO_ADDR;
extern s32 D_L08_001B3A30[] MACRO_ADDR;
extern char D_L08_001B3A40[] MACRO_ADDR;
extern char D_L08_002603E0[];

extern void func_00282B50(void *a, void *b, s32 c);

/* Transitions the slot matching the key (1 -> 2, 4 -> 3), copying the caller's
   transform and target vector into its per-slot storage. */
s32 func_L08_004294A0(s32 key, void *transform, char *target)
{
    s32 i;
    for (i = 0; i < 3; i++) {
        if (key == gBeamSlotKey[i]) {
            s32 state = gBeamSlotState[i];
            if (state == 1) gBeamSlotState[i] = 2;
            else if (state == 4) gBeamSlotState[i] = 3;
            FastMemoryHelperC(D_L08_002603E0 + i * 0x40, transform, 0x40);
            qcopy(D_L08_001B3A40 + i * 0x10, target);
            return 1;
        }
    }
    return 0;
}
