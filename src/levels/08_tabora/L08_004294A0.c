#include "common.h"

extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;
extern char g_beam_targets[] MACRO_ADDR;
extern char g_slot_pane_matrices[];

extern void mem_fast_helper_c(void *a, void *b, s32 c);

/* Transitions the slot matching the key (1 -> 2, 4 -> 3), copying the caller's
   transform and target vector into its per-slot storage. */
s32 TransitionTaboraSlot(s32 key, void *transform, char *target)
{
    s32 i;
    for (i = 0; i < 3; i++) {
        if (key == g_beam_slot_key[i]) {
            s32 state = g_beam_slot_state[i];
            if (state == 1) g_beam_slot_state[i] = 2;
            else if (state == 4) g_beam_slot_state[i] = 3;
            mem_fast_helper_c(g_slot_pane_matrices + i * 0x40, transform, 0x40);
            qcopy(g_beam_targets + i * 0x10, target);
            return 1;
        }
    }
    return 0;
}
