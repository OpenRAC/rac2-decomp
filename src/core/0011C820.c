#include "common.h"
#include "structs.h"
#include <stdarg.h>

 /* "e%d" */
extern void *r1_D_0012FD00;

/* The print core: walks fmt with the va_list, writing through the hook
   r1_D_0012FD00, and returns the count. */
extern int r1_func_0011A0A0(const char *, va_list);

extern void tty_putchar_deci2();

/* rac1-decomp src/core/00119D88.c: func_0011A6C8 */
/* Prints formatted text to the debug console and returns how many characters were printed. */
int printf_to_deci2_console(const char *fmt, ...) {
    va_list ap;
    void *saved = r1_D_0012FD00;
    int ret;

    r1_D_0012FD00 = (void *)tty_putchar_deci2;
    va_start(ap, fmt);
    ret = r1_func_0011A0A0(fmt, ap);
    va_end(ap);
    r1_D_0012FD00 = saved;
    return ret;
}
