#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void tab_menu_draw(void *);

void func_PAL_0029CEC8(void) {
    if (D_001A8CFC != 0)
        tab_menu_draw(D_001A8CFC + 0x3C210);
}
