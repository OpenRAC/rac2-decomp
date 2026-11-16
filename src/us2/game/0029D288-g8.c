#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_screen_draw_parts(void *);

/* Draws a menu panel, if the menu system exists. */
void menu_screen_draw_parts_call_us2(void) {
    if (g_resident_data_base != 0)
        menu_screen_draw_parts(g_resident_data_base + 0x3A000);
}

extern int grid_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int grid_menu_update_call_us2(int value) {
    if (g_resident_data_base != 0)
        return grid_menu_update(g_resident_data_base + 0x3A000, value);
    return 0;
}
