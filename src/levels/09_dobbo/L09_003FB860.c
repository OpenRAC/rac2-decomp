#include "include_asm.h"
#include "common.h"

extern int g_beam_slot_state_2[] MACRO_ADDR;
extern int g_beam_slot_light_handle[] MACRO_ADDR;
extern int g_beam_slot_light_handle_alt[] MACRO_ADDR;
extern int g_sound_slot_ptrs[];
extern void gfx_free_point_light(int);

/* Clears one beam link slot by index and stops its two sounds. */
void beam_slot_clear_by_index(int index)
{
    int handle;

    g_beam_slot_state_2[index] = 0;
    g_sound_slot_ptrs[index * 2] = 0;
    handle = g_beam_slot_light_handle[index];
    *(int *)((u8 *)g_sound_slot_ptrs + index * 8 + 4) = 0;
    if (handle != -1) {
        gfx_free_point_light(handle);
        g_beam_slot_light_handle[index] = -1;
    }
    if (g_beam_slot_light_handle_alt[index] != -1) {
        gfx_free_point_light(g_beam_slot_light_handle_alt[index]);
        g_beam_slot_light_handle_alt[index] = -1;
    }
}
