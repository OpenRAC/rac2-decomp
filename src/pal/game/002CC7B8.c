#include "include_asm.h"

#include "common.h"
extern int menu_send_request_pal(int, char *);
extern char g_menu_request_screen_data[];
extern short g_menu_command_flag[];
extern void level_set_dependent_value(void);

/* Handles one menu step with three cases: accept, ask another function, or run a reset (PAL). */
int menu_handle_step_with_reset_pal(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: g_menu_command_flag[0] = 8; result = 1; break;
    case 1: result = menu_send_request_pal(3, g_menu_request_screen_data); break;
    case 2: level_set_dependent_value(); result = 1; break;
    }
    return result;
}




