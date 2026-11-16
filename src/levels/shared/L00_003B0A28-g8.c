#include "names.h"
/* Advances the trailing node-ring cursor to a live slot or the insertion cursor. */
typedef struct { float pos[3]; int active; int pad; unsigned char links[8]; } CursorNode;
extern CursorNode g_effect_path_node_table[];
extern unsigned char g_trail_slot_head __attribute__((sda));
extern unsigned char g_trail_slot_tail __attribute__((sda));
void AdvanceNodeRingCursor(void)
{
    if (g_trail_slot_tail != g_trail_slot_head) {
        g_trail_slot_tail++;
        while (g_effect_path_node_table[g_trail_slot_tail].active == 0 &&
               g_trail_slot_tail != g_trail_slot_head) {
            g_trail_slot_tail++;
        }
    }
}
