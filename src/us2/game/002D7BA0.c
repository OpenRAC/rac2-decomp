#include "include_asm.h"

extern void func_0029D830(int *);
extern int func_0029DB28(unsigned int, unsigned int, unsigned int, int);
extern int D_001C51D0;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 D_0025A6E0;
extern int D_0025A620[];

int func_US2_002D8270(int *arg0)
{
    func_0029D830(arg0);
    *(int *)((char *)arg0 + 0xA0) = func_0029DB28(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)arg0 + 0x30;
        int index = D_001C51D0;

        if (*(int *)(base + (index << 2)) != -1) {
            D_0025A6E0.f3C = -0x240;
            D_0025A6E0.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)D_0025A620 = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)arg0 + 0xA4) = 0;
    return 0;
}

INCLUDE_ASM("asm/us2/game", func_US2_002D8320);
