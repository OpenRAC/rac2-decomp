#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00445F90);




INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00447ED8);



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

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00448650);
