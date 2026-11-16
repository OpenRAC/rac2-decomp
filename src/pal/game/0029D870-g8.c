#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_draw_with_prompts(void *);

void func_PAL_0029D870(void) {
    if (g_resident_data_base != 0)
        menu_draw_with_prompts(g_resident_data_base + 0x3CF50);
}

extern int popup_update_position(void *, int);

int func_PAL_0029D8A0(int value) {
    if (g_resident_data_base != 0)
        return popup_update_position(g_resident_data_base + 0x3CF50, value);
    return 0;
}
