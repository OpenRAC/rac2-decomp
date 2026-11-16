#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int list_screen_layout(void *, int);

int func_PAL_0029CC98(int value) {
    if (g_resident_data_base != 0)
        return list_screen_layout(g_resident_data_base + 0x3B030, value);
    return 0;
}

extern void list_screen_draw(void *);

void func_PAL_0029CCD8(void) {
    if (g_resident_data_base != 0)
        list_screen_draw(g_resident_data_base + 0x3B030);
}

extern void map_screen_draw(void *);

void func_PAL_0029CD08(void) {
    if (g_resident_data_base != 0)
        map_screen_draw(g_resident_data_base + 0x3B7A8);
}
