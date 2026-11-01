#include "include_asm.h"

#include "common.h"
void func_002B9180(void *);
int func_00282978(short *);

void func_PAL_L00_00338920(void *param_1)
{
  int lVar1;

  lVar1 = func_00282978((short *)((char *)param_1 + 10));
  if (lVar1 != 0) {
    func_002B9180(param_1);
  }
  return;
}
