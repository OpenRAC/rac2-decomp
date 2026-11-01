#include "include_asm.h"


extern short D_00152C20;
extern int D_001B1594 __attribute__((sda));
extern void func_0027C480(void);
extern void func_0027BD70(void);
extern void func_002E8BA8(void);

void func_US2_002EB740(void)
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

