#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void radial_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void radial_menu_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        radial_menu_draw(g_resident_data_base + 0x3A4C0);
}

extern void msg_box_init_localized(void *, int, int, int);

/* Initializes a localized message box on the menu panel, if the menu system exists. */
void func_US2_0029DA88(int first, int second, int third) { if (g_resident_data_base != 0) msg_box_init_localized(g_resident_data_base + 0x36F28, first, second, third); }

extern void msg_box_init_short(void *, int, int);

/* Initializes a short message box on the menu panel, if the menu system exists. */
void msg_box_panel_init_short_us2(int first, int second) {
    if (g_resident_data_base != 0)
        msg_box_init_short(g_resident_data_base + 0x36F28, first, second);
}
