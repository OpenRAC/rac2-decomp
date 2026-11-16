#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_9(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int setup_l00_run_three_return_zero_7_us2(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_9();
    DoGifPaging();
    return 0;
}

