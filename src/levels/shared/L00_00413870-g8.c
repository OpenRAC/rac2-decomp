#include "include_asm.h"
#include "names.h"

extern float D_L00_001B13D8 __attribute__((sda));
extern int D_L00_001B13C4 __attribute__((sda));
extern int D_L00_001B13C8 __attribute__((sda));
extern int D_L00_001B13CC __attribute__((sda));
extern int D_L00_001B13D0 __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_L00_00413918(char *, int, int, int, int);

/* Scrolls the wave line texture and draws its two ribbons. */
void func_L00_00413870(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scroll = *(float *)(state + 0x14) - D_L00_001B13D8;

    *(float *)(state + 0x14) = scroll;
    if (scroll <= -8.0f) {
        *(float *)(state + 0x14) = scroll + 8.0f;
    }
    VU1_addGSregister(0x47, 0x51001ULL);

    DrawWaveLineRibbon(object, *(int *)(state + 0), D_L00_001B13C4, D_L00_001B13CC, 10);
    DrawWaveLineRibbon(object, *(int *)(state + 4), D_L00_001B13C8, D_L00_001B13D0, 20);
}
