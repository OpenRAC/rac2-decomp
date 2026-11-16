#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void gfx_enable_screen_flag(void);
extern int g_screen_flag_enabled __attribute__((sda));

/* Turns a screen flag on. */
void gfx_enable_screen_flag(void) {
    g_screen_flag_enabled = 1;
}


/* Turns the same screen flag off. */
void gfx_disable_screen_flag(void) {
    g_screen_flag_enabled = 0;
}
