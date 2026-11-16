#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int g_menu_input_flags;
extern int level_l00_call_module_handler_with_arg_11_us2(int);

/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_L00_0034F9C8(void) {
    level_l00_call_module_handler_with_arg_11_us2(g_menu_input_flags);
    return 0;
}


/* func_002D2918 is built from 002D2918-g8.c. */

int func_US2_L00_0034F9F0(void) {
    level_l00_call_module_handler_with_arg_11_us2(g_menu_input_flags);
    return 0;
}


#include "common.h"
extern void SetupGifPaging(long);
extern void func_US2_L00_0030F228(void);
extern void DoGifPaging(void);

int func_US2_L00_0034FA18(void)
{
  SetupGifPaging(0);
  func_US2_L00_0030F228();
  DoGifPaging();
  return 0;
}

