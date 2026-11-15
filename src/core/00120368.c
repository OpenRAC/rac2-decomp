#include "include_asm.h"
#include "names.h"

extern void (*D_00135D34)(void);

/* Calls the current handler for an unrecoverable exception error. */
void call_terminate_handler(void) {
    D_00135D34();
}
