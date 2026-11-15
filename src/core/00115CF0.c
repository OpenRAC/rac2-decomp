#include "common.h"

/* The unit saves $ra in a TImode slot (`sq`), so it is built with the
   -mastra-quad-saves profile. Variadic wrapper: the compiler's own register
   save area is the va_list retail passes (sp + 0x50, not the stack arguments
   ginclude's va_start would point at), so the body reaches it the way the other varargs shims in src/ do,
   from __builtin_next_arg(arg1) minus the 0x30 of register-save area. */
extern int vfprintf_stream(int arg0, int arg1, void *arg2);

/* Prints text to an output stream using a format string and extra values. */
void func_00115CF0(int stream, int format, ...) {
    vfprintf_stream(stream, format, (char *)__builtin_next_arg(format) - 0x30);
}
