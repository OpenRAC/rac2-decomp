#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int g_menu_input_flags;
extern int level_l00_call_module_handler_with_arg_11_us2(int);



/* Forwards the menu input flags to a level module handler and returns zero. */
int menu_toggle_option_draw_l00_us2(void) {
    level_l00_call_module_handler_with_arg_11_us2(g_menu_input_flags);
    return 0;
}




/* Same as the previous function: forwards the menu input flags to a level module handler. */
int menu_toggle_option_draw_l00_2_us2(void) {
    level_l00_call_module_handler_with_arg_11_us2(g_menu_input_flags);
    return 0;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void level_l00_call_module_handler_10_us2(void);
extern void DoGifPaging(void);

/* Sets up GIF paging, runs one level module handler, finishes paging and returns zero. */
int level_l00_run_setup_return_zero_9_us2(void)
{
  SetupGifPaging(0);
  level_l00_call_module_handler_10_us2();
  DoGifPaging();
  return 0;
}

