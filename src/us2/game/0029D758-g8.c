#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int list_page_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int list_page_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return list_page_update(g_resident_data_base + 0x3F3F0, value);
    return 0;
}

extern void list_page_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void list_page_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        list_page_draw(g_resident_data_base + 0x3F3F0);
}
