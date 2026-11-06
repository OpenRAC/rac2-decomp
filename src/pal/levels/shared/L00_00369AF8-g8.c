#include "include_asm.h"

/* func_PAL_L00_00369AF8, the PAL copy of func_L00_00367308: the same C, where word 31 becomes 6
 * and two copied timers take the 50 Hz scale. */

typedef struct { int words[34]; } ResetState;
typedef struct { int words[10]; } ResetRow;
typedef struct {
    char reserved00[0x50];
    int active;
    char reserved54[0x2C];
} ResetBlock;

extern ResetState D_L00_00221410;
extern ResetRow D_L00_0028B380[15];
extern ResetBlock D_L00_002214D0[128];
extern int D_L00_001AC598 __attribute__((sda));
extern int D_L00_001AC59C __attribute__((sda));

void func_PAL_L00_00369AF8(void) {
    int i;

    D_L00_00221410.words[7] = 2;
    D_L00_00221410.words[6] = 3;
    D_L00_00221410.words[8] = 4;
    D_L00_00221410.words[0] = -1;
    D_L00_00221410.words[10] = 100;
    D_L00_00221410.words[14] = -1;
    D_L00_00221410.words[31] = 6;
    D_L00_00221410.words[1] = 0;
    D_L00_00221410.words[4] = 0;
    D_L00_00221410.words[2] = 0;
    D_L00_00221410.words[5] = 0;
    D_L00_00221410.words[3] = 0;
    D_L00_00221410.words[30] = 0;
    D_L00_00221410.words[9] = 0;
    D_L00_00221410.words[11] = 0;
    D_L00_00221410.words[13] = 0;
    D_L00_00221410.words[15] = 0;
    D_L00_00221410.words[18] = 0;
    D_L00_00221410.words[19] = 0;
    D_L00_00221410.words[20] = 0;
    D_L00_00221410.words[21] = 0;
    D_L00_00221410.words[28] = 0;
    D_L00_00221410.words[23] = 0;
    D_L00_00221410.words[25] = 0;
    D_L00_00221410.words[24] = 0;
    D_L00_00221410.words[26] = 0;
    D_L00_00221410.words[22] = 0;
    D_L00_00221410.words[27] = 0;
    D_L00_00221410.words[32] = 0;
    D_L00_00221410.words[33] = 0;
    D_L00_001AC598 = 0;
    D_L00_001AC59C = 0;
    for (i = 0; i < 15; i++)
        D_L00_0028B380[i].words[5] = D_L00_0028B380[i].words[3];
    D_L00_0028B380[7].words[5] = (D_L00_0028B380[7].words[3] * 5 + 2) / 6;
    D_L00_0028B380[13].words[5] = (D_L00_0028B380[13].words[3] * 5 + 2) / 6;
    for (i = 127; i >= 0; i--)
        D_L00_002214D0[i].active = 0;
}
