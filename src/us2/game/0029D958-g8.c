#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void small_list_menu_draw_rows(void *);

/* Draws a menu panel, if the menu system exists. */
void small_list_menu_panel_draw_rows_us2(void) {
    if (g_resident_data_base != 0)
        small_list_menu_draw_rows(g_resident_data_base + 0x3E9C8);
}
