#include "common.h"
extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 g_beam_wave_angles[] MACRO_ADDR;
extern s32 g_beam_twist_angles[] MACRO_ADDR;
extern s32 g_beam_sway_angles[] MACRO_ADDR;
extern s32 g_beam_start_light_ids[] MACRO_ADDR;
extern s32 g_beam_end_light_ids[] MACRO_ADDR;
extern s32 g_beam_light_masks[] MACRO_ADDR;
extern s32 g_beam_modes[] MACRO_ADDR;
extern s32 g_beam_phases[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;

/* Reserves a free beam slot for the given key and sets it up. Returns 0 if all slots are taken. */
s32 ClaimTaboraSlot(s32 key, s32 light_mask, s32 mode) {
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
            g_beam_wave_angles[j] = 0;
            g_beam_twist_angles[j] = 0;
            g_beam_sway_angles[j] = 0;
            g_beam_start_light_ids[j] = -1;
            g_beam_end_light_ids[j] = -1;
            g_beam_light_masks[j] = light_mask;
            g_beam_modes[j] = mode;
            g_beam_phases[j] = 0;
            g_beam_slot_state[j] = 1;
            return 1;
        }
    }
    return 0;
}
