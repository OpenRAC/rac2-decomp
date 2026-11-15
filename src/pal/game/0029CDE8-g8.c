#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void menu_screen_draw_parts(void *);

void func_PAL_0029CDE8(void) {
    if (D_001A8CFC != 0)
        menu_screen_draw_parts(D_001A8CFC + 0x3A0B0);
}

extern int grid_menu_update(void *, int);

int func_PAL_0029CE18(int value) {
    if (D_001A8CFC != 0)
        return grid_menu_update(D_001A8CFC + 0x3A0B0, value);
    return 0;
}
