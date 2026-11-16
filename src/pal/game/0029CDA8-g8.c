#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int info_panel_update(void *, int);

/* Updates the info panel menu panel and returns its answer; returns 0 if the menu system does not exist. */
int menu_update_info_panel_pal(int value) {
    if (g_resident_data_base != 0)
        return info_panel_update(g_resident_data_base + 0x3BB08, value);
    return 0;
}
