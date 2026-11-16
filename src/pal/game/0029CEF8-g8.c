#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int tab_menu_update(void *, int);

/* Updates the tab menu 2 menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_tab_menu_2_pal(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C210, value);
    return 0;
}

extern void item_menu_draw(void *);

/* Draws the item menu menu panel, if the menu system exists. (PAL address) */
void menu_draw_item_menu_pal(void) {
    if (g_resident_data_base != 0)
        item_menu_draw(g_resident_data_base + 0x3C530);
}

extern int item_menu_update(void *, int);

/* Updates the item menu menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_item_menu_pal(int value) {
    if (g_resident_data_base != 0)
        return item_menu_update(g_resident_data_base + 0x3C530, value);
    return 0;
}
