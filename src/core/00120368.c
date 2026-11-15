#include "include_asm.h"

extern void (*D_00135D34)(void);

/* Calls the handler stored in D_00135D34. */
void func_00120368(void) {
    D_00135D34();
}
