#include "include_asm.h"
#include "names.h"

extern char *D_L02_001B368C __attribute__((section(".sdata")));
extern void part_start_record_effect_by_level_kind(char *arg0, char *arg1, int arg2);

/* Index -1 means "no record". */
void func_PAL_L02_003294D8(int arg0, int arg1) {
    char *base;

    if (arg0 != -1) {
        base = D_L02_001B368C + (arg0 << 7);
        part_start_record_effect_by_level_kind(base + 0x30, base + 0x70, arg1);
    }
}

extern unsigned char D_0018C0D4;
extern void hero_reset_position_and_direction(int a0, int a1, int a2, int a3);
extern void cam_reset_entry(int arg0);

void func_PAL_L02_00329518(char *arg0, char *arg1, int arg2) {
    int kind = 0;

    switch (D_0018C0D4) {
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

