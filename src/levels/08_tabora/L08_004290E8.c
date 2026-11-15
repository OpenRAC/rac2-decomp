#include "common.h"
extern s32 D_L08_001B39A0[] MACRO_ADDR;
extern s32 D_L08_001B3A30[] MACRO_ADDR;
extern void func_L08_00429408(s32 a0);
extern void func_L08_00429560(s32 a0, s32 a1);
extern void func_L08_002F2D10(void (*fn)(void *), void *arg);
extern void func_L08_00429EE8(void *);

/* The spawner's three slots: the first byte of the record says whether the slot is
   empty (0), in use (1) or a finished one (4); a slot whose record is gone is freed. */
void func_L08_004290E8(char *spawner) {
    s32 i;
    s32 k;
    s32 count;
    s32 slotState;

    switch (*(u8 *)(spawner + 0x20)) {
    case 0:
        for (k = 0; k < 3; k++) {
            gBeamSlotState[k] = 0;
            gBeamSlotKey[k] = 0;
        }
        *(u8 *)(spawner + 0x20) = 1;
        *(u8 *)(spawner + 0x30) = 0xFF;
        break;
    case 1:
        count = 0;
        for (i = 0; i < 3; i++) {
            slotState = gBeamSlotState[i];
            if (slotState == 1) {
                if (*(signed char *)(gBeamSlotKey[i] + 0x20) < 0) {
                    gBeamSlotState[i] = 0;
                    gBeamSlotKey[i] = 0;
                }
            } else if (slotState == 4) {
                ReleaseBeamSlot(i);
            } else if (slotState != 0) {
                update_slot_panes_and_effects(gBeamSlotKey[i], i);
                count++;
                gBeamSlotState[i] = 4;
            }
        }
        if (count != 0) {
            QueueDrawCallback(DrawBeamSlots, spawner);
        }
        break;
    }
}
