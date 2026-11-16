#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void level_l00_call_module_handler_6(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int setup_l00_run_three_return_zero_6_us2(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_6();
    DoGifPaging();
    return 0;
}

extern int g_menu_input_flags;
extern int module_l00_call_handler_with_arg_9(int a);

int input_l00_update_return_zero_3_us2(void)
{
    module_l00_call_handler_with_arg_9(g_menu_input_flags);
    return 0;
}

