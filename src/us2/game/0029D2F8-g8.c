#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void tab_menu_draw(void *);

void func_US2_0029D2F8(void) {
    if (D_001A8CFC != 0)
        tab_menu_draw(D_001A8CFC + 0x3C160);
}

extern int tab_menu_update(void *, int);

int func_US2_0029D328(int value) {
    if (D_001A8CFC != 0)
        return tab_menu_update(D_001A8CFC + 0x3C160, value);
    return 0;
}

void func_US2_0029D368(void) {
    if (D_001A8CFC != 0)
        tab_menu_draw(D_001A8CFC + 0x3C160);
}

int func_US2_0029D398(int value) {
    if (D_001A8CFC != 0)
        return tab_menu_update(D_001A8CFC + 0x3C160, value);
    return 0;
}
