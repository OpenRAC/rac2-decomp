/* 6 November 2026, round 10c: no gain (14 rows by real count, 13 runs). Retail needs priority obj > base > stride > p; our base is 0.125 because of the REG_EQUIV `*= 2` (local-alloc.c:855), 0.25 without it, so it also needs a second set that combine cannot fold. Reusing n for obj[0x23] in case 2 (17 rows) lifts stride to 0.300, just under p's 0.304; case orders, per-case p reads and idx locals with groups are worse. */
/* 6 November 2026 (round 10): best now 412/412 bytes, 0/1 USA, 15 real rows, in its
 * own unit with -O2 -G0 -ffunction-sections -fno-schedule-insns (29 units use it).
 * Mechanism: tbl/n are reused in cases 1/2 (record pointer, call result); combine
 * absorbs those refs, and without sched1 REG_BASIC_BLOCK is not recomputed, so
 * base/stride stay global: obj s0, stride s2, hi temp v0, case 0 beql/lh and size
 * match. Left: p s1 / base s3 (retail base s1, p s3) and case 1 v0/v1 swapped.
 * Priorities (global.c): obj .415 > p .304 > stride .139 > base .125; base/stride
 * lengths are doubled by REG_EQUIV. Groups weight p's lh as much as base/stride
 * (y/z forms: p rises); only ~7 nested groups on the sets would reorder. With
 * sched1 on, the same C is 416 (sched recomputes REG_BASIC_BLOCK to block 6).
 * Case 1 `n = idx; &D[n * 0x150]` gives 14 rows but puts idx in s2.
 * No help: -flive-range, -funroll-loops loops (400-408), case-0 forms with a
 * record/index local, struct-array table, float local, switch-value local.
 */
/* 6 November 2026 (round 9): still 416/412 bytes, 0/1 USA. The extra word is
 * case 0's first `lh a1, 0x36(p)`: retail fills the beql slot with it (s0 = obj is
 * live there), ours fills it with `ld s0` because local-alloc gives the table base
 * s0. Base and stride are single-block, single-death pseudos (local-alloc.c:359),
 * so they are allocated before obj. Note: the base length 42 is REG_LIVE_LENGTH
 * doubled for its REG_EQUIV note, so even as globals the order would be obj
 * (39/71) > p (14/34) > base (10/42) > stride (10/50), not retail's base/stride
 * before p. Proof: one `tbl`/`n` variable set in all three cases makes them
 * global: obj s0 and case 0's beql/lh layout match retail, but p s1, base s2,
 * stride s3, and cases 1/2 use s2/s3 (408/412). No change (416) from
 * -fno-rerun-loop-opt, -fno-regmove, -fno-rerun-cse-after-loop, -fno-gcse,
 * -fno-strength-reduce, -fno-schedule-insns(2), -fno-caller-saves, -fexceptions,
 * -g, -O3, -ffast-math, -fmove-all-movables, -frac2-sticky-volatile-refs,
 * -frac2-keep-block-order/-zero-copy, -frac2-gcse-unsplit-edges, -frac2-qcopy.
 * Per-call groups (with/without -fno-rerun-loop-opt, -fno-gcse) 416-428; table
 * hoisted to the top 400; if-chain 384; case reorders 404-416; a 3-step loop
 * with -funroll-loops 408. Needs base/stride global AND above p.
 */
/* 6 November 2026: default game G0, best C remains 416/412 bytes, 0/1 USA.
 * New bounded trials: group the initializer call, group its record-address
 * calculation, group the middle append call, or group the complete four-call
 * initialization sequence. Each gives 420/412, with obj in s3, p in s2,
 * table in s0 and stride in s1: none promotes the table/stride as required.
 * -fno-expensive-optimizations gives 404/412, drops the saved FP zero and
 * retains the wrong integer allocation. -fno-local-alloc is unsupported.
 * Read-only RAC1/RAC4 searches found no corresponding initialization donor.
 * Stop the tied grouping approach; retain the older best body below.
 */
/* 4 November 2026 current-RAC1 source-method trial; retained, not linked.
 * Two new real-operation group trials (the first append call and the state-pointer read) each
 * produce 420/412 bytes, 0/1 USA placements. Neither promotes table/stride allocation as
 * required; the older best C below is retained.
 */
/* opus-1 xhigh, USA v1.01: 416 bytes / 412 retail, 0 of 1 places match.
 * (The earlier form of the alpha test, >= 2 first, gives 412/412 with the wrong
 * final layout; the arm order below reproduces retail's layout.)
 * The remaining rows appear to follow from one allocation difference: retail has obj s0,
 * table base s1, stride s2, p s3; here base s0, stride s1, obj s2, p s3.
 * Base and stride are single-block, single-death pseudos in case 0, so local-alloc
 * takes them first and ties the %hi temp to the base. Retail's `lui v0` then
 * `addiu s1, v0` shows both were global pseudos there. The extra 4 bytes and both
 * dispatch delay slots come from this: `ld s0` can fill them only while s0 is dead
 * in case 0; with obj in s0 reorg must steal `lh a1` into a beql.
 * Priorities (floor_log2(refs) * refs / length) would need obj > base > stride > p:
 * obj 13 refs, length 71 = .549; base 5, 21 = .476; p 7, 34 = .412; stride 5, 25 = .400
 * (base and stride lengths are local-alloc qty lengths halved, an estimate).
 * So stride also needs length <= 24, or p length >= 36, and any added ref of p
 * (8 refs) lifts p above obj. A test between the AC0 calls does make both global
 * (obj s0, lui v0) but then gave p s1, base s2, stride s3 and leaves its own words.
 * The split probably lies after the first AC0 call, since mtc1 f20 sits above the A98
 * call in the same block. No allowed construct found that splits it and leaves no code.
 * No change from: -G8 unit, explicit base/stride locals, typed record array.
 * Declarations needed are below; compiled in the plain .c unit, not linked.
 */
#include "include_asm.h"
#include "common.h"

extern char D_L03_00259A30[];
extern void func_L00_00322A98(u8 *, char *);
extern void func_L00_00322AC0(char *, s32, s32, float);
extern void func_L00_00322BE0(char *, s32);
extern void func_L00_00322EC8(char *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_00273B70(u8 *);
extern void func_0029F338(void *);

void func_L03_00421930(u8 *obj)
{
    u8 *p = *(u8 **)(obj + 0x68);
    char *tbl;
    s32 n;

    switch (obj[0x20]) {
    case 0:
        tbl = D_L03_00259A30;
        n = 0x150;
        func_L00_00322A98(obj, &tbl[*(s16 *)(p + 0x36) * n]);
        func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0x28, 2, 0.0f);
        func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0x14, 4, 0.0f);
        func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0xA, 6, 0.0f);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * 0x150];
        func_L00_00322BE0(tbl, 0);
        n = func_00273B70(obj);
        if (n != 0) {
            func_002A7750(obj, 2, -1);
            *(u16 *)(obj + 0x34) |= 0x2800;
        }
        break;
    case 2:
        func_00273B70(obj);
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * 0x150];
        func_L00_00322EC8(tbl);
        if (obj[0x23] < 2) {
            func_0029F338(obj);
        } else {
            obj[0x23] -= 2;
        }
        break;
    }
}
