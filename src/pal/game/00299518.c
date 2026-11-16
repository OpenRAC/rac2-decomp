#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));
extern int g_pending_value __attribute__((sda));

int func_PAL_00299518(void) {
    return g_pending_value;
}


int func_PAL_00299520(void) {
    int value = g_pending_value;
    g_pending_value = 0;
    return value != 0;
}

