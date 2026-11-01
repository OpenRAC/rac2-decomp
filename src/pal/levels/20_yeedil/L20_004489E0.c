#include "include_asm.h"



extern unsigned int D_L20_001B2F9C __attribute__((sda));
extern int func_L20_00449AC8(char *);
extern void func_0039BDF0(char *, char *, int, int);

char *func_PAL_L20_00448D88(char *arg0, char *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    unsigned int p = D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);

    if (func_L20_00449AC8((char *)p) != 0) {
        func_L20_004499E8((char *)p, arg0, arg1);
        func_0039BDF0((char *)p, (char *)(p + 0x10), 0x12C, 0);
        return (char *)p;
    }
    return 0;
}

