/* 8 November 2026 (re-measure on new master compiler: default set-side sticky volatile, mtc1 hazard fix): flat form unchanged, 412/412, 0/1 USA, 11 real rows (same p s1 / base s3 swap). No RAC1/RAC4 donor; the sibling EntryGroup view (func_L03_00421398) is the same address arithmetic; no sym+offset address, so -Wa,--r5900-la-addend=sn does not apply. New trials (13 check.py runs): inline group(p) helper with literal 0x150 -> 416 bytes, 70 rows; s16 *ip = p + 0x36 for case 0 reads -> cse folds back, 11; flags -fno-cse-skip-blocks, -fno-thread-jumps, -fno-strict-aliasing, -fno-inline-functions, -fsched-spec-load, -frac2-keep-block-order tie at 11; -fforce-addr 15; -fno-cse-follow-jumps 416 bytes. */
/* 8 November 2026 (REG_EQUIV round): dropping the REG_EQUIV REG_LIVE_LENGTH *= 2 (and four other equivalence probes) leaves 12 masked words; that probe changes 3181 matched units. SN 2.95.2 keeps the doubling. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 412/412 flat form, 11 rows from one register swap (global-alloc needs obj > base > stride > p; only padding-like nested groups reorder them). */
/* 7 November 2026, FINAL: no match. Retained best is the flat C below (no groups): 412/412, 0/1 USA v1.01, own unit -O2 -G0 -ffunction-sections -fno-schedule-insns, 11 real rows, scheduling exact. Blocker: one register swap, p s1 / table base s3 (retail base s1, p s3); global-alloc priority needs obj > base > stride > p but gets obj .415 > p .298 > stride .143 > base .139, and only loop-depth weight can lift base/stride. The 2-difference grouped form (comment at the end) needs nested depth-4/depth-6 do/while(0) padding, so it is not kept.
 * Final-round trials (17 check.py runs): reusing n/an int-typed base for obj[0x23] or the 0x34 halfword in cases 1/2 reorders priorities (n reuse: obj, stride, p, base; base reuse: obj, base, p, stride) but the reused value then sits in an s register (retail v1) and case 2's test turns signed: 15-21 rows. A real 3-step loop for the (0x28,2)/(0x14,4)/(0xA,6) calls with -funroll-loops unrolls fully and gives base > stride > p, but obj drops to last and 0.0f is rematerialised per call (no f20): 408 bytes, 59 rows.
 */
/* 6 November 2026, round 11c: flat form stays at 11 rows. Local-alloc priorities (refs/length after REG_EQUIV x2): obj .415 (13/94) > p .298 (7/47) > stride .143 (5/70) > base .139 (5/72). The base would need 8 refs to pass p; without REG_EQUIV it reaches only .278. Setting tbl/n in cases 1/2 lengthens base/stride (352/392) and drops them further; typed-array forms bring back the 416-byte layout. Only loop-depth weighting (groups) reorders them. */
/* 6 November 2026, round 11b (13 more check.py runs): no match.
 * Call-3 fixes tried on the two-difference C below, each still two: call 3's
 * lh read into `index` inside the group after call 2; the whole offset
 * `index = lh * n` inside the group; 0x14/4 from locals set in the group
 * (cse folds them back). sched2 still has mov.s f12,f20 and the mult ready in
 * the same cycle, and the mult wins on priority. Any group end between calls
 * 1 and 4 does this to the next call.
 * Flat form (no do/while groups and no `zero` local; case 0 is just index, n,
 * tbl and the five calls in order, cases 1/2 as below): 412/412, 11 real
 * rows, ALL from one register swap (p in s1, table base in s3; retail p s3,
 * base s1). Scheduling there matches retail exactly. Priorities: obj .415 >
 * p .298 > n .143 / tbl .139. Single-level groups cannot fix it: one level
 * adds at most +1 per statement, which leaves tbl at 10 refs or fewer, while
 * any group over a call-3/4 lh also lifts p (47 long). Measured: one group from
 * the block start through call 2 gives 28-30 rows, from the block start through
 * the end 35, around n and tbl separately 13, plus one around func_002A7750 19.
 * The C below needs a depth-4 and a depth-6 group. Keep the flat form if that
 * nesting is ruled padding.
 */
/* 6 November 2026, round 11: 412/412 bytes, 0/1 USA v1.01, TWO real differences
 * (was three), own unit -O2 -G0 -ffunction-sections -fno-schedule-insns.
 * Left: call 3 (0x14, 4) +0xa4/+0xa8, ours mult then mov.s f12,f20; retail
 * mov.s then mult. Allocation (obj s0, base s1, stride s2, p s3) and the first
 * block (lui, daddu a0, mult, addiu s1, mtc1) now match.
 * Mechanism: a group's loop notes make the next insn a sched2 barrier. Old
 * barriers at the li 0x150 and lui made the mult win the tie with daddu a0.
 * Now one depth-4 group runs from the block start through the second call, so
 * its BEG notes are harmless; a depth-6 group around func_002A7750 lifts obj.
 * The `zero` local set between n and tbl makes tbl and n tie (17 refs / 70),
 * and the tie goes to tbl (lower pseudo). Priorities: obj .979 > tbl .971 =
 * n .971 > p .957 (pri = floor_log2(refs) * refs / length, lreg dump).
 * The group's END barrier lands on call 3's lh (2-cycle load), so mov.s and
 * mult become ready together and mult has the higher priority. Ending after
 * the first call (needs zero set inside) breaks call 2 the same way; ending
 * after a later call does the same to that call; ending before func_002A7750
 * gives p (47 long) more weight than tbl/n at any depth. Any end at the li
 * 0x150, the lui or the mult moves the first block. Literal 0.0f in call 3 and
 * deeper func_002A7750 groups tie at two. 20 check.py runs. No linked build.
 */
/* 6 November 2026, Codex scheduling follow-up: no improvement after 200
 * check.py runs including baseline and final confirmation. Retain the valid
 * three-difference C below: 412/412 bytes, 0/1 USA v1.01 placements, own unit
 * -O2 -G0 -ffunction-sections -fno-schedule-insns. Relocation-only displayed
 * rows were excluded; the remaining offsets are +0x64, +0x6c and +0x70.
 * New trials: explicit zero/owner setup groups at four initialization points;
 * weighting the real table assignment in cases 1/2 while reducing case-0
 * setup groups; inlined initialization/append helpers; jointly varying stride
 * depth and table-plus-initializer groups; explicit FP zero inside those groups.
 * Owner groups and ungrouped initializer helpers tie at three; all other forms
 * worsen the schedule, allocation or size. The sched2 dump shows LOOP_END
 * notes on table setup prevent the argument move crossing its low-half addiu.
 * Extending the group through the initializer prevents zero hoisting before
 * that call; initializing zero inside it restores hoisting but still leaves
 * at least five rows, including the first append's argument order.
 * No candidate used uninitialized locals, invented accesses or dead operations.
 * No new source/flags retained; the INCLUDE_ASM marker stays. No linked build.
 */
/* 6 November 2026, Codex allocation follow-up: 412/412 bytes, 0/1 USA v1.01,
 * THREE real instruction differences, checked with tools/check.py --diff.
 * Required own-unit flags: -O2 -G0 -ffunction-sections -fno-schedule-insns.
 * Read the first state index before separate one-pass groups around the stride
 * setup (depth 3) and table-base setup (depth 4), in that order. This gives
 * retail's obj=s0, base=s1, stride=s2, p=s3. A separate case-1 stride local k
 * also gives retail's v0/v1 allocation. All reads, calls and stores are retained;
 * every local is initialized before use. No volatile, inline asm or aliases.
 * Remaining scheduling cycle:
 *   +0x64: ours addiu s1,v0,lo(table); retail daddu a0,s0,zero
 *   +0x6c: ours mtc1 zero,f20;         retail addiu s1,v0,lo(table)
 *   +0x70: ours daddu a0,s0,zero;      retail mtc1 zero,f20
 * Everything else agrees, including all relocation instruction/register fields.
 * 193 compiling check.py invocations including baseline and final confirmation.
 * New measurements: separate setup-group depths/order plus an early real index
 * read improve 14/15 rows to 7; an independent case-1 stride improves 7 to 3.
 * Extending setup groups over the first call gives 14 rows; grouping its actual
 * address work does not help. Owner-copy placement ties at 3; explicit FP-zero
 * lifetime gives 4-6; grouping the initial multiply gives 11 or 420 bytes.
 * On this new body, -fno-rerun-loop-opt, -fno-gcse, -fno-regmove,
 * -fno-sched-interblock and -fno-peephole tie at 3; disabling the second CSE
 * gives 4. Different group depths disturb allocation or produce 420 bytes.
 * Next useful experiment must preserve this allocation while resolving only
 * the three-instruction sched2 cycle. No linked build was run.
 */
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
    s32 index;
    s32 k;

    switch (obj[0x20]) {
    case 0:
        index = *(s16 *)(p + 0x36);
        n = 0x150;
        tbl = D_L03_00259A30;
        func_L00_00322A98(obj, &tbl[index * n]);
        func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0x28, 2, 0.0f);
        func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0x14, 4, 0.0f);
        func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0xA, 6, 0.0f);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        k = 0x150;
        tbl = &D_L03_00259A30[*(s16 *)(p + 0x36) * k];
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

/* Round-11 grouped form, case 0 only (2 differences; nested groups = padding, not kept):
 * void func_L03_00421930(u8 *obj)
 * {
 *     u8 *p = *(u8 **)(obj + 0x68);
 *     char *tbl;
 *     s32 n;
 *     s32 index;
 *     s32 k;
 *     float zero;
 *
 *     switch (obj[0x20]) {
 *     case 0:
 *         do {
 *             do {
 *                 do {
 *                     do {
 *                         index = *(s16 *)(p + 0x36);
 *                         n = 0x150;
 *                         zero = 0.0f;
 *                         tbl = D_L03_00259A30;
 *                         func_L00_00322A98(obj, &tbl[index * n]);
 *                         func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0x28, 2, zero);
 *                     } while (0);
 *                 } while (0);
 *             } while (0);
 *         } while (0);
 *         func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0x14, 4, zero);
 *         func_L00_00322AC0(&tbl[*(s16 *)(p + 0x36) * n], 0xA, 6, zero);
 *         do {
 *             do {
 *                 do {
 *                     do {
 *                         do {
 *                             do {
 *                                 func_002A7750(obj, 1, -1);
 *                             } while (0);
 *                         } while (0);
 *                     } while (0);
 *                 } while (0);
 *             } while (0);
 *         } while (0);
 *         break;
 */
