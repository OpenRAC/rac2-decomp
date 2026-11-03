/* Current C reconstruction, 2 November 2026; not linked or counted.
 * Default game -O2 -G0 -ffunction-sections. USA v1.01 local check:1/1,
 * 80/80 bytes, including independently evidenced file-scope eight-byte
 * alignment after the closed loop (current RAC1 tfragfunc.c precedent).
 * Without alignment, the actual loop is76 bytes and all words agree.
 * The former note's control-flow reading was wrong: the back edge reaches
 * entry(), not only the two synchronization calls. ParseBin returns the next
 * entry pointer, used on the next loop iteration (RAC1 boot.c agrees).
 * USA v2.00 and PAL still catalogue656 bytes: this80-byte main followed by
 * the576-byte sound initializer. Their unpadded checks fail76/656; final
 * aligned C is not accepted across releases while those rows are merged.
 * Reopen after release-qualified catalogue carry/split at main+0x50; then
 * rerun every carrying check and the strict linked build. Keep the marker.
 */
#include "common.h"

typedef void (*OverlayEntry)(void);

extern void func_0011FC48(void);
extern OverlayEntry func_00131CB8(void);
extern void func_0011AEA0(int);
extern void func_0026EDE8(void);

/* Run each overlay entry, then install the next binary and synchronize. */
void func_00131D98(void)
{
    OverlayEntry entry;

    func_0011FC48();
    entry = func_0026EDE8;
    do {
        entry();
        entry = func_00131CB8();
        func_0011AEA0(0);
        func_0011AEA0(2);
    } while (1);
}

/* Retail aligns the following body to eight bytes after the closed back edge. */
__asm__(".align 3");
