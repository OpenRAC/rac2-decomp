#include "include_asm.h"
#include "names.h"

extern void (*g_terminate_handler)(void);

/* Calls the current handler for an unrecoverable exception error. */
void call_terminate_handler(void) {
    g_terminate_handler();
}
