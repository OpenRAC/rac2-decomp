#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int level_l00_call_module_handler_with_arg_11(int a);

/* Passes the menu input flags to a level module handler and returns zero. */
int input_l00_update_return_zero_pal(void)
{
    level_l00_call_module_handler_with_arg_11(g_menu_input_flags);
    return 0;
}

#include "common.h"
extern void SetupGifPaging(long);
extern void level_l00_menu_draw_with_prompts_pal(void);
extern void DoGifPaging(void);

/* Brackets a level module handler call with GIF paging setup and flush, then returns zero. */
int level_l00_paging_call_handler_2_pal(void)
{
  SetupGifPaging(0);
  level_l00_menu_draw_with_prompts_pal();
  DoGifPaging();
  return 0;
}

