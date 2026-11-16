#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));
extern int g_pal_return_value_b __attribute__((sda));

/* Returns PAL global value b. */
int get_pal_return_value_b(void) {
    return g_pal_return_value_b;
}

