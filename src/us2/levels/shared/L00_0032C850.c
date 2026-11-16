#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));

extern int g_level_int_value_a __attribute__((sda));

/* Returns a level-wide integer value. */
int level_get_int_value_a_us2(void) {
    return g_level_int_value_a;
}



