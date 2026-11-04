/* 4 November 2026 current-RAC1 source trials; retained, not linked.
 * A real phase-calculation group remains 276/276 bytes, 0/1 USA, first +0x64. Defining the
 * consumed cycle factor before the period call instead gives 284/276 bytes, 0/1. Neither fixes
 * the remainder/constant allocation. The original 276-byte body below remains the best draft; no
 * argument-bank width, return contract or global qualifier changed.
 */
/* 2026-11-03 w02 source-contract review (USA v1.01 only).
 * Profile: -O2 -G0 -ffunction-sections.
 * Current check.py: 276/276 bytes, 0/1 places, first mismatch +0x78.
 * Corrected func_002AA548 to its actual float return. The modulo and 120/tau FP scratch-register choices remain different.
 * Reopen: Independent sched1 constant-creation/lifetime evidence; documented tau/wrapper controls tie.
 * No linked match or cross-release qualification is claimed. Earlier notes follow.
 */
/* Claude Opus 5.5 xhigh (opus-1), v2049, 2026-11-01: NOT MATCHING.
 * USA v1.01: 276/276 bytes, 0 of 1 places; 13 of 69 check rows differ, 4 of them
 * relocation-only jal rows and 9 registers. Profile: default L16_00403900.c flags
 * (-O2 -G0 -ffunction-sections).
 *
 * Remaining: only register colours. The D_L16_001B2648 load is $v1 where retail
 * has $a0, mfhi is $a0 where retail has $v1, 120.0f is $f2 where retail has $f0,
 * and 2*pi is $f0 where retail has $f2. Frame, order and all other operands agree.
 *
 * Solved here: the period call through an inline wrapper stops cse merging the two
 * 120.0f literals, so the accumulator takes $f20 and the constant reloads, which is
 * what the 28 October notes could not reach. MACRO_ADDR gives the lui/lw pair.
 *
 * What should fix it: retail's sched1 order must differ, since local-alloc gets
 * mod before D only when 2*span(D) > 3*span(mod) (insn distances, for example 5 and
 * 3, or 4 and 2), and floats 120 -> pi -> 2*pi only when
 * span(120) <= span(pi) < span(2*pi). One fitting sched1 order is
 * D, period copy, 2*pi, trap, div, 120, float, pi, div.s, mul.s, sub.s. Sched2 then
 * sorts by priority back to the retail order. Mine schedules 120 before the trap.
 * Sched1 ties break by constant LUID, so a wording that creates 2*pi before 120
 * is the thing to look for.
 *
 * Negative controls, same 13 rows: `period = wrapper(120.0f); tau = 6.2831855f;`
 * with tau used in the product; an inline
 * `angle(int frame, float period, float offset)` with the 2*pi inside it.
 *
 * Declarations: all below. L16_00403900.c already declares func_00283CF0.
 */
#include "common.h"
extern s32 func_00283CF0(float);
extern s32 D_L16_001B2648 MACRO_ADDR;
extern float func_00283198(float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_L16_00412F48(u8 *);
static inline s32 func_L16_00411368_period(float seconds)
{
    return func_00283CF0(seconds);
}

void func_L16_00411368(u8 *arg)
{
    u8 *s0;
    u8 *s1;
    float f20;

    s0 = arg;
    s1 = *(u8 **)(arg + 0x68);
    f20 = 10.0f;
    if (s0[0x20] == 0xD || s0[0x20] == 0xF || s0[0x20] == 0xE || s0[0x20] == 0x11)
        f20 = 25.0f;
    f20 = f20 + func_00283198((float)(D_L16_001B2648 % func_L16_00411368_period(120.0f)) / 120.0f * 6.2831855f - 3.1415927f);
    func_002AA548(s0 + 0x18, s1 + 0x268, *(float *)(s1 + 0x264) + f20,
                  0.0083333338f, 0.0027777778f, 0.16666667f);
    func_L16_00412F48(s0);
}
