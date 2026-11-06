#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_00417ED0, the PAL copy of func_L00_00412FF8: the same C, except that D_L00_001B13DC
 * is read as a word, held in a local across the -1 store, and scaled to 50 Hz. */

extern int D_L00_001B1378 __attribute__((sda));
extern int D_L00_001B137C __attribute__((sda));
extern int D_L00_001B13DC __attribute__((sda));
extern char D_00189EB0[];
extern char D_L00_0025A1A0[];
extern char D_L00_0025A420[];
extern char *func_0029EFD0(int id);
extern void func_002833F0(char *dst, char *src);
extern void func_00282D30(float *dst, char *src, float scale);
extern void func_00282CC0(char *dst, char *src, float *local);
extern void func_PAL_L00_00418190(char *object);

char *func_PAL_L00_00417ED0(char *owner)
{
    char *object = func_0029EFD0(0x1195);
    char *state;
    int timer;
    int counter;
    float local[4];

    if (object != 0) {
        *(unsigned char *)(object + 0x20) = 1;
        *(unsigned char *)(object + 0x30) = 0xFF;
        state = *(char **)(object + 0x68);
        timer = D_L00_001B13DC;
        *(int *)(state + 0x18) = -1;
        *(unsigned short *)(state + 0x1E) = ((s32)(timer) * 5 + 2) / 6;
        func_002833F0(object + 0xC0, D_00189EB0);
        counter = D_L00_001B1378;
        *(char **)(state + 0) = D_L00_0025A1A0 + counter * 0xA0;
        *(char **)(state + 4) = D_L00_0025A420 + counter * 0x140;
        if ((unsigned int)counter >= 4)
            D_L00_001B1378 = 0;
        D_L00_001B1378 = (D_L00_001B1378 + 1) % 4;
        *(int *)(state + 0x24) = D_L00_001B137C;
        *(char **)(state + 0x20) = owner;
        func_00282D30(local, *(char **)(D_00189EB0 + 0x2200) + 0xE0, 0.75f);
        func_00282CC0(object + 0x10, D_00189EB0 - 0x10, local);
        func_PAL_L00_00418190(object);
    }
    return object;
}
