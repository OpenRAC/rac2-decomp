#include "include_asm.h"

#include "common.h"
#include "structs.h"
extern int g_screen_flag_enabled __attribute__((sda));

extern int g_level_init_flag_e __attribute__((sda));

void func_US2_L00_00404330(void) {
    g_level_init_flag_e = 0;
}


