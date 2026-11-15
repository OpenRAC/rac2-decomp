#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int single_toggle_c_update(void *, int);

int func_US2_0029D838(int value) {
    if (D_001A8CFC != 0)
        return single_toggle_c_update(D_001A8CFC + 0x3EB50, value);
    return 0;
}

extern void single_toggle_c_draw(void *);

void func_US2_0029D878(void) {
    if (D_001A8CFC != 0)
        single_toggle_c_draw(D_001A8CFC + 0x3EB50);
}

extern int list_menu_update(void *, int);

int func_US2_0029D8A8(int value) {
    if (D_001A8CFC != 0)
        return list_menu_update(D_001A8CFC + 0x3E760, value);
    return 0;
}

extern void menu_draw_if_active(void *);

void func_US2_0029D8E8(void) {
    if (D_001A8CFC != 0)
        menu_draw_if_active(D_001A8CFC + 0x3E760);
}

extern int list_menu_set_selection(void *, int);

int func_US2_0029D918(int value) {
    if (D_001A8CFC != 0)
        return list_menu_set_selection(D_001A8CFC + 0x3E9C8, value);
    return 0;
}
