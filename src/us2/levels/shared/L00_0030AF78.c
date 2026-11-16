#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));

extern int g_level_int_value_b __attribute__((sda));

int func_US2_L00_0030AF78(void) {
    return g_level_int_value_b;
}



