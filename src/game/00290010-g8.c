#include "common.h"

/* A unit of its own so that the call to func_00290628 goes through its symbol: PAL and USA v2.00 have has
   that function as assembly at an address of its own, and a call within one object can only
   reach the object's own copy. */

extern int D_001A9000 __attribute__((sda));
extern int D_001A9004 __attribute__((sda));
extern float D_001A9008 __attribute__((sda));
extern int D_001A900C __attribute__((sda));
extern int D_001A9010 __attribute__((sda));
extern int func_00290628(void);
extern int func_002900B8(void);
extern void func_0029B7C0(int (*)(void), int (*)(void), int);
extern float func_002AA340(int *, int, int);

/* Starts or updates a screen overlay of the given mode with two values and an amount. */
void func_00290010(int mode, int first, int second, float amount)
{
    if (D_001A9000 == 0 || (D_001A9004 != 2 && mode == 2)) {
        D_001A9004 = mode;
        func_0029B7C0(func_00290628, func_002900B8, 1);
    }
    if (mode == D_001A9004) {
        D_001A900C = first;
        D_001A9010 = second;
        D_001A9008 = amount;
        func_002AA340(&D_001A9000, 10, 2);
    }
}
