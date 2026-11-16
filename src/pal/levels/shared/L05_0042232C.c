#include "include_asm.h"
#include "names.h"


extern int math_random_int_below(int);

/* func_PAL_L05_004224E8, the PAL copy of func_L05_0041D728: the same C, where the alpha steps take PAL's 50 Hz scale. */
void glow_l05_ring_init_state_2_pal(unsigned char *actor) {
    unsigned char *state = *(unsigned char **)(actor + 0x68);
    float *rand_cursor;
    int *fade_table;
    int i;
    int j;

    rand_cursor = (float *)state;
    for (i = 3; i >= 0; i--) {
        *rand_cursor++ = (float)math_random_int_below(0xFF);
    }
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    fade_table = (int *)(state + 0x20);
    for (j = 0; j < 4; j++) {
        fade_table[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(state + 0x30) = 2.8f;
    *(float *)(state + 0x34) = 3.5f;
    *(float *)(state + 0x38) = 3.5f;
    *(float *)(state + 0x3C) = 2.8f;
}


