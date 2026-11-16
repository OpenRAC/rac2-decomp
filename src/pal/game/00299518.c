#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));
extern int g_pending_value __attribute__((sda));

/* Returns the pending menu value. */
int menu_get_pending_value_pal(void) {
    return g_pending_value;
}


/* Returns whether a menu value was pending, and clears it. */
int menu_take_pending_value_pal(void) {
    int value = g_pending_value;
    g_pending_value = 0;
    return value != 0;
}

