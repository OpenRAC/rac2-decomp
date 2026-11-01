#include "include_asm.h"

#include "common.h"
extern char D_00188660[];
extern char D_L00_001B8DC0[];
extern char *D_L00_001B19EC __attribute__((section(".sdata")));
extern float func_00282E48(char *, char *);
extern int func_00282948(int *);
extern int func_L00_0035F640(int, int, char *, int);
extern int func_002A77E0(int);
extern void func_002E59F8(int);

void func_PAL_L00_00430188(char *self) {
    int *sub = *(int **)(self + 8);
    unsigned int flags;
    float distance;
    if (sub[0] < 0) return;
    distance = func_00282E48(D_L00_001B8DC0, self + 0x40);
    if (distance < *(float *)(self + 0xc)) {
        char *slot;
        flags = 0;
        if (*(u8 *)(D_L00_001B19EC + sub[0] * 32 + 0x18)) flags |= 4;
        slot = D_00188660 + sub[4] * 0x70;
        if (*(char **)(slot + 0x8c) == self && *(u8 *)(slot + 0x74)) return;
        if (func_00282948(sub + 3)) {
            sub[4] = func_L00_0035F640(sub[0], flags, self, 0x400);
            if (sub[2] > 0) sub[3] = (int)((sub[1] + func_002A77E0(sub[2] - sub[1])) * 5e+01f);
        }
    } else if (*(float *)(self + 0xc) + 1.0f < distance) {
        char *slot;
        int index = sub[4];
        if (index != -1) {
            slot = D_00188660 + index * 0x70;
            if (*(char **)(slot + 0x8c) == self && *(u8 *)(slot + 0x74)) func_002E59F8(index);
        }
        sub[4] = -1;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00430308);
