#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int tab_menu_update(void *, int);

int func_PAL_0029CEF8(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C210, value);
    return 0;
}

extern void item_menu_draw(void *);

void func_PAL_0029CF38(void) {
    if (g_resident_data_base != 0)
        item_menu_draw(g_resident_data_base + 0x3C530);
}

extern int item_menu_update(void *, int);

int func_PAL_0029CF68(int value) {
    if (g_resident_data_base != 0)
        return item_menu_update(g_resident_data_base + 0x3C530, value);
    return 0;
}
