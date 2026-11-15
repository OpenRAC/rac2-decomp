#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_00418768, the PAL copy of func_L00_00413870: the same C, where the step is scaled by 1.2f for 50 Hz. */
extern float D_L00_001B13D8 __attribute__((sda));
extern int D_L00_001B13C4 __attribute__((sda));
extern int D_L00_001B13C8 __attribute__((sda));
extern int D_L00_001B13CC __attribute__((sda));
extern int D_L00_001B13D0 __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void wave_line_draw_ribbon(char *, int, int, int, int);

void func_PAL_L00_00418768(char *object)
{
    char *state = *(char **)(object + 0x68);
    float value = *(float *)(state + 0x14) - D_L00_001B13D8 * 1.2f;

    *(float *)(state + 0x14) = value;
    if (value <= -8.0f) {
        *(float *)(state + 0x14) = value + 8.0f;
    }
    VU1_addGSregister(0x47, 0x51001ULL);

    wave_line_draw_ribbon(object, *(int *)(state + 0), D_L00_001B13C4, D_L00_001B13CC, 10);
    wave_line_draw_ribbon(object, *(int *)(state + 4), D_L00_001B13C8, D_L00_001B13D0, 20);
}
