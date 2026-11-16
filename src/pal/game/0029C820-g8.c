#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base;
extern int g_mission_menu_depth __attribute__((sda));
extern int g_mission_select_enabled __attribute__((sda));
extern int g_notice_owner;
extern short g_menu_command_flag[];
extern void circle_menu_draw_pal(void *);

/* func_PAL_0029C820, the PAL copy of func_0029BEB8: the same C with one more
   test, D_0018A000[0] (the halfword counter other units set to 8) must be zero,
   and the callee becomes func_PAL_0033C600 at offset 0x3F860. */
void module_l00_call_handler_2_pal(void) {
    if (g_mission_menu_depth != 0 && g_menu_command_flag[0] == 0 && g_notice_owner == 0 && g_mission_select_enabled != 0 && g_resident_data_base != 0)
        circle_menu_draw_pal(g_resident_data_base + 0x3F860);
}
