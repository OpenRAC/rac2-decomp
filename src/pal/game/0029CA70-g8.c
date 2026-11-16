#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void hud_update_subsystems(void *);

/* Draws the hud subsystems menu panel, if the menu system exists. */
void menu_draw_hud_subsystems_pal(void) {
    if (g_resident_data_base != 0)
        hud_update_subsystems(g_resident_data_base + 0x36F28);
}

extern void hud_item_bolt_draw(void *);

/* Draws the hud bolt menu panel, if the menu system exists. */
void menu_draw_hud_bolt_pal(void) {
    if (g_resident_data_base != 0)
        hud_item_bolt_draw(g_resident_data_base + 0x36F28);
}

extern void list_menu_draw_centered_rows(void *);

/* Draws the centered list menu panel, if the menu system exists. */
void menu_draw_centered_list_pal(void) {
    if (g_resident_data_base != 0)
        list_menu_draw_centered_rows(g_resident_data_base + 0x39160);
}

extern int UpdateMenuChoiceListWidgets(void *, int);

/* Updates the choice list menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_choice_list_pal(int value) {
    if (g_resident_data_base != 0)
        return UpdateMenuChoiceListWidgets(g_resident_data_base + 0x39160, value);
    return 0;
}
