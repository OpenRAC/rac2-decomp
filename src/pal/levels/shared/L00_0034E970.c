#include "include_asm.h"

#include "common.h"
extern void SetupGifPaging(long);
extern void func_PAL_L00_0030F658(void);
extern void DoGifPaging(void);

int func_PAL_L00_0034E970(void)
{
  SetupGifPaging(0);
  func_PAL_L00_0030F658();
  DoGifPaging();
  return 0;
}

