/*
 * func_00131DE8 (snd_StartSoundSystem counterpart, RAC1 func_0012DB68 in 989snd.c)
 * Tier: Claude Opus 5.5 (task v2100)
 * Best check: 0 of 1 places; 572 of 576 bytes; only the last call differs.
 * Build: needs its own -g8 unit (src/core/00131DE8-g8.c) with the default
 *   -O2 -G8 -ffunction-sections flags (gcse on). 00131780.c is sdk -G2 and
 *   cannot produce the $gp accesses.
 * What differs: reorg fills `jal func_00132C48`'s delay slot with
 *   `move $6,$sp`. Retail leaves a nop there, with the same final order
 *   before the jal (free[1], a2=sp, args[0], free[0], error=0).
 *   This toolchain's resource.c assigns res->volatil (it does not OR it), so
 *   a2=sp is rejected only when the store just after it (args[0]) is
 *   volatile, or when a label or asm lies between. Declaring args volatile
 *   gives the nop but reorders the stores, and it is a forbidden construct.
 *   The original construct is unknown.
 * Mixed $gp/absolute pairs: sized sda array for [0], incomplete _1 alias for
 *   [1]. MACRO_ADDR on the client and read-work structs keeps gcse from
 *   hoisting HIGHs out of the error loops: the frame stays 0x40, and s3/s4 keep
 *   hi(D_00146CC0)/hi(D_00147CC0).
 */
#include "common.h"

typedef struct {
    int pad[9];
    void *server;
    int pad28[2];
} SifClientData;

extern SifClientData D_001A7040 MACRO_ADDR;
extern SifClientData D_001A7140 MACRO_ADDR;
extern int *D_001A74A0[2] __attribute__((sda));
extern int *D_001A74A0_1[] __attribute__((sda));
extern int D_001A74A8[2] __attribute__((sda));
extern int D_001A74A8_1[] __attribute__((sda));
extern void *D_001A74B0[2] __attribute__((sda));
extern void *D_001A74B0_1[] __attribute__((sda));
extern int *D_001A74B8[2] __attribute__((sda));
extern int *D_001A74B8_1[] __attribute__((sda));
extern int D_001A74C8 __attribute__((sda));
extern void *D_001A74D0 __attribute__((sda));
extern volatile long D_001A74D8 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
extern int D_001A74F8 __attribute__((sda));
typedef struct {
    volatile int active;
    int pad4[3];
    volatile int error;
} SndReadWork;

extern SndReadWork D_001A7100 MACRO_ADDR;
extern int D_00146CC0[], D_00147CC0[], D_00148CC0[], D_00149CC0[], D_0014ACC0[], D_0014B100[];
extern char D_001A7500[], D_001A7528[];
extern void func_0011CF78(int);
extern int func_0011D450(SifClientData *, int, int);
extern void func_00115D48(const void *, ...);
extern int func_00132C48(int, int, void *);

void func_00131DE8(int flags) {
    int i;
    int args[2];
    void *server;

    D_001A74A0[0] = D_00146CC0;
    D_001A74A0_1[1] = D_00147CC0;
    D_001A74B8[0] = D_0014ACC0;
    D_001A74B8_1[1] = D_0014B100;
    D_001A74B0[0] = D_00148CC0;
    D_001A74B0_1[1] = D_00149CC0;
    if (flags & 2) {
        D_001A74F8 = 1;
    } else {
        D_001A74F8 = 0;
    }
    func_0011CF78(0);
    for (;;) {
        if (func_0011D450(&D_001A7040, 0x123456, 0) < 0) {
            func_00115D48(D_001A7500, D_001A7528, 0xB1);
            for (;;) {
            }
        }
        server = D_001A7040.server;
        i = 10000;
        for (i--; i != -1; i--) {
        }
        if (server != 0) {
            break;
        }
    }
    D_001A74C8 = 0;
    D_001A74D0 = 0;
    D_001A74D8 = 0;
    D_001A7180 = 0;
    do {
        if (func_0011D450(&D_001A7140, 0x123457, 0) < 0) {
            func_00115D48(D_001A7500, D_001A7528, 0xC6);
            for (;;) {
            }
        }
        i = 10000;
        for (i--; i != -1; i--) {
        }
    } while (D_001A7140.server == 0);
    D_001A7100.active = 0;
    *D_00146CC0 = 0;
    *D_00147CC0 = 0;
    D_001A7100.error = 0;
    D_001A74A8[0] = 0xFFC;
    D_001A74A8_1[1] = 0xFFC;
    args[0] = (int)&D_001A7100.active;
    args[1] = flags;
    func_00132C48(0, 8, args);
}
