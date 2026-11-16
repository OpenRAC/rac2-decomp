#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void tab_menu_draw(void *);

/* Draws the tab menu 2 menu panel, if the menu system exists. (PAL address) */
void menu_draw_tab_menu_2_pal(void) {
    if (g_resident_data_base != 0)
        tab_menu_draw(g_resident_data_base + 0x3C210);
}
