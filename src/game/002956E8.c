#include "names.h"
/* Carried from rac3-decomp (src/levels/shared/L01_0042DB28.c, func_L01_0042E1D8): the
   same instructions with rac2's offsets. Returns func_00295680(1) when it is non-zero;
   otherwise picks the first of slots 1-4 whose flags lack 0x1000 and whose word is set
   (5 when none is), hands it to func_00295788(0, slot) and returns it. */

#include "common.h"

typedef struct {
    u8 pad[0x288];
    s32 b[5];
    s32 a[5];
} SlotBlock;

extern SlotBlock g_map_overlay_state;
extern s32 map_find_free_slot(s32);
extern void map_move_cache_slot(s32, s32);

s32 map_select_first_usable_slot(void) {
    s32 slot = map_find_free_slot(1);

    if (slot != 0) {
        return slot;
    }
    for (slot = 1; slot < 5; slot++) {
        if (!(g_map_overlay_state.a[slot] & 0x1000) && g_map_overlay_state.b[slot] != 0) {
            break;
        }
    }
    map_move_cache_slot(0, slot);
    return slot;
}
