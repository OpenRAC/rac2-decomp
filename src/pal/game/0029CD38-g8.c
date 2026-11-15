#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int map_screen_update_layout(void *, int);

int func_PAL_0029CD38(int value) {
    if (D_001A8CFC != 0)
        return map_screen_update_layout(D_001A8CFC + 0x3B7A8, value);
    return 0;
}

extern void radial_menu_destroy(void *);

void func_PAL_0029CD78(void) {
    if (D_001A8CFC != 0)
        radial_menu_destroy(D_001A8CFC + 0x3BB08);
}
