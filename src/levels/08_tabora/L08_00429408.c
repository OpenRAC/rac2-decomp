#include "common.h"

extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 g_beam_start_light_ids[] MACRO_ADDR;
extern s32 g_beam_end_light_ids[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;
extern void gfx_free_point_light(s32);

/* clears slot a0's two state words and releases its two handles (-1 = none) */
void beam_slot_release(s32 slot)
{
    g_beam_slot_state[slot] = 0;
    g_beam_slot_key[slot] = 0;
    if (g_beam_start_light_ids[slot] != -1) {
        gfx_free_point_light(g_beam_start_light_ids[slot]);
        g_beam_start_light_ids[slot] = -1;
    }
    if (g_beam_end_light_ids[slot] != -1) {
        gfx_free_point_light(g_beam_end_light_ids[slot]);
        g_beam_end_light_ids[slot] = -1;
    }
}
