#include "include_asm.h"
#include "names.h"


/* func_US2_00287108: v2.00's own exit helper of the menu overlay: refresh, set D_0018A000 to 10, pop the state. */
extern short g_menu_command_flag;
extern void pad_clear_port_state(void);
extern int request_end_slot(int, int);

void menu_exit_overlay_us2(void)
{
    pad_clear_port_state();
    g_menu_command_flag = 10;
    request_end_slot(0, 0);
}
