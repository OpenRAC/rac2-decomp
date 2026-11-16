#include "include_asm.h"

#include "common.h"
extern int func_PAL_002D6710(int, char *);
extern char g_menu_request_screen_data[];
extern short g_menu_command_flag[];
extern void level_set_dependent_value(void);

int func_PAL_002CC8C8(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: g_menu_command_flag[0] = 8; result = 1; break;
    case 1: result = func_PAL_002D6710(3, g_menu_request_screen_data); break;
    case 2: level_set_dependent_value(); result = 1; break;
    }
    return result;
}




