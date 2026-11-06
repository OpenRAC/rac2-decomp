/* 6 November 2026, round 4: best body below (492/492, 0/2 places, 10 words). Own unit
 * (src/levels/shared/L04_00416E38.c), -O2 -G0 -ffunction-sections -fno-gcse. The
 * func_00326A10 dead-test rounding helper gives the ghost $s2 and the block boundaries;
 * `ky = 371.0f` after the first rounding gives retail's f22/f21 roles, and the floats-first
 * prototype of func_0029B658 (as func_L04_00417028's note) gives the second draw's argument
 * order. Left: the second draw's two rounding results in v1 (retail v0; the regalloc dump
 * shows each result conflicting with the dead mode load, local-allocated to v0, and with
 * hard v0 from the fix scratch), x4's load/temporary v0/v1 swapped and x4/y4 in s1/s0
 * (x4 has 2 refs, y4 3). Hill-climb over declaration and top-assignment order (350 runs,
 * scratchpad m5g/hc.py) found nothing better. `x4 = D; x4 /= 2;` puts x4 in s0 but loads
 * into it (14 rows); nested y4, a width temporary, swapped test operands: no change;
 * a group around x4 (26), the dead-store-before helper (476 bytes), y4 first (size change).
 */
/* func_L04_00416E38 - 492 bytes, places 04:00416E38 and 11:00406938.
 * Retained C below: tier opus-1 (v1645), rechecked by opus-2 (v1724), 31 October 2026.
 * Tier opus-2 (v1823), 31 October 2026: C below retained, recompiled here: 488/492, 0/2 places, 95 cdiff
 * rows differ, link values included. Measured on the overseer's lead (a test that vanishes, as in func_002D3D88); it did not work:
 * - Retail has no load for a mode: its only GPR load is D_001A7340, for x4. func_002D3D88's helper with
 *   mode = D_L04_001B2D40 (assumed by analogy with D_001B23A0/D_001B23A4, not evidenced) gives 576/492:
 *   lw $s2 stays, and the arms rematerialize the scale, 263/371 and 0.5 per rounding.
 * - Its test on the previous coordinate (y = sc(x, 371.0f, 0)), a placeholder anyway: 496/492.
 * - if (r != 0) return r + adjust; return r; with adjust 0, r being the rounded value: 472/492, 120
 *   rows differ, the same as plain C. Testing an unset mode instead also interleaves the chains.
 * No-else arms after a fix, on an otherwise unset local; none is admissible, all shape probes:
 * - Two constants used once each (if (y != 0) { w = 130; h = 384; }): set and test gone, but sched2
 *   hoists the constants above the chain, so no boundary is left there. The same arm after each y,
 *   with the colour set at the top: 484/492.
 * - Two constants used twice each: sets and branch stay in the output.
 * - One large constant (if (y != 0) color = ...): movn.
 * $s2: a colour local at the top is propagated (no pseudo); a box pointer local stays as
 * addiu $s0,$sp,0x10. Neither gives the empty save. func_L00_004003F0's note reads it as
 * fix_truncsfsi2's reload scratch, never printed, and lists this function; that fits better than the
 * pseudo inference below, but was not re-measured here, and that note finds no C shape reaches it.
 * Options on the reused-temporary plain C, all 472/492: -g, -fno-sched-interblock,
 * -frac2-keep-block-order, -ffast-math, -fno-expensive-optimizations, -fno-gcse, -fno-schedule-insns2,
 * -fno-schedule-insns with -fno-sched-interblock or -g.
 *
 * Best check.py: 488/492 bytes, 0/2 places, 93 of 123 words differ apart from link values (USA
 * v1.01), default -O2 -G0 -ffunction-sections. Not admissible as it stands: it uses a
 * do { } while (0) wrapper. No exact-bytes form was found.
 *
 * opus-2 evidence (the barrier is at the fix, and it is a real block boundary):
 * - Measured: a volatile asm with outputs in place of each (int) cast, which makes only that
 *   insn a scheduling barrier and does not flush cse (it is not a bare ASM_OPERANDS),
 *     __asm__ __volatile__("cvt.w.s %1,%2\n\tmfc1 %0,%1" : "=r"(i), "=&f"(t) : "f"(f));
 *   gives 484/492 and retail's whole order, which do/while cannot give because its LOOP_BEG note
 *   is a barrier in front of y: mfc1 v0,f2; mul.s; mtc1 v0,f12; cvt.s.w; add.s; cvt.w.s;
 *   mfc1 v0,f1; mtc1 v0,f13. So nothing bounds the start of a rounding, only its end. A probe,
 *   not a proposal: retail's allocation below shows the original is not this asm.
 * - Read from retail: 263/371/0.5, the scale when it spans x and y, x and y, and x4 (sra s0,v1,1)
 *   are never tied to a dying operand; 222/479/349 are (mul.s f0,f1,f0). combine_regs refuses a
 *   pseudo with reg_qty < 0 (not local to a block, or dying more than once). Only values that
 *   span a rounding are untied, so we infer retail has several basic blocks at allocation.
 *   Single-block forms keep tying: mul.s f20,f0,f20 and sra s0,s0,1 here.
 * - The boundary survives sched2 (the argument loads and swc1 f21 do not fill the mul/add latency
 *   slots) and leaves no branch, so jump2 deletes it: the only later pass that removes a jump to
 *   the next insn. A jump already at .+1 in flow2 is gone before sched2 (tidy_condjump_fallthru),
 *   so its arm must die in flow2's own life analysis. The test must be a bare beq/bne/bltz form:
 *   delete_computation would leave any feeding compare behind.
 * - cse keeps 263/371/0.5 across the boundaries, so no join with two predecessors: an `if` with
 *   no else (cse skip-block). Measured: identical arms on an unset local, if (c) A else A, give
 *   504/492 and rematerialize the constants per block; that local took $s0, as its last test came
 *   before x4/y4 were set.
 * - Measured arms: a single small-constant set is if-converted (movz/movn, no block). In a
 *   two-set arm the branch stays, the small-constant set disappears and its use is the constant
 *   (inferred: reload's reg_equiv_constant). That is the shape "live at flow1, dead at flow2"; it
 *   would also explain $s2 (inferred): a call-crossing pseudo whose references vanish after
 *   allocation leaves regs_ever_live set. No arm tried here reproduces retail.
 * Next: the source construct after each rounding (no-else if, arm dead only after reload), which
 * is likely shared with func_0033C028, func_0033A520 and func_002900B8. Placeholder conditions and
 * identical arms are not admissible for now; func_0033C028's landed form flushes cse here.
 *
 * Earlier notes (opus-1):
 *
 * What retail shows: every scale-and-round (D_L04_001B2D44 * K + 0.5f, then cvt.w.s) is
 * computed serially in $f0 with the scale in $f1, the fix result goes straight to its argument
 * register, the constants 263/371/0.5 stay in $f22/$f21/$f20 and are loaded only where first
 * used, and no argument set-up (li a2..t1, li.s f14/f15, the 9-argument call's t0..t3) is
 * hoisted above the roundings. Plain C (inline casts, a static inline helper, separate int
 * temporaries) lets sched1 interleave the x and y chains, hoist the li.s constants and the
 * argument loads, and lets combine move each fix to the argument copy: 472-480 bytes.
 *
 * Found here: (1) one float temporary f and one scale temporary s reused by every rounding
 * (f = s * K; f += 0.5f; v = f;) gives retail's $f0/$f1/$f2 use (480 bytes plain, all FP
 * registers right with -fno-schedule-insns but then sched2 still hoists the argument loads);
 * (2) the colour 0x80F0F0F0 is passed sign-extended (lui/ori): a 32-bit int value (here a local
 * int), not a 64-bit constant; (3) wrapping each rounding in do { } while (0) (macro below)
 * gives retail's whole first and third groups: the loop notes act as scheduler barriers.
 * Whether such a wrapper is admissible is the open question in docs/MATCHING-BLOCKERS.md
 * ("A non-empty do { ... } while (0) as a block barrier"); this is the same family as
 * func_0033A520 (a block boundary after a scale-and-round) and func_L04_00417028.
 *
 * Still different with the macro:
 * - retail saves and restores $s2 (sd at 0x40, ra at 0x48) without ever using it; this C has
 *   no third callee-saved GPR (8 bytes). Likely a pseudo given $s2 by global-alloc that a
 *   real block boundary would make global (see func_0033A520's note), not reproduced.
 * - second group: retail converts x to float (mtc1 v0,f12; cvt.s.w) before y's fix, reusing
 *   $v0, with y's mul scheduled between; here both conversions follow the y macro (x in $v1).
 *   The conversion inside the macro is merged into the f12 copy by combine either way.
 * - last group: retail loads the scale into $f0 and 349.0 into $f1 (a plain expression, not the
 *   s temporary) interleaved with D_001A7340 / 2; a plain expression here regresses to 484.
 * - third group: retail sets a3 = 44 before t0..t2, here it goes to the jal delay slot.
 * Next: find the original construct that ends a block after each rounding but leaves no
 * branch (compare func_0033C028's identical-arm if, already in src/), and the $s2 pseudo.
 */
#include "common.h"

extern float D_L04_001B2D44 __attribute__((sda));
extern int D_L04_001B2D40 __attribute__((sda));
extern int D_001A7340 __attribute__((sda));
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_0029B658(float, float, float, float, int, int);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern char *func_00288FB8(int);
extern void func_00280200(void *, unsigned long long, char *, int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);

static __inline__ int menu_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L04_001B2D40 == active)
        scaled = 1.0f;
    return result;
}

void func_L04_00416E38(void) {
    char box[32];
    float s, half, ky, kx;
    int x1, y1, x3, y3, x4, y4, on;

    half = 0.5f;
    on = 1;
    kx = 263.0f;
    s = D_L04_001B2D44;
    x1 = menu_coord(kx, s, half, on);
    ky = 371.0f;
    y1 = menu_coord(ky, s, half, on);
    func_0027EB88(x1, y1, 130, 384, 96, 0x60442D00);
    s = D_L04_001B2D44;
    func_0029B658((float)menu_coord(kx, s, half, on), (float)menu_coord(ky, s, half, on),
                  130.0f, 384.0f, 96, 0x55F0C070);
    s = D_L04_001B2D44;
    x3 = menu_coord(222.0f, s, half, on);
    y3 = menu_coord(479.0f, s, half, on);
    func_002802E0(box, x3, y3, 44, 468, 256, 299, 16, 3);
    func_00280200(box, (int)0x80F0F0F0, func_00288FB8(0xA41), -1);
    x4 = D_001A7340 / 2;
    y4 = menu_coord(349.0f, D_L04_001B2D44, half, on);
    func_0027FB40(x4, y4, (int)0x80F0F0F0, func_00288FB8(0x2F2C), -1);
}
