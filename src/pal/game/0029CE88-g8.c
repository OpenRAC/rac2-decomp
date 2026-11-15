#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int tab_menu_update(void *, int);

int func_PAL_0029CE88(int value) {
    if (D_001A8CFC != 0)
        return tab_menu_update(D_001A8CFC + 0x3C210, value);
    return 0;
}
