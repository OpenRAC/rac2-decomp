#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int single_toggle_c_update(void *, int);

int func_US2_0029D838(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_c_update(g_resident_data_base + 0x3EB50, value);
    return 0;
}

extern void single_toggle_c_draw(void *);

void func_US2_0029D878(void) {
    if (g_resident_data_base != 0)
        single_toggle_c_draw(g_resident_data_base + 0x3EB50);
}

extern int list_menu_update(void *, int);

int func_US2_0029D8A8(int value) {
    if (g_resident_data_base != 0)
        return list_menu_update(g_resident_data_base + 0x3E760, value);
    return 0;
}

extern void menu_draw_if_active(void *);

void func_US2_0029D8E8(void) {
    if (g_resident_data_base != 0)
        menu_draw_if_active(g_resident_data_base + 0x3E760);
}

extern int list_menu_set_selection(void *, int);

int func_US2_0029D918(int value) {
    if (g_resident_data_base != 0)
        return list_menu_set_selection(g_resident_data_base + 0x3E9C8, value);
    return 0;
}
