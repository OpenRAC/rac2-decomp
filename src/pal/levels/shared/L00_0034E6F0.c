#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_15(void);

/* Brackets a level module handler call with GIF paging setup and flush, then returns zero. */
int level_l00_run_setup_return_zero_3_pal(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_15();
    DoGifPaging();
    return 0;
}

