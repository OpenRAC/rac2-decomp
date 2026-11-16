#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void radial_menu_draw(void *);

void func_PAL_0029D5B8(void) {
    if (g_resident_data_base != 0)
        radial_menu_draw(g_resident_data_base + 0x3A570);
}

extern void msg_box_init_localized(void *, int, int, int);

void func_PAL_0029D5E8(int a0, int a1, int a2) { if (g_resident_data_base != 0) msg_box_init_localized(g_resident_data_base + 0x36F28, a0, a1, a2); }

extern void msg_box_init_short(void *, int, int);

void func_PAL_0029D630(int first, int second) {
    if (g_resident_data_base != 0)
        msg_box_init_short(g_resident_data_base + 0x36F28, first, second);
}
