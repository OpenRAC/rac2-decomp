/* 4 November 2026 source audit: removed the call wrapper used only as a scheduling barrier.
 * The previous controlled result below is historical and cannot qualify this
 * revised draft. Production remains assembly; no linked or native credit.
 * Fresh check: 140/140 bytes, US 0/28, first mismatch +0x24. US2/PAL name absent.
 * Profile: -O2 -G0 -ffunction-sections. Reopen on a real rounding/call block witness.
 */
/* Maintainer ABI correction, 29 October 2026: the qualified EE compiler
 * measures sizeof(long) == sizeof(long long) == 8 and sizeof(void *) == 4.
 * The PR #365 trials narrowing the style argument to u32 used a false
 * interface. Their sizes are not a valid ABI-preserving improvement.
 * Restore the earlier wide-argument candidate; no new match is claimed.
 */
#include "common.h"

/* func_002CDA20 (140 bytes, boot + 27 levels), tier opus-2, 29 October 2026.
 *
 * The C below is exact in all places: check.py printed
 * "28 of 28 places match" when it replaced the marker in
 * src/game/002CD8C0.c (default -O2 -G0 unit, no -G8 sibling needed).
 * It is kept out of src/ because it depends on the non-empty
 * `do { ... } while (0)` wrapper. MATCHING-BLOCKERS.md has an open question
 * for maintainers about using that wrapper as a block barrier
 * (func_L02_003FB000, func_0033A520). If they accept the wrapper, this C can
 * land as it is.
 *
 * Without the wrapper the best result is 140/140 bytes and 0/28 places, with
 * 7 instructions differing from +0x24:
 *  - 293.0f and 0.5f go to $f1/$f2, where retail has $f2/$f1;
 *  - after the func_00288FB8 call the arguments are set up as a3, a2, a1, t0,
 *    where retail has a1, a3, a2, t0.
 * The argument order cannot be reached in one basic block. The fix result
 * (fcvt, cost 3) feeds `move a1,s0`, while the call waits only one cycle
 * (anti dependence) after the fix. So a1 is always one cycle behind `move a3,v0`,
 * in both sched1 and sched2.
 *
 * The loop notes of the wrapper make the first insn inside it (the li a0 of
 * the call) depend on every earlier set (haifa sched_analyze_insn's loop-note
 * barrier). That delays the call until a1 is ready together with a3, and a1
 * wins (5 vs 5 dependents in sched2, and the lower LUID). The barrier also
 * takes the call off the float load's dependents. The load and the 293.0f
 * then tie, so LUID decides: `k = 293.0f` must come before the expression.
 * The 293.0f is then born first and has the longer life, so local-alloc gives
 * the 0.5f $f1 first and the 293.0f $f2. Without the local (plain
 * `D_001B23A4 * 293.0f`) the arguments are right, but the float registers
 * stay swapped.
 *
 * The same retail shape (and the same wrapper result, checked as a
 * standalone compile only) fits func_002CF2B8 (256.0f, func_0029C530) and
 * probably func_002D53F0 (329.0f, 0x1A6). func_002CD3C0's retail
 * (a3, a2, t0, a1) is the unwrapped form.
 *
 * Declarations: D_001B23A4 as declared in src/game/0033C028-qcopy.c (the
 * per-program float; the sda attribute in a -G0 unit gives retail's
 * `lui $at` + `lwc1` macro load); func_0029C4C0 is the boot name of the
 * second callee (check.py resolves it in every level); the remaining
 * externs match those already in src/game/002CD8C0.c.
 */

extern void func_0027C540(long);

extern void func_0027C660(void);

extern void func_0029C4C0(void);

extern float D_001B23A4 __attribute__((sda));

extern char *func_00288FB8(int);

extern int func_0027FAA8(int, int, unsigned long, char *, int);

int func_002CDA20(void)
{
    float k;
    int y;

    func_0027C540(0);
    func_0029C4C0();
    k = 293.0f;
    y = (int)(D_001B23A4 * k + 0.5f);
    func_0027FAA8(0x1A5, y, 0x80F0F0F0, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
