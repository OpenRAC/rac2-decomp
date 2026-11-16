#include "include_asm.h"


#include "common.h"

extern int math_random_int_below(int x);

/* func_PAL_L05_004211C0, the PAL copy of func_L05_0041C410: four random floats, four fixed ones,
   then the fade table at +0x20 scaled to 50 Hz, which turns its loop into a count-up one. */
void glow_l05_ring_init_state_pal(char *obj)
{
    float *state = *(float **)(obj + 104);
    float *rand_cursor = state;
    int *fade_table;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *rand_cursor = (float)math_random_int_below(255);
        rand_cursor++;
    }

    state[4] = -1.0000000000000000000000e+00f;
    state[5] = -2.2500000000000000000000e+00f;
    state[6] = 1.2500000000000000000000e+00f;
    state[7] = 2.5000000000000000000000e+00f;

    fade_table = (int *)(state + 8);
    for (j = 0; j < 4; j++)
    {
        fade_table[j] = ((s32)(j * 64 + 63) * 5 + 2) / 6;
    }

    state[12] = 3.0f;
    state[13] = 3.7f;
    state[15] = 3.0f;
    state[14] = 3.7f;
}

