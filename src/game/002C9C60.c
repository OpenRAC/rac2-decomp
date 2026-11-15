#include "include_asm.h"
#include "names.h"

extern struct {
    char pad[0x1C0];
    float one;
    float reciprocal;
    int mode;
} D_001F2840;

/* Stores 1.0 and the inverse of the given value in the pause state block and clears its mode. */
void menu_set_pause_scale_inverse(float value)
{
    float inverse = 1.0f / value;
    g_pause_menu_state.one = 1.0f;
    g_pause_menu_state.reciprocal = inverse;
    g_pause_menu_state.mode = 0;
}
