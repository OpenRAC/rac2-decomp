#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_003435B0(char *, int);
extern void func_00343538(char *, char *);
extern void func_00343580(char *);
extern void func_003435A0(char *, char *);
extern char D_00259F58[];
extern char D_0025D0E0[];
extern char *D_001A8CFC[] __attribute__((sda));

int func_PAL_002D4430(void)
{
    if (D_001A8CFC[0] != 0) {
        func_003435B0(D_001A8CFC[0] + 0x3C530, 0);
        func_00343538(D_001A8CFC[0] + 0x3C530, D_00259F58);
        func_00343580(D_001A8CFC[0] + 0x3C530);
        func_003435A0(D_001A8CFC[0] + 0x3C530, D_0025D0E0);
    }
    return 0;
}

extern char D_00259CE0[];
extern char D_0025D288[];

int func_PAL_002D44B0(void)
{
    if (D_001A8CFC[0] != 0) {
        func_003435B0(D_001A8CFC[0] + 0x3C530, 1);
        func_00343538(D_001A8CFC[0] + 0x3C530, D_00259CE0);
        func_00343580(D_001A8CFC[0] + 0x3C530);
        func_003435A0(D_001A8CFC[0] + 0x3C530, D_0025D288);
    }
    return 0;
}

