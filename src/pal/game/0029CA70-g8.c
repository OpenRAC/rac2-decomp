#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void hud_update_subsystems(void *);

void func_PAL_0029CA70(void) {
    if (g_resident_data_base != 0)
        hud_update_subsystems(g_resident_data_base + 0x36F28);
}

extern void hud_item_bolt_draw(void *);

void func_PAL_0029CAA0(void) {
    if (g_resident_data_base != 0)
        hud_item_bolt_draw(g_resident_data_base + 0x36F28);
}

extern void list_menu_draw_centered_rows(void *);

void func_PAL_0029CAD0(void) {
    if (g_resident_data_base != 0)
        list_menu_draw_centered_rows(g_resident_data_base + 0x39160);
}

extern int UpdateMenuChoiceListWidgets(void *, int);

int func_PAL_0029CB00(int value) {
    if (g_resident_data_base != 0)
        return UpdateMenuChoiceListWidgets(g_resident_data_base + 0x39160, value);
    return 0;
}
