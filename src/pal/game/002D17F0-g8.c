#include "common.h"

/* func_PAL_002D17F0, the PAL copy of func_002D08C8: the same C, without the
   second flag test; the last store goes to element 2 instead of 3. */

extern int D_001A8CFC;
extern int ref_002D08C8_01 __attribute__((sda));
extern int D_001F2848[];
extern int D_001ABA0C[4] __attribute__((sda));
extern unsigned char D_001A7A0A;

int func_PAL_002D17F0(void)
{
    if (D_001A8CFC != 0) {
        D_001F2848[0] = 1;
        if (ref_002D08C8_01 != 0)
            D_001ABA0C[1] = 1;
        if (D_001A7A0A != 0) {
            D_001ABA0C[0] = 1;
            D_001ABA0C[2] = 1;
        }
    }
    return 0;
}
