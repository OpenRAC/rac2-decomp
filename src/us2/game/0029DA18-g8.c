#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int radial_menu_update_us2(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int radial_menu_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return radial_menu_update_us2(g_resident_data_base + 0x3A4C0, value);
    return 0;
}
