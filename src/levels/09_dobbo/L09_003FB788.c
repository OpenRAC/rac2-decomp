#include "common.h"

extern int g_sound_slot_ptrs[];
extern int g_beam_slot_state_2[] MACRO_ADDR;
extern int g_beam_slot_light_handle[] MACRO_ADDR;
extern int g_beam_slot_light_handle_alt[] MACRO_ADDR;

extern void gfx_free_point_light(int);

/* Frees the beam link slot that holds this id and stops its two sounds. Returns 1 if a slot was freed, else 0. */
int ReleaseRecordSlot(int id) {
    int i;
    for (i = 0; i < 16; i++) {
        if (g_sound_slot_ptrs[i * 2] == id || g_sound_slot_ptrs[i * 2 + 1] == id) {
            g_beam_slot_state_2[i] = 0;
            g_sound_slot_ptrs[i * 2] = 0;
            g_sound_slot_ptrs[i * 2 + 1] = 0;
            if (g_beam_slot_light_handle[i] != -1) {
                gfx_free_point_light(g_beam_slot_light_handle[i]);
                g_beam_slot_light_handle[i] = -1;
            }
            if (g_beam_slot_light_handle_alt[i] != -1) {
                gfx_free_point_light(g_beam_slot_light_handle_alt[i]);
                g_beam_slot_light_handle_alt[i] = -1;
            }
            return 1;
        }
    }
    return 0;
}
