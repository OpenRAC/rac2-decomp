#include "include_asm.h"
#include "names.h"

extern unsigned char D_L00_001B26B4[];
extern int math_fast_float_d(void *p);

/* Advances the resident fade timer by one step. */
void fade_tick_timer(void)
{
    math_fast_float_d(D_L00_001B26B4);
}
