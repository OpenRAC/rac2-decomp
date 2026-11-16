#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void level_l00_call_module_handler_8(void);

int level_l00_run_setup_return_zero_2_pal(void)
{
    SetupGifPaging(0);
    level_l00_call_module_handler_8();
    DoGifPaging();
    return 0;
}

