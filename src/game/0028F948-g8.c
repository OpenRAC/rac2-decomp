#include "include_asm.h"
#include "names.h"

extern int D_L00_001A8F00;
extern int D_L00_001A9350 __attribute__((sda));
extern int D_L00_001A9090 __attribute__((sda));
extern int func_00282948(void *);
extern void func_0029B810(int);
/* Checks for a button press while the gauge pop-up is shown and, if so, asks the pop-up system to close it. */
int func_00290628(void)
{
    if (D_L00_001A8F00 == 0 && FastFloatHelperD(&D_L00_001A9350) != 0)
        ClearLevelObjectTableEntry(1);
    return D_L00_001A9090;
}

extern int D_001A9000 __attribute__((sda));
extern int D_001A9004 __attribute__((sda));
extern float D_001A9008 __attribute__((sda));
extern int D_001A900C __attribute__((sda));
extern int D_001A9010 __attribute__((sda));
extern int func_002900B8(void);
extern void func_0029B7C0(int (*)(void), int (*)(void), int);
extern float func_002AA340(int *, int, int);
