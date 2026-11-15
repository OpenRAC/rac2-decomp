#include "common.h"

/* The unit saves $s0, $s1 and $ra in TImode slots (`sq`), so it is built with
   the -mastra-quad-saves profile. func_00116300 and func_00116360 are declared
   with the argument retail passes; they ignore it. */
extern void *D_00133E74;

extern void func_00116300(void *arg0) __asm__("func_00116300");

extern void FreeReentrant(void *arg0, int arg1);

extern void func_00116360(void *arg0) __asm__("func_00116360");

/* Gives a block of heap memory back, taking the memory lock while it works. */
void func_00115F78(int block) {
    malloc_lock_acquire(D_00133E74);
    FreeReentrant(D_00133E74, block);
    malloc_lock_release(D_00133E74);
}
