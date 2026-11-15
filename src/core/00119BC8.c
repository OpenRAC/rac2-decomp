#include "common.h"

/* The body saves $ra in a TImode slot (`sq $ra,0($sp)`), which is the
   -mastra-quad-saves profile these units were built with. */
extern int func_00119BF8(void *arg0, void *arg1, int arg2, int arg3);

/* Calls the integer-only formatter func_00119BF8 with the context stored at offset 0x54 of the
   stream. */
int func_00119BC8(void *arg0, int arg1, int arg2) {
    return VfprintfInteger(*(int *)((char *)arg0 + 0x54), arg0, arg1, arg2);
}
