#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void gfx_enable_screen_flag(void);
extern int D_001B1668 __attribute__((sda));

/* Turns a screen flag on. */
void gfx_enable_screen_flag(void) {
    D_001B1668 = 1;
}


/* Turns the same screen flag off. */
void gfx_disable_screen_flag(void) {
    D_001B1668 = 0;
}
