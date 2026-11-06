/* func_PAL_L00_003AB208, the PAL copy of func_L00_003A7AF0: the same C, where 0.1f becomes 0.4166667f and both arms scale for 50 Hz. */
#include "common.h"
extern float D_L00_001B2868 __attribute__((section(".data")));
extern float D_L00_001B286C __attribute__((section(".data")));
extern float D_L00_001B2870 __attribute__((section(".data")));
extern float ref_L00_003A7AF0_00 __attribute__((sda));
extern int D_L00_001AF6C4 __attribute__((sda));
extern int D_L00_001AF6CC __attribute__((sda));
extern int func_L00_00329E90(char *, int, void *);
extern char *func_L00_0032A088(int, int);
extern int func_L00_00329FF0(int);

void func_PAL_L00_003AB208(char *object)
{
    char *state = *(char **)(object + 0x68);
    int local[4];
    int value, i;
    int index;
    int *table;
    int kind;
    float range;
    *(short *)(state + 4) = -1;
    *(float *)(state + 12) = 0.4166667f;
    *(int *)(state + 0) = 0;
    *(short *)(state + 6) = 0;
    *(short *)(state + 16) = 0;
    *(int *)(state + 8) = 0;
    *(int *)(state + 36) = -1;
    *(int *)(state + 40) = 0;
    *(int *)(state + 44) = 0;
    *(int *)(state + 48) = 0;
    *(int *)(state + 60) = -1;
    if (*(short *)(object + 0xAA) == 1490)
        *(int *)(state + 52) = ((s32)(D_L00_001AF6C4) * 5 + 2) / 6;
    else
        *(int *)(state + 52) = ((s32)(D_L00_001AF6CC) * 5 + 2) / 6;
    *(unsigned int *)(object + 0x78) = 0xFF0020FF;
    index = func_L00_00329E90(object, 0, local);
    *(short *)(state + 18) = index;
    if (local[0] == 0) {
        table = (int *)func_L00_0032A088(*(short *)(object + 0xAA), (short)index);
        value = func_L00_00329FF0((int)(table + 16));
        for (i = 0; i < 16; i++) {
            table[i] = value;
            value += 640;
        }
    }
    kind = *(short *)(object + 0xAA);
    D_L00_001B2868 = 0.104719766f;
    range = 30.0f;
    if (kind == 1490) {
        range = 20.0f;
        D_L00_001B286C = range;
    } else {
        ref_L00_003A7AF0_00 = range;
    }
    D_L00_001B2870 = 0.104719766f;
}
