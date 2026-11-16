#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));

extern int g_level_int_value_b __attribute__((sda));

/* Returns the level int value stored in g_level_int_value_b. */
int level_get_int_value_b_us2(void) {
    return g_level_int_value_b;
}



