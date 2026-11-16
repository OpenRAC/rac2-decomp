#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int single_toggle_c_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int single_toggle_c_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_c_update(g_resident_data_base + 0x3EB50, value);
    return 0;
}

extern void single_toggle_c_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void single_toggle_c_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        single_toggle_c_draw(g_resident_data_base + 0x3EB50);
}

extern int list_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int list_menu_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return list_menu_update(g_resident_data_base + 0x3E760, value);
    return 0;
}

extern void menu_draw_if_active(void *);

/* Draws a menu panel, if the menu system exists. */
void list_menu_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        menu_draw_if_active(g_resident_data_base + 0x3E760);
}

extern int list_menu_set_selection(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int list_menu_panel_set_selection_us2(int value) {
    if (g_resident_data_base != 0)
        return list_menu_set_selection(g_resident_data_base + 0x3E9C8, value);
    return 0;
}
