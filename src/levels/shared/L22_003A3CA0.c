#include "include_asm.h"
#include "common.h"

extern s32 D_L22_001B2AC4 __attribute__((sda));
extern s32 D_L22_001B2AB8[3] __attribute__((sda));
extern s32 D_L22_0023B530[3][60];
extern s32 D_L22_001B1920[4];
extern s32 *D_L22_001B2AB4 __attribute__((sda));

/* Clears the counts and rows of spawned pickups and sets the starting limits from the ship. */
void func_L22_003A3CA0(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    s32 i, j;
    s32 *q;
    s32 a, b;

    D_L22_001B2AC4 = 0;
    for (i = 0; i < 3; i++) {
        s32 *row;

        D_L22_001B2AB8[i] = 0;
        row = D_L22_0023B530[i];
        for (j = 0x31; j >= 0; j--)
            row[j] = 0;
    }
    q = D_L22_001B2AB4;
    b = *(s16 *)(vars + 0x32E);
    D_L22_001B1920[3] = b;
    q[3] = b;
    a = *(s16 *)(vars + 0x32A);
    D_L22_001B1920[2] = a;
    q[2] = a;
    D_L22_001B1920[0] = 0;
    q[0] = 0;
    D_L22_001B1920[1] = 0;
    q[1] = 0;
}
