#include "common.h"

/* $ra is saved in a TImode slot (`sq`), so this unit is built with the
   -mastra-quad-saves profile. func_00115210 is declared with the argument
   retail passes; its definition in 00115200.c ignores it. */
extern void *D_00133E74;

extern void **func_00115210(void *arg0) __asm__("func_00115210");

/* Runs the library step that gets its shared data ready before text is printed. */
void libc_init_stdio_state(void) {
    libc_get_data_block(D_00133E74);
}
