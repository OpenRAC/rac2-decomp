#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void small_list_menu_draw_rows(void *);

void func_US2_0029D958(void) {
    if (g_resident_data_base != 0)
        small_list_menu_draw_rows(g_resident_data_base + 0x3E9C8);
}
