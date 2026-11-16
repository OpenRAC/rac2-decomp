#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int tab_menu_update(void *, int);

/* Updates the tab menu menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_tab_menu_pal(int value) {
    if (g_resident_data_base != 0)
        return tab_menu_update(g_resident_data_base + 0x3C210, value);
    return 0;
}
