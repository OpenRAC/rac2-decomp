#include "common.h"

/* The unit saves $ra and $fp in TImode slots (`sq $ra,0x20($sp)`,
   `sq $fp,0x10($sp)`) and spills every named argument to the frame, so it is
   built with the -mastra-quad-saves profile at -O0: the three arguments live
   at 0, 4 and 8 of the frame, the global is re-read for the call, and the
   callee's long result is forwarded without an explicit truncation. */

extern void *D_00133E74;

struct _reent;
extern long func_00117278(struct _reent *, const char *, char **, int);

/* Calls strtol (func_00117278) with the current reentrancy block. */
long func_001175F0(int arg0, int arg1, int arg2) {
    return func_00117278(D_00133E74, (const char *)arg0, (char **)arg1, arg2);
}
