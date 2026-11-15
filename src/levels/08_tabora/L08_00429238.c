#include "common.h"
extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 D_L08_001B39B0[] MACRO_ADDR;
extern s32 D_L08_001B39C0[] MACRO_ADDR;
extern s32 D_L08_001B39D0[] MACRO_ADDR;
extern s32 D_L08_001B39E0[] MACRO_ADDR;
extern s32 D_L08_001B39F0[] MACRO_ADDR;
extern s32 D_L08_001B3A00[] MACRO_ADDR;
extern s32 D_L08_001B3A10[] MACRO_ADDR;
extern s32 D_L08_001B3A20[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;

/* Reserves a free beam slot for the given key and sets it up. Returns 0 if all slots are taken. */
s32 ClaimTaboraSlot(s32 key, s32 lightMask, s32 mode) {
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        if (g_beam_slot_key[i] == key) {
            return 1;
        }
    }
    for (j = 0; j < 3; j++) {
        if (g_beam_slot_key[j] == 0) {
            g_beam_slot_key[j] = key;
            D_L08_001B39B0[j] = 0;
            D_L08_001B39C0[j] = 0;
            D_L08_001B39D0[j] = 0;
            D_L08_001B39E0[j] = -1;
            D_L08_001B39F0[j] = -1;
            D_L08_001B3A00[j] = lightMask;
            D_L08_001B3A10[j] = mode;
            D_L08_001B3A20[j] = 0;
            g_beam_slot_state[j] = 1;
            return 1;
        }
    }
    return 0;
}
