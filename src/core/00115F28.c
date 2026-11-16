#include "common.h"

/* The unit saves $ra, $s0 and $s1 in TImode slots (`sq`), so it is built with
   the -mastra-quad-saves profile. D_00133E74 is re-read after every call
   because a callee may store to it, which is what retail does. */
extern void *g_libc_state_record;

extern int malloc_lock_acquire(void *arg0);

extern void *malloc_reentrant(void *arg0, int arg1);

extern void malloc_lock_release(void *arg0);

/* Gets a block of heap memory of the given size, taking the memory lock while it works. */
void *malloc(int size) {
    int result;

    malloc_lock_acquire(g_libc_state_record);
    result = malloc_reentrant(g_libc_state_record, size);
    malloc_lock_release(g_libc_state_record);
    return result;
}
