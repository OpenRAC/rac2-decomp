#include "common.h"

extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 D_L08_001B39E0[] MACRO_ADDR;
extern s32 D_L08_001B39F0[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;
extern void gfx_free_point_light(s32);

/* clears slot a0's two state words and releases its two handles (-1 = none) */
void beam_slot_release(s32 slot)
{
    g_beam_slot_state[slot] = 0;
    g_beam_slot_key[slot] = 0;
    if (D_L08_001B39E0[slot] != -1) {
        gfx_free_point_light(D_L08_001B39E0[slot]);
        D_L08_001B39E0[slot] = -1;
    }
    if (D_L08_001B39F0[slot] != -1) {
        gfx_free_point_light(D_L08_001B39F0[slot]);
        D_L08_001B39F0[slot] = -1;
    }
}
