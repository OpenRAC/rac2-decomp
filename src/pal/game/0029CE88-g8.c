#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int tab_menu_update(void *, int);

int func_PAL_0029CE88(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C210, value);
    return 0;
}
