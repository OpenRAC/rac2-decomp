#include "names.h"
/* func_PAL_L05_00448A58, the PAL copy of func_L05_00442828: the same C, where scale frames; lit 6 becomes 5. */
#include "common.h"
extern int g_ship_state __attribute__((sda));
extern int g_ship_transition_timer __attribute__((sda));
extern char g_ship_saved_euler[] __attribute__((aligned(16))) MACRO_ADDR;
extern char g_ship_record_position[] __attribute__((aligned(16))) MACRO_ADDR;

/* Starts a ship transition: saves the position and orientation and sets its timer, scaled to 50 Hz. */
void ship_start_transition_pal(char *position, char *euler, int frames)
{
    g_ship_state = 1;
    g_ship_transition_timer = (((int)(frames) * 5 + 2) / 6);
    qcopy(g_ship_saved_euler, euler);
    qcopy(g_ship_record_position, position);
}
