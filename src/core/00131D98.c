#include "common.h"

typedef void (*OverlayEntry)(void);

extern void func_0011FC48(void);
extern OverlayEntry func_00131CB8(void);
extern void func_0011AEA0(int);
extern void ref_00131D98_00(void);

/* Run each overlay entry, install the next binary, and synchronize its caches. */
/* Runs each boot program in turn, loading the next one after each, forever. */
void func_00131D98(void)
{
    OverlayEntry entry;

    RunShutdownCallbacksOnce();
    entry = ref_00131D98_00;
    do {
        entry();
        entry = LoadBootBinChunks();
        FlushCache(0);
        FlushCache(2);
    } while (1);
}

/* The separately called sound initializer begins at the next eight-byte boundary. */
__asm__(".align 3");
