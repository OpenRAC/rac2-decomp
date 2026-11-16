#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int simple_page_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int simple_page_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return simple_page_update(g_resident_data_base + 0x3C7E8, value);
    return 0;
}

extern void two_toggle_b_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void two_toggle_b_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        two_toggle_b_draw(g_resident_data_base + 0x3D1D8);
}

extern int two_toggle_b_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int two_toggle_b_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_b_update(g_resident_data_base + 0x3D1D8, value);
    return 0;
}
