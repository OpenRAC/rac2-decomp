#include "common.h"

/* The unit saves $ra, $s0 and $s1 in TImode slots (`sq`), so it is built with
   the -mastra-quad-saves profile. The call's failure value is the unsigned 0xFFFFFFFF, and the
   body below runs when the call returns it */
extern int D_00133E78;

extern u32 func_0011B270(int arg0);

/* Asks the system for more heap memory. If that fails, it hands back the error code. */
u32 func_00115C90(int *errnoOut, u32 increment) {
    u32 result;

    D_00133E78 = 0;
    result = ProcessKernelRequestA(increment);
    if (result == 0xFFFFFFFF) {
        if (D_00133E78 != 0)
            *errnoOut = D_00133E78;
    }
    return result;
}
