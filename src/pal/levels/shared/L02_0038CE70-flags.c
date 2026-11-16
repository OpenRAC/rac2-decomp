#include "include_asm.h"

#include "common.h"
extern int g_current_map_index[] __attribute__((sda));
extern char *g_moby_l02_list_head[] __attribute__((sda));
extern int g_hovering_object_count SDATA(D_L02_001AEC78);
extern int g_frame_l02_counter[] __attribute__((sda));
extern unsigned char g_enemy_count_trigger_low_done __attribute__((nosda));
extern unsigned char g_enemy_count_trigger_high_done __attribute__((nosda));
extern int g_one_shot_flag __attribute__((nosda));
extern void moby_set_state(void *, int, int);
extern int snd_play_from_global_bank(int, int, int);
extern void value_set_entry_by_index_pal(int, int);

void enemy_count_trigger_update_pal(unsigned char *object) {
    int state = object[0x20];
    switch (state) {
    case 2:
        break;
    case 0:
        object[0x30] = 0xFF;
        if (g_current_map_index[0] == 2) {
            char *entry;
            int kind;
            for (entry = g_moby_l02_list_head[0]; entry; entry = *(char **)(entry + 0x28)) {
                kind = *(short *)(entry + 0xAA);
                if ((kind == 0xA9C || kind == 0xD0D || kind == 0xAA4 || kind == 0xE93 || kind == 0x1259) && *(float *)(entry + 0x18) < 400.0f)
                    ++g_hovering_object_count;
            }
        } else if (g_current_map_index[0] == 3) {
            char *entry;
            int kind;
            int n;
            entry = g_moby_l02_list_head[0];
            if (entry) {
                n = g_hovering_object_count;
                do {
                    kind = *(unsigned short *)(entry + 0xAA);
                    if ((unsigned)(kind - 0xF37) < 2 || (short)kind == 0xF3E)
                        ++n;
                    entry = *(char **)(entry + 0x28);
                } while (entry);
                g_hovering_object_count = n;
            }
        }
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (g_current_map_index[0] == 2) {
            if (g_frame_l02_counter[0] == 2) g_hovering_object_count = 0x71;
            if (g_hovering_object_count >= 11 || g_enemy_count_trigger_low_done) return;
            g_enemy_count_trigger_low_done = state;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index_pal(0x1233, -1);
            g_one_shot_flag = state;
        } else if (g_current_map_index[0] == 3) {
            if (g_frame_l02_counter[0] == 2) g_hovering_object_count = 0x70;
            if (g_hovering_object_count >= 12 || g_enemy_count_trigger_high_done) return;
            g_enemy_count_trigger_high_done = state;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index_pal(0x1233, -1);
            g_one_shot_flag = state;
        }
        break;
    }
}
