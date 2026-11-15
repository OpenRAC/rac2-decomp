#include "names.h"
/* Own unit for -mno-split-addresses. Case 2 keeps the three-way dispatch. State 1's two arms
   each make the calls: jump2 merges them from the first jal, which leaves the arguments
   before the completion-byte store and the jal's slot empty. */
#include "common.h"

extern int g_current_map_index[] __attribute__((sda));
extern char *D_L02_001B35A8[] __attribute__((sda));
extern int g_hovering_object_count SDATA(D_L02_001AEC78);
extern int g_frame_l02_counter[] __attribute__((sda));
extern unsigned char D_001A7A6E __attribute__((nosda));
extern unsigned char D_001A7A75 __attribute__((nosda));
extern int D_L02_001A903C __attribute__((nosda));
extern void moby_set_state(void *, int, int);
extern int snd_play_from_global_bank(int, int, int);
extern void value_set_entry_by_index(int, int);

/* Update for the moby class 4815 trigger. It counts certain enemies in the level, then fires a one-time event when the count drops low enough. */
void enemy_count_trigger_update(unsigned char *object) {
    int state = object[0x20];
    switch (state) {
    case 2:
        break;
    case 0:
        object[0x30] = 0xFF;
        if (g_current_map_index[0] == 2) {
            char *entry;
            int kind;
            for (entry = D_L02_001B35A8[0]; entry; entry = *(char **)(entry + 0x28)) {
                kind = *(short *)(entry + 0xAA);
                if ((kind == MOBY_CLASS_SLOT_MACHINE || kind == 0xD0D /* moby class 3341 */ || kind == 0xAA4 /* moby class 2724 */ || kind == 0xE93 /* moby class 3731 */ || kind == 0x1259 /* moby class 4697 */) && *(float *)(entry + 0x18) < 400.0f)
                    ++g_hovering_object_count;
            }
        } else if (g_current_map_index[0] == 3) {
            char *entry;
            int kind;
            int remaining;
            entry = D_L02_001B35A8[0];
            if (entry) {
                remaining = g_hovering_object_count;
                do {
                    kind = *(unsigned short *)(entry + 0xAA);
                    if ((unsigned)(kind - 0xF37 /* moby class 3895 */) < 2 || (short)kind == 0xF3E /* moby class 3902 */)
                        ++remaining;
                    entry = *(char **)(entry + 0x28);
                } while (entry);
                g_hovering_object_count = remaining;
            }
        }
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (g_current_map_index[0] == 2) {
            if (g_frame_l02_counter[0] == 2) g_hovering_object_count = 0x71;
            if (g_hovering_object_count >= 11 || D_001A7A6E) return;
            D_001A7A6E = state;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index(0x1233, -1);
            D_L02_001A903C = state;
        } else if (g_current_map_index[0] == 3) {
            if (g_frame_l02_counter[0] == 2) g_hovering_object_count = 0x70;
            if (g_hovering_object_count >= 12 || D_001A7A75) return;
            D_001A7A75 = state;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index(0x1233, -1);
            D_L02_001A903C = state;
        }
        break;
    }
}
