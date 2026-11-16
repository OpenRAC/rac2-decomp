#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int info_panel_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int info_panel_update_call_us2(int value) {
    if (g_resident_data_base != 0)
        return info_panel_update(g_resident_data_base + 0x3BA58, value);
    return 0;
}
