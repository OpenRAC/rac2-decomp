#include "common.h"

/* The unit saves $ra and $fp in TImode slots (`sq $ra,0x20($sp)`,
   `sq $fp,0x10($sp)`) and spills every named argument to the frame, so it is
   built with the -mastra-quad-saves profile at -O0: the three arguments live
   at 0, 4 and 8 of the frame, the global is re-read for the call, and the
   callee's long result is forwarded without an explicit truncation. */

extern void *D_00133E74;

struct _reent;
extern long _strtol_r(struct _reent *, const char *, char **, int);

/* Turns a text string into a whole number, using the library state record. */
long strtol(int text, int endPtr, int base) {
    return _strtol_r(D_00133E74, (const char *)text, (char **)endPtr, base);
}
