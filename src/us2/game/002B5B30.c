#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));

extern int g_global_int_value_a __attribute__((sda));

/* Returns the global integer value read by the pause menu code. */
int mode_get_global_value_a_us2(void) {
    return g_global_int_value_a;
}




