#include "common.h"

/* The unit saves $ra in a TImode slot (`sq`), so it is built with the
   -mastra-quad-saves profile. */
extern int g_malloc_lock_owner;

extern int g_malloc_lock_depth;

extern int g_malloc_lock_sema;

extern void SignalSema(int arg0);

/* Releases the memory lock, and wakes a waiting thread once the last hold is let go. */
void malloc_lock_release(void) {
    if (--g_malloc_lock_depth == 0) {
        g_malloc_lock_owner = -1;
        SignalSema(g_malloc_lock_sema);
    }
}
