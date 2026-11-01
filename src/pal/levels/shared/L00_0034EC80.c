#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_0034EC80);

#include "common.h"
extern void func_0027C540(long);
extern void func_PAL_L00_0030F7A8(void);
extern void func_0027C660(void);

int func_PAL_L00_0034ED08(void)
{
  func_0027C540(0);
  func_PAL_L00_0030F7A8();
  func_0027C660();
  return 0;
}

