#include "common.h"
extern char *D_L02_001B1190[] SDATA(D_L02_001B1190);

/* Checks whether the current wave is finished so the next one can begin. */
int arena_l02_is_wave_complete(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *challengeRow = D_L02_001B1190[*(short *)(state + 0x120)];
    char *waveEntry = *(char **)(challengeRow + 0x4) + *(short *)(state + 0x122) * 0x14;
    int ok;

    ok = *(int *)(state + 0x90) == *(short *)(waveEntry + 0);
    if (*(int *)(state + 0x94) != *(short *)(waveEntry + 2))
        ok = 0;
    if (*(int *)(state + 0x98) != *(short *)(waveEntry + 4))
        ok = 0;
    ok &= 1;
    if (*(int *)(state + 0x9C) != *(short *)(waveEntry + 6))
        ok = 0;
    if (*(unsigned char *)(waveEntry + 0x10))
        ok &= *(int *)(state + 0xA0);
    if (*(unsigned char *)(waveEntry + 0x11))
        ok &= *(int *)(state + 0xA4);
    return *(int *)(state + 0x60) == 0 && ok != 0;
}
