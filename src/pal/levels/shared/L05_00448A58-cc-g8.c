#include "names.h"
/* func_PAL_L05_00448A58, the PAL copy of func_L05_00442828: the same C, where scale a2; lit 6 becomes 5. */
#include "common.h"
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern char g_ship_saved_euler[] __attribute__((aligned(16))) MACRO_ADDR;
extern char g_ship_record_position[] __attribute__((aligned(16))) MACRO_ADDR;

void func_PAL_L05_00448A58(char *a0, char *a1, int a2)
{
    g_ship_state = 1;
    g_ship_transition_timer = (((int)(a2) * 5 + 2) / 6);
    qcopy(g_ship_saved_euler, a1);
    qcopy(g_ship_record_position, a0);
}
