#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void tab_menu_draw(void *);

void func_US2_0029D2F8(void) {
    if (g_resident_data_base != 0)
        tab_menu_draw(g_resident_data_base + 0x3C160);
}

extern int tab_menu_update(void *, int);

int func_US2_0029D328(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C160, value);
    return 0;
}

void func_US2_0029D368(void) {
    if (g_resident_data_base != 0)
        tab_menu_draw(g_resident_data_base + 0x3C160);
}

int func_US2_0029D398(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C160, value);
    return 0;
}
