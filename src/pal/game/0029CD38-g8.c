#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int map_screen_update_layout(void *, int);

/* Updates the map screen menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_map_screen_pal(int value) {
    if (g_resident_data_base != 0)
        return map_screen_update_layout(g_resident_data_base + 0x3B7A8, value);
    return 0;
}

extern void radial_menu_destroy(void *);

/* Tears down the radial menu menu panel, if the menu system exists. */
void menu_radial_menu_destroy_pal(void) {
    if (g_resident_data_base != 0)
        radial_menu_destroy(g_resident_data_base + 0x3BB08);
}
