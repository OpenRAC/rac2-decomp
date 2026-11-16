#include "include_asm.h"
#include "names.h"
typedef signed int s32;

extern s32 g_beam_slot_state[];
extern s32 g_beam_start_light_ids[];
extern s32 g_beam_end_light_ids[];
extern s32 g_beam_slot_key[];
extern void gfx_free_point_light(s32 slotKey);

/* Releases a slot in a table of three when it belongs to the given key, and lets go of its two handles. */
/* Frees the one of the three slots whose 0x1B3A30 word still names A0. */
s32 slot_release_by_key(s32 slotKey)
{
    s32 *pHandleA, *pHandleB, *pActive, *pOwner;
    s32 i;
    s32 handle;
    i = 0;
    pActive = g_beam_slot_state;
    pHandleA = g_beam_start_light_ids;
    pHandleB = g_beam_end_light_ids;
    pOwner = g_beam_slot_key;
    for (; i < 3; i++) {
        if (*pOwner == slotKey) {
            handle = *pHandleA;
            *pActive = 0;
            *pOwner = 0;
            if (handle != -1) {
                gfx_free_point_light(handle);
                *pHandleA = -1;
            }
            handle = *pHandleB;
            if (handle != -1) {
                gfx_free_point_light(handle);
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

