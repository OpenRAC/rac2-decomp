#include "include_asm.h"

#include "common.h"
extern int g_current_map_index[] __attribute__((sda));
extern char *D_L02_001B35A8[] __attribute__((sda));
extern int g_hovering_object_count SDATA(D_L02_001AEC78);
extern int g_frame_l02_counter[] __attribute__((sda));
extern unsigned char D_001A7A6E __attribute__((nosda));
extern unsigned char D_001A7A75 __attribute__((nosda));
extern int D_L02_001A903C __attribute__((nosda));
extern void moby_set_state(void *, int, int);
extern void snd_play_from_global_bank(int, int, int);
extern void func_US2_002B1880(int, int);

void func_US2_L02_0038B458(unsigned char *object) {
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
                if ((kind == 0xA9C || kind == 0xD0D || kind == 0xAA4 || kind == 0xE93 || kind == 0x1259) && *(float *)(entry + 0x18) < 400.0f)
                    ++g_hovering_object_count;
            }
        } else if (g_current_map_index[0] == 3) {
            char *entry;
            int kind;
            int n;
            entry = D_L02_001B35A8[0];
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
            if (g_hovering_object_count >= 11 || D_001A7A6E) return;
            D_001A7A6E = state;
            snd_play_from_global_bank(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L02_001A903C = state;
        } else if (g_current_map_index[0] == 3) {
            if (g_frame_l02_counter[0] == 2) g_hovering_object_count = 0x70;
            if (g_hovering_object_count >= 12 || D_001A7A75) return;
            D_001A7A75 = state;
            snd_play_from_global_bank(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L02_001A903C = state;
        }
        break;
    }
}
