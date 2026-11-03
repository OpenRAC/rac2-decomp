/* Maintainer ABI correction, 29 October 2026: the qualified EE compiler
 * measures sizeof(long) == sizeof(long long) == 8 and sizeof(void *) == 4.
 * The PR #365 trials narrowing the style argument to u32 used a false
 * interface. Their sizes are not a valid ABI-preserving improvement.
 * Restore the earlier wide-argument candidate; no new match is claimed.
 */
#include "common.h"

/* Near miss: the candidate is retail's exact 136 bytes and every call, the
 * float computation and the u64 argument are right, but three instructions
 * differ.
 *
 * Retail keeps the 256.0f in `$f2` and the 0.5f in `$f1`
 * (`mtc1 $at,$f2` ; `mtc1 $at,$f1`), this cc1 keeps them the other way
 * round (`$f1` and `$f2`); the order of the two constants in the source does
 * not change it.
 *
 * Retail also sets up the arguments of the `func_0027FAA8` call as `$a1`,
 * `$a3`, `$a2` and `$t0`; this cc1 sets up `$a3`, `$a2` and `$a1`.
 *
 * The float is read from a per-program address (0x001B23A4 in the boot,
 * 0x001B2704 in level 00), so it is a `ref_` symbol; with `-G8` the load is
 * the symbolic `l.s $f0,sym` that retail's `lui $at`+`lwc1` pair comes from,
 * and with `-G0` the address is materialised in `$v0` instead.
 *
 * The unit needs `-G8` for the symbolic load.
 *
 * Opus-1 (Claude Opus 5.5, task v2125, 3 November 2026): recompiled here,
 * this body is still 136/136 bytes, 0/28 places. Both walls come from
 * sched1. The ref load has an anti-dependence on the func_00288FB8 call, which
 * raises its priority, so it issues before the 256.0f and local-alloc gives
 * the 256.0f `$f1`. And the `$a1` copy waits on the cvt latency, so `$a3`/`$a2`
 * are set first. The following form gives all 28 of 28 places, but only with a
 * `do { } while (0)` around the call (a forbidden barrier, so not landable):
 *
 *     static __inline__ int probe_y(float value)
 *     { return (int)(value * ref_L00_002CF2B8_01 + 0.5f); }
 *     ...
 *     func_0027C540(0);
 *     func_L00_0030D608();
 *     {
 *         int y = probe_y(256.0f);
 *         do {
 *             func_0027FAA8(0x1A5, y, 0x80F0F0F0, func_00288FB8(0x2D4F), -1);
 *         } while (0);
 *     }
 *     func_0027C660();
 *     return 0;
 *
 * The loop notes split the float computation from the call setup: the 256.0f
 * is issued first (it is the inline parameter, so it has the lower LUID), and
 * `$a1` is copied first in the call block. Writing the y argument inline as
 * a call to a helper with a real `if (D_001B23A0 != 0)` test, whose two arms
 * become identical here, gives retail's float registers and argument order.
 * The only extra code is the `lui`+`lw` of D_001B23A0 (8 bytes). jump2 merges
 * the arms after flow2 has run, so nothing deletes the dead load. Retail has
 * no such load, so the original construct must end the block in the same
 * place without reading memory. Look for a register-only test or a real loop
 * in the sibling text-draw functions (func_002CDA20.c has the same pattern).
 */

extern void func_0027C540(long);

extern void func_0027C660(void);

extern void func_L00_0030D608(void);

extern s32 func_00288FB8(s32);

extern s32 func_0027FAA8(s32, s32, u64, s32, s32);

extern float ref_L00_002CF2B8_01;

int func_002CF2B8(void)
{
    s32 s0;

    func_0027C540(0);
    func_L00_0030D608();
    s0 = (s32)(0.5f + 256.0f * ref_L00_002CF2B8_01);
    func_0027FAA8(0x1A5, s0, 0x80F0F0F0, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
