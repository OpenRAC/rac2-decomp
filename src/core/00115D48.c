#include "common.h"

/* The unit saves $ra in a TImode slot (`sq`), so it is built with the
   -mastra-quad-saves profile. Variadic: one named argument, so the register
   save area starts at the $a1 slot, 0x38 below the stack arguments. The
   object is stamped into the context it points at, and both the context and
   the va_list go to func_00118CC8. */
extern void *g_libc_state_record;

extern int vfprintf_dispatch(void *arg0, int arg1, void *arg2);

/* Prints text to the standard output using a format string and extra values. */
void printf(int format, ...) {
    void *obj = g_libc_state_record;
    void *ctx = *(void **)((char *)obj + 8);

    *(void **)((char *)ctx + 0x54) = obj;
    vfprintf_dispatch(*(void **)((char *)obj + 8), format,
                  (char *)__builtin_next_arg(format) - 0x38);
}
