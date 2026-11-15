#include "common.h"

/* The unit saves $ra, $s0 and $s1 in TImode slots (`sq`), so it is built with
   the -mastra-quad-saves profile. D_00133E74 is re-read after every call
   because a callee may store to it, which is what retail does. */
extern void *D_00133E74;

extern void malloc_lock_acquire(void *arg0);

extern int malloc_reentrant(void *arg0, int arg1);

extern void malloc_lock_release(void *arg0);

/* Gets a block of heap memory of the given size, taking the memory lock while it works. */
int malloc(int size) {
    int result;

    malloc_lock_acquire(D_00133E74);
    result = malloc_reentrant(D_00133E74, size);
    malloc_lock_release(D_00133E74);
    return result;
}
