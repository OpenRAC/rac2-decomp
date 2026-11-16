#include "common.h"
extern char *g_arena_challenge_table_2[] SDATA(D_L02_001B1190);

/* Checks whether the current wave is finished so the next one can begin. */
int arena_l02_is_wave_complete(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *challenge_row = g_arena_challenge_table_2[*(short *)(state + 0x120)];
    char *wave_entry = *(char **)(challenge_row + 0x4) + *(short *)(state + 0x122) * 0x14;
    int ok;

    ok = *(int *)(state + 0x90) == *(short *)(wave_entry + 0);
    if (*(int *)(state + 0x94) != *(short *)(wave_entry + 2))
        ok = 0;
    if (*(int *)(state + 0x98) != *(short *)(wave_entry + 4))
        ok = 0;
    ok &= 1;
    if (*(int *)(state + 0x9C) != *(short *)(wave_entry + 6))
        ok = 0;
    if (*(unsigned char *)(wave_entry + 0x10))
        ok &= *(int *)(state + 0xA0);
    if (*(unsigned char *)(wave_entry + 0x11))
        ok &= *(int *)(state + 0xA4);
    return *(int *)(state + 0x60) == 0 && ok != 0;
}
