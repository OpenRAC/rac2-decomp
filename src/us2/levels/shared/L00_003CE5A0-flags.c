#include "include_asm.h"

#include "common.h"
#include "structs.h"
extern int g_screen_flag_enabled __attribute__((sda));

extern int g_level_init_flag_b __attribute__((sda));

void func_US2_L00_003CE5A0(void) {
    g_level_init_flag_b = 0;
}


