#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void menu_screen_draw_parts(void *);

void func_US2_0029D288(void) {
    if (D_001A8CFC != 0)
        menu_screen_draw_parts(D_001A8CFC + 0x3A000);
}

extern int grid_menu_update(void *, int);

int func_US2_0029D2B8(int value) {
    if (D_001A8CFC != 0)
        return grid_menu_update(D_001A8CFC + 0x3A000, value);
    return 0;
}
