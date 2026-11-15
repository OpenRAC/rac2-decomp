#include "names.h"
/* libgcc _eh.o: __default_terminate, from the L_eh section of GCC's libgcc2.c
   (GPL-2.0-or-later with the libgcc linking exception), built like 00120A30.c. It is
   terminate_func's default, referenced from two data words, and calls abort
   (func_00115E28), which does not return. Its entry is four bytes into the catalogued
   row, after one word of 0xCDCDCDCD linker fill. */
extern void func_00115E28(void) __attribute__((noreturn));

/* Default action when something goes wrong in exception handling: stops the program. */
void default_terminate(void) {
    func_00115E28();
}
