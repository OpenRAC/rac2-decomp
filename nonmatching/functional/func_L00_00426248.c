/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), v0733, 29 October 2026: 240/248 bytes, 0/27 places.
 * Profile: -O2 -G0 -ffunction-sections -mno-split-addresses, standalone unit.
 * Complete declarations follow. Reusing the table offset for the resolved
 * header address restores retail's s1 header / s2 record-counter allocation.
 * Both globals use incomplete-array sda declarations to avoid address hoisting.
 * Remaining: base load is scheduled before the i*64+j sum, one global load
 * fills the j-loop branch slot, and the two loop-header nops are absent.
 * MACRO_ADDR, -g, -fno-sched-spec and -fno-schedule-insns2 leave these
 * residuals unchanged. Unsized plain arrays at -G0 hoist both addresses and
 * grow to 260 bytes; -G8 with no split addresses gives 252 bytes and hoists
 * the first address into s7. Next useful experiment needs independently
 * justified loop-header/address lifetimes, not another spelling of the loops.
 */
#include "common.h"
typedef struct Rac2Native_428d1e2cc4aa1f21_Entry {
    unsigned char unknown_00[16];
    int type_10;
    int index_14;
    unsigned char unknown_18[24];
} Rac2Native_428d1e2cc4aa1f21_Entry;

extern char *D_L00_001B1880[] __attribute__((sda));
extern char *D_L00_001B1F94[] __attribute__((sda));
extern float func_00282DF0(void *);

void func_L00_00426248(void)
{
    int i, j, k;

    for (i = 0; i < 64; i++) {
        for (j = 0; j < 64; j++) {
            char *base = D_L00_001B1880[0];
            int off = ((int *)base)[i * 64 + j];

            if (off == 0) {
                continue;
            }
            off += (int)base;
            for (k = 0; k < *(int *)off; k++) {
                Rac2Native_428d1e2cc4aa1f21_Entry *entry =
                    (Rac2Native_428d1e2cc4aa1f21_Entry *)((char *)off + 16) + k;

                if (entry->type_10 == 5) {
                    func_00282DF0(D_L00_001B1F94[0] + (entry->index_14 << 7));
                }
            }
        }
    }
}
