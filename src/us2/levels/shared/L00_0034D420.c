#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_15(void);

int func_US2_L00_0034D420(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_15();
    DoGifPaging();
    return 0;
}

