#include "common.h"
extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;
extern void beam_slot_release(s32 a0);
extern void update_slot_panes_and_effects(s32 a0, s32 a1);
extern void gfx_queue_draw_callback(void (*fn)(void *), void *arg);
extern void beam_slots_draw(void *);

/* The spawner's three slots: the first byte of the record says whether the slot is
   empty (0), in use (1) or a finished one (4); a slot whose record is gone is freed. */
void UpdateTaboraSlotStates(char *spawner) {
    s32 i;
    s32 k;
    s32 count;
    s32 slot_state;

    switch (*(u8 *)(spawner + 0x20)) {
    case 0:
        for (k = 0; k < 3; k++) {
            g_beam_slot_state[k] = 0;
            g_beam_slot_key[k] = 0;
        }
        *(u8 *)(spawner + 0x20) = 1;
        *(u8 *)(spawner + 0x30) = 0xFF;
        break;
    case 1:
        count = 0;
        for (i = 0; i < 3; i++) {
            slot_state = g_beam_slot_state[i];
            if (slot_state == 1) {
                if (*(signed char *)(g_beam_slot_key[i] + 0x20) < 0) {
                    g_beam_slot_state[i] = 0;
                    g_beam_slot_key[i] = 0;
                }
            } else if (slot_state == 4) {
                beam_slot_release(i);
            } else if (slot_state != 0) {
                update_slot_panes_and_effects(g_beam_slot_key[i], i);
                count++;
                g_beam_slot_state[i] = 4;
            }
        }
        if (count != 0) {
            gfx_queue_draw_callback(beam_slots_draw, spawner);
        }
        break;
    }
}
