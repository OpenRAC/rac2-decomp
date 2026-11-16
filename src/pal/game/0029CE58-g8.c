#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void tab_menu_draw(void *);

void func_PAL_0029CE58(void) {
    if (g_resident_data_base != 0)
        tab_menu_draw(g_resident_data_base + 0x3C210);
}
