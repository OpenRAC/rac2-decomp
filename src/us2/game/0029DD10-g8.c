#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_draw_with_prompts(void *);

/* Draws a menu panel, if the menu system exists. */
void prompt_menu_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        menu_draw_with_prompts(g_resident_data_base + 0x3CEA0);
}

extern int popup_update_position(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int popup_panel_update_position_us2(int value) {
    if (g_resident_data_base != 0)
        return popup_update_position(g_resident_data_base + 0x3CEA0, value);
    return 0;
}
