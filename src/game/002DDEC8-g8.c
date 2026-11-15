#include "include_asm.h"
#include "common.h"

/* The resident flag is small data: this file is built with -G8. Its address
   differs from program to program, so it has no level in its name. */
extern int ref_L00_002DF190_00 __attribute__((sda));
extern int snd_play_from_global_bank(int, int, int);

extern char g_pad_state[];
extern int D_001ABCA0 __attribute__((sda));
extern short D_001B2028[] MACRO_ADDR;
extern u8 D_00261C08[];
extern u8 D_001A7B30[] MACRO_ADDR;
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern u8 D_001395B8[];
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_001A8CEC MACRO_ADDR;
extern void moby_mark_flag_and_append_to_list(int);
extern void value_set_entry_by_index(int, int);

/* Corresponds to RAC1 process_unlock_code_input. */
/* Checks the secret button code the player enters. A full 20-press code is matched against the table and unlocks the matching extra. */
void process_unlock_code_input(void) {
    char *pad = g_pad_state;
    int lim0, lim;
    int index55, index74, index80;
    int pressed, direction, j, code, index, matched;
    if ((*(long *)(pad + 0x1C0) & 0xF) == 6) {
        pressed = *(int *)(pad + 0x1C4);
        if (!(pressed & 0xF0A0)) return;

        if (D_001ABCA0 >= 20) return;
        if (pressed & 0x1000) direction = 0;
        else if (pressed & 0x4000) direction = 1;
        else if (pressed & 0x8000) direction = 2;
        else if (pressed & 0x2000) direction = 3;
        else direction = (pressed & 0x80) ? 4 : 5;
        D_001B2028[D_001ABCA0] = direction;
        D_001ABCA0 += 1;
        if (D_001ABCA0 != 20) return;
        code = -1;
        index = 2;
        lim0 = 0x93;
        lim = *(int *)&lim0;
        for (; index < lim; index++) {
            matched = 1;
            for (j = 0; j < 20; j++) {
                if (D_001B2028[j] != D_00261C08[(j * index + index) & 0xff]) {
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
        index55 = code - 55;
        index74 = code - 74;
        index80 = code - 80;
        if (code < 56) {
            g_item_owned_flags[code] = 1;
            D_001A7B30[code] = 1;
        } else if ((unsigned)(code - 56) < 18) {
            moby_mark_flag_and_append_to_list(index55);
        } else if ((unsigned)index74 < 6) {
            D_001395B8[index74] = 1;
        } else if ((unsigned)index80 < 30) {
            if (!D_001A7A60[index80]) {
                D_001A7A60[index80] = 1;
                snd_play_from_global_bank(1, 0, 0);
                value_set_entry_by_index(0x1233, -1);
                D_001A8CEC = 1;
            }
        }
    } else {
        D_001ABCA0 = 0;
    }
}

/* Plays a menu sound, but only when menu sounds are turned on. */
void snd_play_menu_sound_if_enabled(int sound_id, int sound_param)
{
    if (ref_L00_002DF190_00 != 0)
        snd_play_from_global_bank(sound_id, sound_param, 0);
}
