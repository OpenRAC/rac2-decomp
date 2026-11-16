#include "include_asm.h"
#include "names.h"

extern char *g_matrix_l02_record_table __attribute__((section(".sdata")));
extern void part_start_record_effect_by_level_kind(char *arg0, char *arg1, int arg2);

/* Index -1 means "no record". */
void part_start_record_effect_by_index_pal(int index, int param) {
    char *record;

    if (index != -1) {
        record = g_matrix_l02_record_table + (index << 7);
        part_start_record_effect_by_level_kind(record + 0x30, record + 0x70, param);
    }
}

extern unsigned char g_screen_mode_flag;
extern void hero_reset_position_and_direction(int a0, int a1, int a2, int a3);
extern void cam_reset_entry(int arg0);

/* Starts an effect whose variant depends on the current setting, then runs an optional follow-up. */
void part_start_record_effect_by_level_kind_pal(char *first, char *second, int extra) {
    int variant = 0;

    switch (g_screen_mode_flag) {
    case 1:
        variant = 0x3F;
        break;
    case 2:
        variant = 0x56;
        break;
    }
    hero_reset_position_and_direction((int)first, (int)second, variant, 1);
    if (extra != -1)
        cam_reset_entry(extra);
}

