#include "include_asm.h"

/* func_PAL_L00_002D6E48, PAL's own: whether the global state is 98, 99 or 100. */
extern int D_0018C0B4;

int func_PAL_L00_002D6E48(void) {
    int state = D_0018C0B4;
    int result = 0;

    if (state < 101) {
        result = state >= 98;
    }
    return result;
}
