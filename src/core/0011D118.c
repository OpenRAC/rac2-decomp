#include "names.h"


/* func_0011D118: owner ABI/declaration review retained. */
void sceSifExitCmd(void);

extern int g_sif_cmd_state;

/* Shuts down the command channel and clears its ready flag. */
void sif_cmd_shutdown(void)
{
  sceSifExitCmd();
  g_sif_cmd_state = 0;
  return;
}
