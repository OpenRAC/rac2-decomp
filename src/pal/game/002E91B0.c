#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002E91B0);




INCLUDE_ASM("asm/pal/game", func_PAL_002EA0B0);

extern short D_00152C20;
extern int D_001B1594 __attribute__((sda));
extern void func_0027C480(void);
extern void func_0027BD70(void);
extern void func_002E8BA8(void);

void func_PAL_002EB800(void)
{
    switch (D_00152C20) {
    case 0:
    case 3:
        func_0027C480();
        break;
    case 1:
        D_001B1594 = 127;
        func_0027BD70();
        break;
    case 2:
        func_002E8BA8();
        break;
    }
}

