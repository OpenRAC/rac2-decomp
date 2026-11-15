#include "include_asm.h"
#include "names.h"

extern void SetupGifPaging(int a);
extern void DoGifPaging(void);
extern void module_l00_call_handler_10(void);

/* Run the three measured setup calls with an explicit long zero, then return the defined integer zero. */
int func_US2_L00_0034FFE0(void)
{
    SetupGifPaging(0);
    module_l00_call_handler_10();
    DoGifPaging();
    return 0;
}

