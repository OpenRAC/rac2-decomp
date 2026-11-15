#include "common.h"

/* The body saves $ra in a TImode slot (`sq $ra,0($sp)`), which is the
   -mastra-quad-saves profile these units were built with. */
extern int VfprintfInteger(void *arg0, void *arg1, int arg2, int arg3);

/* Prints text to a stream using the integer-only print routine. */
int vfprintf_stream(void *stream, int format, int args) {
    return VfprintfInteger(*(int *)((char *)stream + 0x54), stream, format, args);
}
