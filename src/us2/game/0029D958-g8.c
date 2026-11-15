#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void small_list_menu_draw_rows(void *);

void func_US2_0029D958(void) {
    if (D_001A8CFC != 0)
        small_list_menu_draw_rows(D_001A8CFC + 0x3E9C8);
}
