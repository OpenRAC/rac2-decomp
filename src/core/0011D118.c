#include "names.h"


/* func_0011D118: owner ABI/declaration review retained. */
void func_0011CB58(void);

extern int D_001346A0;

/* Shuts down the command channel and clears its ready flag. */
void func_0011D118(void)
{
  ExitSifCmd();
  D_001346A0 = 0;
  return;
}
