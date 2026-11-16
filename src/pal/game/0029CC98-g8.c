#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int list_screen_layout(void *, int);

/* Updates the list screen menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_list_screen_pal(int value) {
    if (g_resident_data_base != 0)
        return list_screen_layout(g_resident_data_base + 0x3B030, value);
    return 0;
}

extern void list_screen_draw(void *);

/* Draws the list screen menu panel, if the menu system exists. */
void menu_draw_list_screen_pal(void) {
    if (g_resident_data_base != 0)
        list_screen_draw(g_resident_data_base + 0x3B030);
}

extern void map_screen_draw(void *);

/* Draws the map screen menu panel, if the menu system exists. */
void menu_draw_map_screen_pal(void) {
    if (g_resident_data_base != 0)
        map_screen_draw(g_resident_data_base + 0x3B7A8);
}
