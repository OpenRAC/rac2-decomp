#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int level_l00_call_module_handler_with_arg_11(int a);

int input_l00_update_return_zero_pal(void)
{
    level_l00_call_module_handler_with_arg_11(g_menu_input_flags);
    return 0;
}

#include "common.h"
extern void SetupGifPaging(long);
extern void func_PAL_L00_0030FE30(void);
extern void DoGifPaging(void);

int func_PAL_L00_00350CD0(void)
{
  SetupGifPaging(0);
  func_PAL_L00_0030FE30();
  DoGifPaging();
  return 0;
}

