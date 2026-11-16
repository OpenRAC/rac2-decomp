#include "names.h"
/* func_L00_003B0CE8 (184 bytes, 27 levels): frees slot idx and, in every used slot from
   the cursor up to the first free one, replaces references to it with that slot's own
   number; rebuilds the list when the freed slot was the cursor. */
#include "common.h"

typedef struct { u8 pad0[0xC]; int used; u8 pad10[4]; u8 id[8]; } Slot;
extern Slot g_effect_path_node_table[];
extern u8 g_trail_slot_head __attribute__((sda));
extern u8 g_trail_slot_tail __attribute__((sda));

extern void AdvanceNodeRingCursor();

void node_free_slot(int idx)
{
    u8 c = idx;
    u8 cur;
    int i;

    g_effect_path_node_table[c].used = 0;
    for (cur = g_trail_slot_tail; cur != g_trail_slot_head; cur++) {
        if (g_effect_path_node_table[cur].used != 0) {
            for (i = 0; i < 8; i++) {
                if (g_effect_path_node_table[cur].id[i] == c)
                    g_effect_path_node_table[cur].id[i] = cur;
            }
        }
    }
    if (c == g_trail_slot_tail)
        AdvanceNodeRingCursor();
}
