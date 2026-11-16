#include "include_asm.h"

#include "common.h"
extern s32 g_trigger_event_list_head __attribute__((sda));
extern u8 g_trigger_event_flags __attribute__((nosda));
extern s32 g_trigger_event_flag __attribute__((sda));
extern void moby_set_state(u8 *, s32, s32);
extern s32 snd_play_from_global_bank(s32, s32, void *);
extern void value_set_entry_by_index_pal(s32, s32);

void moby_wait_no_active_trigger_event_pal(s32 a0)
{
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(u8 *)(a0 + 0x30) = 0xFF;
        moby_set_state((u8 *)a0, 1, -1);
        break;
    case 1: {
        s32 found = 0;
        s32 node = g_trigger_event_list_head;

        while (node != 0) {
            if (*(s16 *)(node + 0xAA) == 0xD3D) {
                if (*(u8 *)(node + 0x20) != 3)
                    found = 1;
            }
            node = *(s32 *)(node + 0x28);
        }
        if (found != 0)
            break;
        if (g_trigger_event_flags == 0) {
            g_trigger_event_flags = 1;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index_pal(0x1233, -1);
            g_trigger_event_flag = 1;
        }
        break;
    }
    }
}
