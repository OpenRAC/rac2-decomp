#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int map_screen_update_layout(void *, int);

int func_US2_0029D1D8(int value) {
    if (D_001A8CFC != 0)
        return map_screen_update_layout(D_001A8CFC + 0x3B6F8, value);
    return 0;
}

extern void radial_menu_destroy(void *);

void func_US2_0029D218(void) {
    if (D_001A8CFC != 0)
        radial_menu_destroy(D_001A8CFC + 0x3BA58);
}
