#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002EBA30);

typedef struct { char pad[0x30]; int selected; char gap[0x3C]; int destination; } State2EB158;
extern State2EB158 D_001B8840;
extern char D_0014B540[];
extern int func_002B7B18(int, int, int);
extern void func_002B7CE0(int);

int func_PAL_002EC070(int index)
{
    char *table = D_0014B540;
    int row = D_001B8840.selected * 0x14C;
    int destination = D_001B8840.destination;
    int base = (int)(table + 0x3EA8);
    int first = *(int *)((index << 2) + row + base);
    int count = *(int *)(((index + 1) << 2) + row + base) - first;
    if (count > 0) {
        func_002B7B18(destination, first + *(int *)(table + 0x3E24), count);
        func_002B7CE0(0);
    }
    return 1;
}

