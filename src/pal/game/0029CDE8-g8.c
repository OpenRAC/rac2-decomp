#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_screen_draw_parts(void *);

void func_PAL_0029CDE8(void) {
    if (g_resident_data_base != 0)
        menu_screen_draw_parts(g_resident_data_base + 0x3A0B0);
}

extern int grid_menu_update(void *, int);

int func_PAL_0029CE18(int value) {
    if (g_resident_data_base != 0)
        return grid_menu_update(g_resident_data_base + 0x3A0B0, value);
    return 0;
}
