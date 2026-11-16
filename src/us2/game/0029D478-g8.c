#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int simple_page_update(void *, int);

int func_US2_0029D478(int value) {
    if (g_resident_data_base != 0)
        return simple_page_update(g_resident_data_base + 0x3C7E8, value);
    return 0;
}

extern void two_toggle_b_draw(void *);

void func_US2_0029D4B8(void) {
    if (g_resident_data_base != 0)
        two_toggle_b_draw(g_resident_data_base + 0x3D1D8);
}

extern int two_toggle_b_update(void *, int);

int func_US2_0029D4E8(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_b_update(g_resident_data_base + 0x3D1D8, value);
    return 0;
}
