#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void item_menu_draw(void *);

void func_US2_0029D3D8(void) {
    if (D_001A8CFC != 0)
        item_menu_draw(D_001A8CFC + 0x3C480);
}

extern int item_menu_update(void *, int);

int func_US2_0029D408(int value) {
    if (D_001A8CFC != 0)
        return item_menu_update(D_001A8CFC + 0x3C480, value);
    return 0;
}
