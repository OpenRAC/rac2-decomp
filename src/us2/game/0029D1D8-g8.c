#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int map_screen_update_layout(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int map_screen_update_layout_call_us2(int value) {
    if (g_resident_data_base != 0)
        return map_screen_update_layout(g_resident_data_base + 0x3B6F8, value);
    return 0;
}

extern void radial_menu_destroy(void *);

/* Draws a menu panel, if the menu system exists. */
void radial_menu_destroy_call_us2(void) {
    if (g_resident_data_base != 0)
        radial_menu_destroy(g_resident_data_base + 0x3BA58);
}
