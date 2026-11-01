#include "include_asm.h"



extern void func_002B0990(char *, char *, int, int, float);
extern void func_L00_002E6EF8(void (*)(char *), char *);
extern void func_L02_003D5F50(char *, int, int);
extern void func_L02_003D62F0(char *);
extern char *D_0018C2BC;

void func_PAL_L02_003D8738(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x95) == 2 ||
        *(unsigned char *)(arg0 + 0x20) == 0x12) {
        func_L02_003D5F50(arg0, 2, 0);
        func_L02_003D5F50(arg0, 3, 1);
    }
    func_L00_002E6EF8(func_L02_003D62F0, arg0);
    if (*(unsigned short *)(arg0 + 0x96) < 0xFFFF) {
        (*(unsigned short *)(arg0 + 0x96))++;
    }
    if (D_0018C2BC != 0 &&
        (D_0018C2BC == arg0 || *(short *)(D_0018C2BC + 0xAA) == 0x9F8)) {
        *(short *)(state + 0x32A) = -1;
    }
    *(unsigned short *)(state + 0x32A) = *(unsigned short *)(state + 0x32A) + 1;
    *(unsigned short *)(state + 0x32E) = *(unsigned short *)(state + 0x32E) + 1;
    func_002B0990(arg0, state + 0x340, 6, 1, 2.5f);
}

