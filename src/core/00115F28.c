#include "common.h"

/* The unit saves $ra, $s0 and $s1 in TImode slots (`sq`), so it is built with
   the -mastra-quad-saves profile. D_00133E74 is re-read after every call
   because a callee may store to it, which is what retail does. */
extern void *D_00133E74;

extern void func_00116300(void *arg0);

extern int func_001166C8(void *arg0, int arg1);

extern void func_00116360(void *arg0);

/* Gets a block of heap memory of the given size, taking the memory lock while it works. */
int func_00115F28(int size) {
    int result;

    AcquireMallocLock(D_00133E74);
    result = MallocReentrant(D_00133E74, size);
    ReleaseMallocLock(D_00133E74);
    return result;
}
