#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void radial_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void resident_radial_menu_draw(void) {
    if (g_resident_data_base != 0)
        radial_menu_draw(g_resident_data_base + 0x3A570);
}

extern void msg_box_init_localized(void *, int, int, int);

/* Passes three values to the first menu panel, if the menu system exists. */
void func_PAL_0029D5E8(int first, int second, int third) { if (g_resident_data_base != 0) msg_box_init_localized(g_resident_data_base + 0x36F28, first, second, third); }

extern void msg_box_init_short(void *, int, int);

/* Passes two values to the first menu panel, if the menu system exists. */
void resident_msg_box_init_short(int first, int second) {
    if (g_resident_data_base != 0)
        msg_box_init_short(g_resident_data_base + 0x36F28, first, second);
}
