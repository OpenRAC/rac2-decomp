#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int map_screen_update_layout(void *, int);

int func_PAL_0029CD38(int value) {
    if (g_resident_data_base != 0)
        return map_screen_update_layout(g_resident_data_base + 0x3B7A8, value);
    return 0;
}

extern void radial_menu_destroy(void *);

void func_PAL_0029CD78(void) {
    if (g_resident_data_base != 0)
        radial_menu_destroy(g_resident_data_base + 0x3BB08);
}
