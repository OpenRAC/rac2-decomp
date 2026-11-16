#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void item_grid_menu_draw(void *);

/* Draws the item grid menu panel, if the menu system exists. */
void menu_draw_item_grid_pal(void) {
    if (g_resident_data_base != 0)
        item_grid_menu_draw(g_resident_data_base + 0x39620);
}

extern void menu_screen_large_draw_parts(void *);

/* Draws the large screen menu panel, if the menu system exists. */
void menu_draw_large_screen_pal(void) {
    if (g_resident_data_base != 0)
        menu_screen_large_draw_parts(g_resident_data_base + 0x39BA0);
}

extern int UpdateItemGridMenu(void *, int);

/* Updates the item grid menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_item_grid_pal(int value) {
    if (g_resident_data_base != 0)
        return UpdateItemGridMenu(g_resident_data_base + 0x39620, value);
    return 0;
}

extern int selection_menu_update_layout(void *, int, int);

/* Updates the selection menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_selection_pal(int first, int second)
{
    if (g_resident_data_base != 0)
        return selection_menu_update_layout(g_resident_data_base + 0x39BA0, first, second);
    return 0;
}

extern int mission_screen_place_parts(void *, int);

/* Updates the mission screen menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_mission_screen_pal(int value) {
    if (g_resident_data_base != 0)
        return mission_screen_place_parts(g_resident_data_base + 0x3B4C8, value);
    return 0;
}

extern void mission_screen_draw_parts(void *);

/* Draws the mission screen menu panel, if the menu system exists. */
void menu_draw_mission_screen_pal(void) {
    if (g_resident_data_base != 0)
        mission_screen_draw_parts(g_resident_data_base + 0x3B4C8);
}
