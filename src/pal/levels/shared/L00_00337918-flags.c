#include "include_asm.h"

#include "common.h"
void part_kill(void *);
int FastDecTimer(short *);

void func_PAL_L00_00338920(void *param_1)
{
  int lVar1;

  lVar1 = FastDecTimer((short *)((char *)param_1 + 10));
  if (lVar1 != 0) {
    part_kill(param_1);
  }
  return;
}
