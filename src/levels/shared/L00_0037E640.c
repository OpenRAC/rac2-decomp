#include "include_asm.h"
#include "names.h"

extern unsigned char g_fade_timer[];
extern int math_fast_float_d(void *p);

/* Advances the resident fade timer by one step. */
void fade_tick_timer(void)
{
    math_fast_float_d(g_fade_timer);
}
