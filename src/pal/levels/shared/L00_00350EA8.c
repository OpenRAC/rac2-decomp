#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void level_l00_call_module_handler_7_pal(void);
extern void DoGifPaging(void);

int func_PAL_L00_00350EA8(void)
{
  SetupGifPaging(0);
  level_l00_call_module_handler_7_pal();
  DoGifPaging();
  return 0;
}



extern void level_l00_call_module_handler_6_pal(void);

int func_PAL_L00_00351000(void)
{
  SetupGifPaging(0);
  level_l00_call_module_handler_6_pal();
  DoGifPaging();
  return 0;
}


extern int g_menu_input_flags;
extern int level_l00_call_module_handler_with_arg_11(int a);

extern int func_PAL_L00_0030F2C8(int a);
extern void ref_PAL_L00_00351088_00(int a);

int input_l00_update_return_zero_2_pal(void)
{
    ref_PAL_L00_00351088_00(g_menu_input_flags);
    return 0;
}


extern void func_0027C540_1(long);
extern void func_L00_0030DFE0(void);
extern void func_0027C660_1(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
long long setup_l00_run_three_return_zero_4_pal(void)
{
    func_0027C540_1(0);
    func_L00_0030DFE0();
    func_0027C660_1();
    return 0;
}

extern int g_menu_choice;

int func_PAL_L00_003510E0(void) {
    g_menu_choice = -1;
    return 0;
}

