#include "include_asm.h"
#include "names.h"


extern int math_random_int_below(int);

/* func_PAL_L05_0042C798, the PAL copy of func_L05_00426D98: the same C, where the alpha steps take PAL's 50 Hz scale. */
/* Sets up the four glow sprites of an L05 ring: random phases, fixed rates and alpha steps, and sizes (PAL: 50 Hz alpha steps). */
void glow_l05_ring_init_2_pal(unsigned char *object) {
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    float *phase;
    int *alpha;
    int i;
    int j;

    phase = (float *)vars;
    for (i = 3; i >= 0; i--) {
        *phase++ = (float)math_random_int_below(0xFF);
    }
    *(float *)(vars + 0x10) = -1.0f;
    *(float *)(vars + 0x14) = -2.25f;
    *(float *)(vars + 0x18) = 1.25f;
    *(float *)(vars + 0x1C) = 2.5f;
    alpha = (int *)(vars + 0x20);
    for (j = 0; j < 4; j++) {
        alpha[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(vars + 0x30) = 2.5f;
    *(float *)(vars + 0x34) = 3.2f;
    *(float *)(vars + 0x38) = 3.2f;
    *(float *)(vars + 0x3C) = 2.5f;
}





