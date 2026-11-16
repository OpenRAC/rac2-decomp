#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void module_l00_call_handler_17_pal(void);
extern void DoGifPaging(void);

/* Brackets a level module handler call with GIF paging setup and flush, then returns zero. */
int level_l00_paging_call_handler_17_pal(void)
{
  SetupGifPaging(0);
  module_l00_call_handler_17_pal();
  DoGifPaging();
  return 0;
}

