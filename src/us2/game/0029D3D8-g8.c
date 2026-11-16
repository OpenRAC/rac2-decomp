#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void item_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void item_menu_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        item_menu_draw(g_resident_data_base + 0x3C480);
}

extern int item_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int item_menu_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return item_menu_update(g_resident_data_base + 0x3C480, value);
    return 0;
}
