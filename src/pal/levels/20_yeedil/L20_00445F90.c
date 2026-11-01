#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00445F90);







extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);
extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);
extern float func_00282E80(char *, char *);
extern void func_002B50E0(char *, char *, float);
extern void func_L01_00321178(char *, char *);

void func_PAL_L20_00448200(char *arg0, char *arg1, float f) {
    char *state = *(char **)(arg0 + 0x68);

    func_002A8C28(arg0, arg0 + 0x10, 0x04010000, 0,
                  *(float *)(state + 0x50) + 0.5f, 50.0f, 1.0f, 1, 0);
    if (func_00282E80(arg0 + 0x10, arg1) <= *(float *)(state + 0x84)) {
        func_002B50E0(arg0, arg1, f);
    } else {
        func_L01_00321178(arg0, arg1);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00448428);

#include "common.h"
extern void func_002A7750(int, int, int);
extern int func_002A7820(int, int);
extern int func_L20_004433B0(char *);
extern int func_002A77E0(int);

void func_PAL_L20_00448650(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int v = *(int *)(state + 0x17F4);
    int r;

    if (v == 2) goto other;
    if (v >= 3) goto other;
    if (v != 1) goto other;
    r = func_L20_004433B0(arg0);
    *(int *)(state + 0x17FC) = r;
    if (r == 0) {
        func_002A7750(arg0, 0xC, 4);
    } else {
        func_002A7750(arg0, 4, 2);
    }
    goto done;
other:
    r = func_002A77E0(2) + 2;
    *(int *)(state + 0x17F8) = r;
    *(int *)(state + 0x1810) = ((s32)(func_002A7820(0xB4, 0x168)) * 5 + 2) / 6;
    func_002A7750(arg0, 3, 1);
done:
    *(int *)(state + 0x17F4) = *(unsigned char *)(arg0 + 0x95);
}

