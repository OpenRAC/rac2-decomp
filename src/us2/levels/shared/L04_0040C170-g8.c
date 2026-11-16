#include "include_asm.h"
#include "names.h"

/* func_US2_L04_0040C170 and func_US2_L04_0040C190, the v2.00 copies of func_L04_0040AC80
   and func_L04_0040AC98: the same C with one more store, to 0x001A8EE4.  The $gp-relative
   store comes first in the source: cc1 moves it to the end of the run, into the delay
   slot, the only place it gets that form (see src/levels/shared/L04_00402D90-g8.c). */

extern unsigned int g_race_state_flags;

extern unsigned int g_race_l04_state_flag_c;

extern unsigned int g_race_state_request __attribute__((sda));

void func_US2_L04_0040C170(void)
{
    g_race_state_request = 1;
    g_race_state_flags = 2;
    g_race_l04_state_flag_c = 1;
}

extern unsigned int g_race_state_flag_b __attribute__((sda));

void func_US2_L04_0040C190(void)
{
    g_race_state_flag_b = 1;
    g_race_l04_state_flag_c = 1;
}
