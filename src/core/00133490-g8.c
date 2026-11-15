#include "common.h"

/* One $gp-relative global (gp - 0x7B64): this unit is built with -G8 by its
   file name and the symbol is declared sda. Boot-time switch - with the flag
   clear the handler runs, otherwise the 0x37 command goes to func_00132DF0
   with zero arguments. */
extern int D_001A748C __attribute__((sda));

extern int sceCdBreak(void);

extern void snd_queue_command(int arg0, int arg1, int arg2, int arg3, int arg4);

/* Runs the local handler, or sends sound command 0x37 when the sound server is in use. */
int snd_run_handler_or_send_cmd37(void) {
    if (D_001A748C == 0)
        return sceCdBreak();
    snd_queue_command(0x37, 0, 0, 0, 0);
    return 1;
}

