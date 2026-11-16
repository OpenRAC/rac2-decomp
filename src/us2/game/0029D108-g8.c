#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void mission_screen_draw_parts(void *);

void func_US2_0029D108(void) {
    if (g_resident_data_base != 0)
        mission_screen_draw_parts(g_resident_data_base + 0x3B418);
}

extern int list_screen_layout(void *, int);

int func_US2_0029D138(int value) {
    if (g_resident_data_base != 0)
        return list_screen_layout(g_resident_data_base + 0x3AF80, value);
    return 0;
}

extern void list_screen_draw(void *);

void func_US2_0029D178(void) {
    if (g_resident_data_base != 0)
        list_screen_draw(g_resident_data_base + 0x3AF80);
}

extern void map_screen_draw(void *);

void func_US2_0029D1A8(void) {
    if (g_resident_data_base != 0)
        map_screen_draw(g_resident_data_base + 0x3B6F8);
}
