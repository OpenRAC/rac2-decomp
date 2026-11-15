#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void menu_draw_with_prompts(void *);

void func_PAL_0029D870(void) {
    if (D_001A8CFC != 0)
        menu_draw_with_prompts(D_001A8CFC + 0x3CF50);
}

extern int popup_update_position(void *, int);

int func_PAL_0029D8A0(int value) {
    if (D_001A8CFC != 0)
        return popup_update_position(D_001A8CFC + 0x3CF50, value);
    return 0;
}
