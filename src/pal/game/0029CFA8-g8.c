#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void menu_draw_frame(void *);

void func_PAL_0029CFA8(void) {
    if (g_resident_data_base != 0)
        menu_draw_frame(g_resident_data_base + 0x3C898);
}
