#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void menu_draw_frame(void *);

void func_PAL_0029CFA8(void) {
    if (D_001A8CFC != 0)
        menu_draw_frame(D_001A8CFC + 0x3C898);
}
