#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_draw_frame(void *);

/* Draws a menu panel, if the menu system exists. */
void menu_frame_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        menu_draw_frame(g_resident_data_base + 0x3C7E8);
}
