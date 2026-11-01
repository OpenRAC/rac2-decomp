#include "include_asm.h"

extern int D_00138344;
extern void func_L00_0030E010(int a);

int func_PAL_L00_00350CA8(void)
{
    func_L00_0030E010(D_00138344);
    return 0;
}

#include "common.h"
extern void func_0027C540(long);
extern void func_PAL_L00_0030FE30(void);
extern void func_0027C660(void);

int func_PAL_L00_00350CD0(void)
{
  func_0027C540(0);
  func_PAL_L00_0030FE30();
  func_0027C660();
  return 0;
}

