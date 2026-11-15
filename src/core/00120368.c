#include "include_asm.h"

extern void (*D_00135D34)(void);

/* Calls the current handler for an unrecoverable exception error. */
void func_00120368(void) {
    D_00135D34();
}
