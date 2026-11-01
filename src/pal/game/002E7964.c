#include "include_asm.h"


INCLUDE_ASM("asm/pal/game", func_PAL_002E7B78);

extern char D_00189E20_9[];
extern char D_001A63A8_3[];
extern short D_00152C2A;
extern void func_002B72E8_1();
extern void func_002E4AC8();
extern void func_00288EA0();
extern void func_002E6D88();

/* One-shot init: raises an int flag, forces a state word outside {6,7} to 5, runs three calls, then clears a 16-bit global. */
void func_PAL_002E7E00(void)
{
    char *p = D_00189E20_9;
    char *q;
    unsigned short v;

    if (*(int *)(p + 9420) <= 0) {
        *(int *)(p + 9420) = 1;
    }
    func_002B72E8_1(0);

    q = D_001A63A8_3;
    v = *(unsigned short *)(q + 114);
    if ((unsigned short)(v - 6) >= 2) {
        *(unsigned short *)(q + 114) = 5;
    }
    func_002E4AC8();
    func_00288EA0();
    func_002E6D88(0);
    D_00152C2A = 0;
}

