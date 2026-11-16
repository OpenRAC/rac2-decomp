#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int selection_menu_update_layout(void *, int, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int selection_menu_update_layout_call_us2(int first, int second)
{
    if (g_resident_data_base != 0)
        return selection_menu_update_layout(g_resident_data_base + 0x39AF0, first, second);
    return 0;
}

extern int mission_screen_place_parts(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int mission_screen_place_parts_call_us2(int value) {
    if (g_resident_data_base != 0)
        return mission_screen_place_parts(g_resident_data_base + 0x3B418, value);
    return 0;
}
