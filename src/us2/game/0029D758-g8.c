#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int list_page_update(void *, int);

int func_US2_0029D758(int value) {
    if (g_resident_data_base != 0)
        return list_page_update(g_resident_data_base + 0x3F3F0, value);
    return 0;
}

extern void list_page_draw(void *);

void func_US2_0029D798(void) {
    if (g_resident_data_base != 0)
        list_page_draw(g_resident_data_base + 0x3F3F0);
}
