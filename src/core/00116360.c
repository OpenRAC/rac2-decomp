#include "common.h"

/* The unit saves $ra in a TImode slot (`sq`), so it is built with the
   -mastra-quad-saves profile. */
extern int D_001341E0;

extern int D_001341E4;

extern int D_00134DB8;

extern void SignalSema(int arg0);

/* Releases the memory lock, and wakes a waiting thread once the last hold is let go. */
void malloc_lock_release(void) {
    if (--D_001341E4 == 0) {
        D_001341E0 = -1;
        SignalSema(D_00134DB8);
    }
}
