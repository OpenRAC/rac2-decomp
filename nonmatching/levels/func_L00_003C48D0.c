/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 684/708 bytes, 61 differences (outer-loop base hoisting and inner-pointer scheduling). */
/* 6 November 2026, round 10: retained C is 684/708 bytes, 0/27 USA
 * places, own -O2 -G0 -ffunction-sections -fno-sched-interblock -fno-gcse unit.
 * A one-pass group around the draw loop's real timer read recovers retail's
 * s0=timer, s1=0x7F7F7F, s2=count; the draw body and countdown now agree.
 * Aligned comparison excluding relocations and shifted branch displacements:
 * 61 differing instructions, versus 69 for the round-9 C by the same method.
 * This count is not directly comparable with the older 71/84 measurements.
 * Remaining: the outer loop hoists the point base into s6 instead of keeping
 * the delta base sp+0x10 there; initial timer address/shift scheduling, inner
 * refresh-loop pointer allocation and draw-preheader address order differ.
 * New measured attempts: external entries at the outer update, guard, byte
 * offset and enabled arm give unchanged or worse code (640..684 bytes).
 * Grouped delta-base initialization saves it in s6, but spills either values
 * or next (692/700 bytes, at least 63 aligned differences). Grouping the real
 * timer offset, first guard, geometry loops or alpha tail does not improve.
 * One shared workspace struct/array ties; reusing an index/address cursor,
 * unsigned indices or one adjacent timer-table owner does not improve.
 * Disabling sched1 worsens the three strongest forms (676/692 bytes);
 * no-force-mem adds one difference; no-cse-skip-blocks/follow-jumps tie.
 * Enabling interblock scheduling ties the retained instruction sequence.
 * No forbidden source steering was used. Next useful input: evidence for
 * the outer-loop entry or genuine point/delta address lifetimes; do not
 * repeat the grouped-buffer or loop-entry variants without new evidence.
 */
/* 6 November 2026, round 9: retained C below, own unit with
 * -O2 -G0 -ffunction-sections -fno-sched-interblock -fno-gcse: 684/708 bytes,
 * 0/27 USA places, but 71 real instruction differences (aligned diff, relocs
 * masked) against 84 for the previous 700-byte form.
 * Gains: the second loop takes a `strand` pointer (`strand += 10, k++`), so
 * pass 1 reduces every k giv and pass 2 reverses the loop (count 4..0, bgez,
 * beql, increments strand/values/count/timer as retail); -fno-sched-interblock
 * keeps those increments at the loop bottom. An in-body `u32 values` holding
 * D_1B29A0 gives retail's fp at the if-start and `addu vX, s5, fp` in each arm;
 * with gcse on, PRE hoists the arm sum instead.
 * Still different: the pass-2 hoisted D_240080 (refs 8, live 152) wins a saved
 * register (s6) over the delta base sp+0x10; with `Vector *d = delta` or with
 * gcse on (which hoists sp+0x10 itself) values or next loses instead. Second
 * loop allocates s0/s1/s2 as 7F7F7F/count/timer, retail timer/7F7F7F/count.
 * Tried, not kept: goto outer loop (next spilled), s16 *values (708 bytes,
 * 92 diffs), values+timer_offset with gcse (PRE merges arms), do/while(0)
 * groups around the tail, next or i = next (one of next/values always spills),
 * timer pointer in loop 2, grey local for 0x7F7F7F, -fno-rerun-loop-opt.
 */
/* 6 November 2026: retained best is now 700/708 bytes, 0/27 USA v1.01
 * places, default -O2 -G0 -ffunction-sections (no extra per-file flags).
 * Indexed points plus next=i+1 and an explicit halfword-table byte offset
 * let the strand index die before the timer tail. This recovers the 0x120
 * frame, s3 strand index, s5 timer offset and both post-copy madd operations.
 * The single 800-byte point owner and all previous-point accesses stay bounded.
 * Still different: the point base occupies s7 rather than being rematerialized,
 * next occupies fp rather than s7, the alpha-table base is rebuilt after the
 * inner loops rather than held in fp, and second-loop pointer allocation/order.
 * Diagnostic baseline/dump objects agree: point-base pseudo 118 has 8 refs
 * over 152 insns and is allocated s7. Retail rematerialization alone does not
 * establish that its outer loop skipped loop.c; reload can rebuild hoisted bases.
 * New trials: goto outer loop 656, goto plus -fno-gcse 652, indexed next with
 * -Os 656; qcopy_nc ties indexed-next 684. Explicit timer offset yields 700;
 * an indexed first timer guard, an owning union vector and a grouped complete
 * alpha tail each tie 700. This body with -fno-rerun-loop-opt gives 688.
 * Early opacity pointer, grouped opacity base, or separate negative-arm
 * opacity pointer each give 684. Those variants are not retained.
 * Next useful experiment: promote the real alpha-table base without extending
 * the strand index's lifetime, then check rematerialization and loop allocation.
 */
/* Historical, earlier 6 November 2026: two checks, no match; then kept 696/708.
 * Plain indexed C (`func_00282CF0(delta[j], D[i][j], D[i][j - 1])`, j = 1..9, own
 * -O2 -G0 unit) gives retail's D_240070 operand but strength-reduces the outer loop
 * (frame 0x140). Writing the outer loop `for (i = 0; i < 5; i = next) { next = i + 1;`
 * gives retail's s7 = i + 1 in the beqz slot and the per-iteration sll/mult (no outer
 * givs), 684/708. Left: loop.c still hoists the D_1B2990/D_240080 addresses out of
 * the outer loop (dump: savings 2, matched refs); retail rebuilds each one, so the
 * outer loop got no loop.c work at all. Reopen with a reason the outer movables are
 * not desirable (or the loop is skipped), not with alias tricks.
 */
/* Complete-strand offset reconstruction, 2026-11-03; not linked.
 * Check: USA v1.01, -O2 -G0 -ffunction-sections -fno-rerun-loop-opt,
 * 696/708 bytes, 0/27 placements; frame 0x130 rather than retail 0x120.
 * Two int32 byte-offset streams describe previous/current points within the
 * one real 800-byte owner. Pointers form only at accessed points, not at a
 * synthetic pre-array symbol. The scalar color contract is u32 in the matched
 * renderer; its six GPR and three FP arguments consume exactly 160 input bytes.
 * This form is 696 bytes (prior indexed form 680), and still misses retail's
 * address re-materialization, loop scheduling or register allocation.
 * Reopen with independent source evidence for those operand lifetimes.
 */

/* Retained strand refresh/draw, 2026-10-28: best680/708B,0/27US.
 * Six bounded trials. Cached record pointer612; narrow no-rerun-loop-opt632;
 * explicit owner indexing680. Adding no-strength-reduce656; broad no-gcse680
 * (no improvement, rejected). Both real color loads and unsigned alpha shift
 * retain680. Best required profile -O2 -G0 -ffunction-sections -fno-rerun-loop-opt.
 * The one canonical array owns five real160B records. Retail separately forms
 * 00240070/00240080 views around adjacent points; this source preserves that
 * overlap without independent alias declarations to manufacture CSE failures.
 * Remaining gap: address re-materialization, multiply/add and store scheduling.
 * Scratch delta[10] indexes1..9 only, matching retail unused slotsp10 and
 * nine initialized delta vectorssp20..AF. Anchor16B, private minimum40B.
 * Draw002EBE88 has six GPR and three FP arguments, void contract; its 776B
 * retail loops count-1 from point1 through9, consuming exactly160 inputbytes.
 */
#include "common.h"
typedef float Vector[4] __attribute__((aligned(16)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L00_002EBE88(void *, int, int, int, u32, u32, float, float, float);
extern Vector D_L00_00240080[5][10];
extern s16 D_L00_001B2990[], D_L00_001B29A0[], D_L00_001B29B0[];
extern float D_L00_001AFF8C_gp SDATA(D_L00_001AFF8C);
extern int D_L00_001AFF24_gp SDATA(D_L00_001AFF24);
extern int D_L00_001AFF20_gp SDATA(D_L00_001AFF20);
extern float D_L00_001B29D4 __attribute__((sda));

/* Five independent ten-point strands. Both previous/current point views use
 * one canonical storage declaration, preserving their true overlap. Scratch
 * index0 is unused because differences are indexed by the target point1..9.
 * The draw helper consumes exactly ten complete16-byte points including W. */
void func_L00_003C48D0(u8 *object)
{
    Vector anchor, delta[10];
    int i, j, k, color, alternate, next;
    u32 alpha;
    Vector *strand;
    float numerator, ratio;
    qcopy(anchor, *(u8 **)(object + 0x68) + 0x30);
    for (i = 0; i < 5; i = next) {
        int timer_offset = i * 2;
        next = i + 1;
        if (*(s16 *)((u8 *)D_L00_001B2990 + timer_offset)) {
            u32 values = (u32)D_L00_001B29A0;
            for (j = 1; j < 10; j++)
                func_00282CF0(delta[j], D_L00_00240080[i][j], D_L00_00240080[i][j - 1]);
            qcopy(D_L00_00240080[i][0], anchor);
            D_L00_00240080[i][0][3] = 0.03999999910593033f;
            for (j = 1; j < 10; j++) {
                func_00282CC0(D_L00_00240080[i][j], D_L00_00240080[i][j - 1], delta[j]);
                D_L00_00240080[i][j][3] = 0.03999999910593033f;
            }
            if (*(s16 *)((u8 *)D_L00_001B2990 + timer_offset) > 0) {
                numerator = func_00283CE0(*(s16 *)((u8 *)D_L00_001B2990 + timer_offset));
                ratio = numerator / func_00283CE0(*(s16 *)((u8 *)D_L00_001B29B0 + timer_offset));
                *(s16 *)(timer_offset + values) = func_00283CF0(D_L00_001AFF8C_gp * ratio);
            } else
                *(s16 *)(timer_offset + values) = 0;
        }
    }
    strand = D_L00_00240080[0];
    for (k = 0; k < 5; strand += 10, k++) {
        int enabled;
        do { enabled = D_L00_001B2990[k]; } while (0);
        if (enabled) {
            alpha = (u32)func_00283CF0(func_00283CE0(D_L00_001B29A0[k]) * D_L00_001B29D4) << 24;
            alternate = D_L00_001AFF24_gp;
            color = D_L00_001AFF20_gp;
            if (*(s16 *)(object + 0xAA) == 0x1192)
                color = alternate;
            func_L00_002EBE88(strand, 23, 14, 10, alpha | 0x7F7F7F, alpha | color, 0.0f, 4.0f, 0.0f);
        }
    }
}
