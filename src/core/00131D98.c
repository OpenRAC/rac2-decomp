#include "common.h"

typedef void (*OverlayEntry)(void);

extern void shutdown_run_callbacks_once(void);
extern OverlayEntry load_boot_bin_chunks(void);
extern void FlushCache(int);
extern void ref_00131D98_00(void);

/* Run each overlay entry, install the next binary, and synchronize its caches. */
/* Runs each boot program in turn, loading the next one after each, forever. */
void run_boot_binaries(void)
{
    OverlayEntry entry;

    shutdown_run_callbacks_once();
    entry = ref_00131D98_00;
    do {
        entry();
        entry = load_boot_bin_chunks();
        FlushCache(0);
        FlushCache(2);
    } while (1);
}

/* The separately called sound initializer begins at the next eight-byte boundary. */
__asm__(".align 3");
