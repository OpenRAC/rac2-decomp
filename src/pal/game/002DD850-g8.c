#include "include_asm.h"

#include "common.h"
extern int snd_play_from_global_bank(int, int, int);
extern char g_pad_state[];
extern int g_unlock_code_length __attribute__((sda));
extern short g_unlock_code_input[] MACRO_ADDR;
extern u8 g_unlock_code_table[];
extern u8 g_help_unlocked_flags[] MACRO_ADDR;
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern u8 g_game_flag_table[];
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int g_unlock_code_entered MACRO_ADDR;
extern void moby_mark_flag_and_append_to_list(int);
extern void value_set_entry_by_index_pal(int, int);

/* Corresponds to RAC1 process_unlock_code_input. */
void process_unlock_code_input_pal(void) {
    char *pad = g_pad_state;
    int lim0, lim;
    int va, vb, vc;
    int pressed, direction, j, code, index, matched;
    if ((*(long *)(pad + 0x1C0) & 0xF) == 6) {
        pressed = *(int *)(pad + 0x1C4);
        if (!(pressed & 0xF0A0)) return;

        if (g_unlock_code_length >= 20) return;
        if (pressed & 0x1000) direction = 0;
        else if (pressed & 0x4000) direction = 1;
        else if (pressed & 0x8000) direction = 2;
        else if (pressed & 0x2000) direction = 3;
        else direction = (pressed & 0x80) ? 4 : 5;
        g_unlock_code_input[g_unlock_code_length] = direction;
        g_unlock_code_length += 1;
        if (g_unlock_code_length != 20) return;
        code = -1;
        index = 2;
        lim0 = 0x93;
        lim = *(int *)&lim0;
        for (; index < lim; index++) {
            matched = 1;
            for (j = 0; j < 20; j++) {
                if (g_unlock_code_input[j] != g_unlock_code_table[(j * index + index) & 0xff]) {
                    matched = 0;
                    break;
                }
            }
            if (matched) {
                code = index - 2;
                break;
            }
        }
        if (code == -1) return;
        va = code - 55;
        vb = code - 74;
        vc = code - 80;
        if (code < 56) {
            g_item_owned_flags[code] = 1;
            g_help_unlocked_flags[code] = 1;
        } else if ((unsigned)(code - 56) < 18) {
            moby_mark_flag_and_append_to_list(va);
        } else if ((unsigned)vb < 6) {
            g_game_flag_table[vb] = 1;
        } else if ((unsigned)vc < 30) {
            if (!g_item_enabled_flags[vc]) {
                g_item_enabled_flags[vc] = 1;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index_pal(0x1233, -1);
                g_unlock_code_entered = 1;
            }
        }
    } else {
        g_unlock_code_length = 0;
    }
}
