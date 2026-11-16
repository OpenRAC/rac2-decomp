#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_screen_draw_parts(void *);

/* Draws the parts screen menu panel, if the menu system exists. */
void menu_draw_parts_screen_pal(void) {
    if (g_resident_data_base != 0)
        menu_screen_draw_parts(g_resident_data_base + 0x3A0B0);
}

extern int grid_menu_update(void *, int);

/* Updates the grid menu menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_grid_menu_pal(int value) {
    if (g_resident_data_base != 0)
        return grid_menu_update(g_resident_data_base + 0x3A0B0, value);
    return 0;
}
