#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002D3C20);

#include "common.h"
extern void func_0027C540(long);
extern void func_PAL_0029D0C8(void);
extern void func_0027C660(void);

int func_PAL_002D3DB8(void)
{
  func_0027C540(0);
  func_PAL_0029D0C8();
  func_0027C660();
  return 0;
}

