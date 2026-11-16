#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void module_l00_call_handler_17_pal(void);
extern void DoGifPaging(void);

int func_PAL_L00_0034E970(void)
{
  SetupGifPaging(0);
  module_l00_call_handler_17_pal();
  DoGifPaging();
  return 0;
}

