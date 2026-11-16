#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));
extern int g_pal_return_value_b __attribute__((sda));

int func_PAL_L00_0032D618(void) {
    return g_pal_return_value_b;
}

