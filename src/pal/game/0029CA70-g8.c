#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void hud_update_subsystems(void *);

void func_PAL_0029CA70(void) {
    if (D_001A8CFC != 0)
        hud_update_subsystems(D_001A8CFC + 0x36F28);
}

extern void hud_item_bolt_draw(void *);

void func_PAL_0029CAA0(void) {
    if (D_001A8CFC != 0)
        hud_item_bolt_draw(D_001A8CFC + 0x36F28);
}

extern void list_menu_draw_centered_rows(void *);

void func_PAL_0029CAD0(void) {
    if (D_001A8CFC != 0)
        list_menu_draw_centered_rows(D_001A8CFC + 0x39160);
}

extern int UpdateMenuChoiceListWidgets(void *, int);

int func_PAL_0029CB00(int value) {
    if (D_001A8CFC != 0)
        return UpdateMenuChoiceListWidgets(D_001A8CFC + 0x39160, value);
    return 0;
}
