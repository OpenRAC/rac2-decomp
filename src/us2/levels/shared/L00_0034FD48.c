#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void level_l00_call_module_handler_6(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_US2_L00_0034FD48(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_6();
    DoGifPaging();
    return 0;
}

extern int D_00138344;
extern void module_l00_call_handler_with_arg_9(int a);

int func_US2_L00_0034FDD0(void)
{
    module_l00_call_handler_with_arg_9(D_00138344);
    return 0;
}

