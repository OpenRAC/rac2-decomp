#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_15(void);

int func_PAL_L00_0034E6F0(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_15();
    DoGifPaging();
    return 0;
}

