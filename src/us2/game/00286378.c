#include "include_asm.h"

INCLUDE_ASM("asm/us2/game", func_US2_00286378);

/* func_US2_00287108: v2.00's own exit helper of the menu overlay: refresh, set D_0018A000 to 10, pop the state. */
extern short D_0018A000;
extern void func_002B8518(void);
extern int func_002B4B70(int, int);

void func_US2_00287108(void)
{
    func_002B8518();
    D_0018A000 = 10;
    func_002B4B70(0, 0);
}

INCLUDE_ASM("asm/us2/game", func_US2_00287140);
