#include "include_asm.h"

#include "common.h"
#include "structs.h"
extern int g_screen_flag_enabled __attribute__((sda));

extern int g_level_init_flag_d __attribute__((sda));

/* Clears the level init flag d. */
void level_clear_init_flag_d_us2(void) {
    g_level_init_flag_d = 0;
}


