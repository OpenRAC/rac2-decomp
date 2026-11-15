#include "names.h"


/* func_0011D118: owner ABI/declaration review retained. */
void sceSifExitCmd(void);

extern int D_001346A0;

/* Shuts down the command channel and clears its ready flag. */
void sif_cmd_shutdown(void)
{
  sceSifExitCmd();
  D_001346A0 = 0;
  return;
}
