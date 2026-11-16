#include "include_asm.h"
#include "names.h"

extern float ref_L02_00385E18_00;

/* Resident fade state, addressed through $gp: the value the setter moves, and its flag. */
extern int ref_L00_0037E670_01;

/* The same state word where it is NOT small data: the retail materialises its address. */
extern float g_fade_level;

extern void func_32B2C8(int, int, int, int, int);

extern short g_screen_pair_x;
extern short g_screen_pair_y;

/* Returns the current fade value. */
float fade_get_value(void)
{
    return ref_L02_00385E18_00;
}

/* sets the fade value to its default (0) or its raised value (otherwise) and clears the flag */
void fade_set_level(int raised)
{
    float level = 40.0f;
    if (raised) {
        level = 100.0f;
        g_fade_level = level;
    } else {
        ref_L02_00385E18_00 = level;
    }
    ref_L00_0037E670_01 = 0;
}

/* the reset side: clears the absolute word and the flag */
void fade_reset_level(void)
{
    g_fade_level = 0;
    ref_L00_0037E670_01 = 0;
}

/* records a pair of 16-bit values, then one fixed five-argument engine call */
void gfx_set_screen_pair_run_effect(int x, int y)
{
    g_screen_pair_x = x;
    g_screen_pair_y = y;
    func_32B2C8(8, 2, 0, 0, 0);
}
