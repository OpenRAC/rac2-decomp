#include "include_asm.h"
#include "common.h"

extern int *g_effect_buffer_a[] MACRO_ADDR;
extern int *g_effect_buffer_b[] MACRO_ADDR;
extern int *g_effect_buffer_c[] MACRO_ADDR;

/* Clears three effect buffers back to zero. */
void part_clear_effect_buffers(void)
{
    int *p;
    int i;

    p = g_effect_buffer_a[0] + 60;
    for (i = 3; i >= 0; i--) { *p = 0; p -= 16; }

    p = g_effect_buffer_b[0] + 4799;
    for (i = 149; i >= 0; i--) { *p = 0; p -= 32; }

    p = g_effect_buffer_c[0];
    for (i = 9; i >= 0; i--) { p[1] = 0; p[0] = 0; p += 4; }
}
