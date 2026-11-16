#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void item_menu_draw(void *);

void func_US2_0029D3D8(void) {
    if (g_resident_data_base != 0)
        item_menu_draw(g_resident_data_base + 0x3C480);
}

extern int item_menu_update(void *, int);

int func_US2_0029D408(int value) {
    if (g_resident_data_base != 0)
        return item_menu_update(g_resident_data_base + 0x3C480, value);
    return 0;
}
