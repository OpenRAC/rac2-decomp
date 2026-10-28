/* Nonmatching C reconstruction. Default game -O2 -G0 profile emits 416 bytes. All three places fail in each release on head allocation/load order. Reopen with measured object types and pointer lifetimes. No strict linked build. */
#include "common.h"

extern char *D_L06_001B9890;
extern char *D_L06_001B21C4;
extern int D_0018C0BC;
extern int D_0018C2C0;
extern char D_00189EA0[];
extern char *D_L06_001FE500[];
extern int func_002ACBC8(void *, int);
extern int func_L00_003206B8(void *, int);
extern int func_002ACCA8(void *, int);
extern int func_002A8AF0(float *, float *, int);

int func_L06_0047A268(char *obj)
{
    char *state = D_L06_001B9890;
    int index = *(short *)(obj + 0x84);
    char *entries = D_L06_001B21C4;
    int forced = 0;
    char *record = *(char **)(entries + index * 32 + 0x1c);
    if (*(short *)(state + 0x86) != 0)
        return 0;
    if (*(short *)(record + 0x2c) == 2 && D_0018C0BC == 26 && *(short *)(record + 0x2e) > 0)
        forced = 1;
    else if (*(short *)(record + 0x2c) == 4 && D_0018C2C0 == 3 && *(short *)(record + 0x2e) > 0)
        forced = 1;
    if (*(int *)(record + 0xc) >= 0 && (forced || func_002ACBC8(D_00189EA0, *(int *)(record + 0xc))))
        return 1;
    if (*(int *)(record + 0x4c) >= 0 && (forced || func_002ACBC8(D_00189EA0, *(int *)(record + 0x4c))))
        return 1;
    if (*(int *)(record + 0x10) >= 0 && (forced || func_L00_003206B8(D_00189EA0, *(int *)(record + 0x10))))
        return 1;
    if (*(int *)(record + 8) >= 0 && (forced || func_002ACCA8(D_00189EA0, *(int *)(record + 8))))
        return 1;
    if (*(int *)(record + 0x14) >= 0) {
        if (forced || func_002A8AF0((float *)D_00189EA0,
                (float *)(D_L06_001FE500[*(int *)(record + 0x14)] + 0x10),
                *(int *)D_L06_001FE500[*(int *)(record + 0x14)]))
            return 1;
    }
    return 0;
}
