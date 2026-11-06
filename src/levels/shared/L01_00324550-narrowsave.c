/* func_L01_00324550: variadic, built with -mastra-quad-saves and -frac2-narrow-saves-below.
   register_precision keeps $ra's save at 64 bits; the narrower save takes the lower slot. */
#include "common.h"
extern int func_00288FB8(int);
extern void func_L01_00324410(char *, char *, int *);
extern void func_0028BCA0(int);
extern void func_0026FEB8(const char *, ...);
extern const char D_001AA590[];
void func_L01_00324550(int id, ...) __attribute__((register_precision(ra, 64)));
void func_L01_00324550(int id, ...)
{
    char text[0x200];
    char *format = (char *)func_00288FB8(id);
    if (format) {
        /* The seven saved integer argument slots are forwarded. */
        func_L01_00324410(text, format, (int *)((char *)__builtin_next_arg(id) - 0x38));
        func_0028BCA0((int)text);
    } else func_0026FEB8(D_001AA590, id);
}
