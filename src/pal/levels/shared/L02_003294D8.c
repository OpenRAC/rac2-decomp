#include "include_asm.h"
#include "names.h"

extern char *g_matrix_l02_record_table __attribute__((section(".sdata")));
extern void part_start_record_effect_by_level_kind(char *arg0, char *arg1, int arg2);

/* Index -1 means "no record". */
void part_start_record_effect_by_index_pal(int arg0, int arg1) {
    char *base;

    if (arg0 != -1) {
        base = g_matrix_l02_record_table + (arg0 << 7);
        part_start_record_effect_by_level_kind(base + 0x30, base + 0x70, arg1);
    }
}

extern unsigned char g_screen_mode_flag;
extern void hero_reset_position_and_direction(int a0, int a1, int a2, int a3);
extern void cam_reset_entry(int arg0);

void part_start_record_effect_by_level_kind_pal(char *arg0, char *arg1, int arg2) {
    int kind = 0;

    switch (g_screen_mode_flag) {
    case 1:
        kind = 0x3F;
        break;
    case 2:
        kind = 0x56;
        break;
    }
    hero_reset_position_and_direction((int)arg0, (int)arg1, kind, 1);
    if (arg2 != -1)
        cam_reset_entry(arg2);
}

