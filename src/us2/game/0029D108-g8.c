#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void mission_screen_draw_parts(void *);

/* Draws a menu panel, if the menu system exists. */
void mission_screen_draw_parts_call_us2(void) {
    if (g_resident_data_base != 0)
        mission_screen_draw_parts(g_resident_data_base + 0x3B418);
}

extern int list_screen_layout(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int list_screen_layout_call_us2(int value) {
    if (g_resident_data_base != 0)
        return list_screen_layout(g_resident_data_base + 0x3AF80, value);
    return 0;
}

extern void list_screen_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void list_screen_draw_call_us2(void) {
    if (g_resident_data_base != 0)
        list_screen_draw(g_resident_data_base + 0x3AF80);
}

extern void map_screen_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void map_screen_draw_call_us2(void) {
    if (g_resident_data_base != 0)
        map_screen_draw(g_resident_data_base + 0x3B6F8);
}
