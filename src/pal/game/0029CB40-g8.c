#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void item_grid_menu_draw(void *);

void func_PAL_0029CB40(void) {
    if (g_resident_data_base != 0)
        item_grid_menu_draw(g_resident_data_base + 0x39620);
}

extern void menu_screen_large_draw_parts(void *);

void func_PAL_0029CB70(void) {
    if (g_resident_data_base != 0)
        menu_screen_large_draw_parts(g_resident_data_base + 0x39BA0);
}

extern int UpdateItemGridMenu(void *, int);

int func_PAL_0029CBA0(int value) {
    if (g_resident_data_base != 0)
        return UpdateItemGridMenu(g_resident_data_base + 0x39620, value);
    return 0;
}

extern int selection_menu_update_layout(void *, int, int);

int func_PAL_0029CBE0(int first, int second)
{
    if (g_resident_data_base != 0)
        return selection_menu_update_layout(g_resident_data_base + 0x39BA0, first, second);
    return 0;
}

extern int mission_screen_place_parts(void *, int);

int func_PAL_0029CC28(int value) {
    if (g_resident_data_base != 0)
        return mission_screen_place_parts(g_resident_data_base + 0x3B4C8, value);
    return 0;
}

extern void mission_screen_draw_parts(void *);

void func_PAL_0029CC68(void) {
    if (g_resident_data_base != 0)
        mission_screen_draw_parts(g_resident_data_base + 0x3B4C8);
}
