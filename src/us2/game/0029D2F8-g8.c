#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void tab_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void tab_menu_draw_call_us2(void) {
    if (g_resident_data_base != 0)
        tab_menu_draw(g_resident_data_base + 0x3C160);
}

extern int tab_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int tab_menu_update_call_us2(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C160, value);
    return 0;
}

/* Draws a menu panel, if the menu system exists. */
void tab_menu_draw_2_call_us2(void) {
    if (g_resident_data_base != 0)
        tab_menu_draw(g_resident_data_base + 0x3C160);
}

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int tab_menu_update_2_call_us2(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C160, value);
    return 0;
}
