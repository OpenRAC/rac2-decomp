#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void level_l00_call_module_handler_7(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_PAL_L00_00351298(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_7();
    DoGifPaging();
    return 0;
}

