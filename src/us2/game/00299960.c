#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));

extern int g_pending_request_flag __attribute__((sda));

/* Returns the pending request flag. */
int pending_request_get_us2(void) {
    return g_pending_request_flag;
}




/* Returns whether a request was pending and clears the flag. */
int pending_request_take_us2(void) {
    int value = g_pending_request_flag;

    g_pending_request_flag = 0;
    return value != 0;
}


