#include "include_asm.h"

#include "common.h"
extern s32 g_beam_slot_state[] MACRO_ADDR;
extern s32 g_beam_slot_key[] MACRO_ADDR;
extern void beam_slot_release(s32 a0);
extern void func_PAL_L08_0042ECD0(s32 a0, s32 a1);
extern void gfx_queue_draw_callback(void (*fn)(void *), void *arg);
extern void func_PAL_L08_0042F658(void *);

/* The spawner's three slots: the first byte of the record says whether the slot is
   empty (0), in use (1) or a finished one (4); a slot whose record is gone is freed. */
void func_PAL_L08_0042E858(char *a0) {
    s32 i;
    s32 k;
    s32 count;
    s32 v;

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        for (k = 0; k < 3; k++) {
            g_beam_slot_state[k] = 0;
            g_beam_slot_key[k] = 0;
        }
        *(u8 *)(a0 + 0x20) = 1;
        *(u8 *)(a0 + 0x30) = 0xFF;
        break;
    case 1:
        count = 0;
        for (i = 0; i < 3; i++) {
            v = g_beam_slot_state[i];
            if (v == 1) {
                if (*(signed char *)(g_beam_slot_key[i] + 0x20) < 0) {
                    g_beam_slot_state[i] = 0;
                    g_beam_slot_key[i] = 0;
                }
            } else if (v == 4) {
                beam_slot_release(i);
            } else if (v != 0) {
                func_PAL_L08_0042ECD0(g_beam_slot_key[i], i);
                count++;
                g_beam_slot_state[i] = 4;
            }
        }
        if (count != 0) {
            gfx_queue_draw_callback(func_PAL_L08_0042F658, a0);
        }
        break;
    }
}

