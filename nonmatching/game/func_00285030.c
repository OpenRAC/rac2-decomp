/* 8 November 2026 (round 9, rank_for_schedule): base 680/680, 6 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 680/680, 6 rows (0x8000 issued early takes a2 from 0xE). */
/* 7 November 2026, FINAL: 680/680 bytes, 0/28 USA places, six real rows (game -O2 -G8 -ffunction-sections); not linked. A fresh C written from the assembly alone (RAC1-style += cursor, RenderTarget struct) reproduces everything to +0x1C8 and, with 0x4410/0x106 in early single-use locals, ties the retained six rows; with literals it gives 16 (the D_001A6480 la then issues after 0x4410/0x106). New controls this round, all tie or worsen: early locals for 0x30003/0x47/0x4400..8001/header/0xE/0x8000 (11-107 rows), reusing bw or tex for 0x106/0x4410 (16-30), and -frac2-gcse-unsplit-edges, -frac2-keep-block-zero-copy, -frac2-sticky-volatile-refs, -fno-regmove, -fno-cse-follow-jumps, -fno-peephole, -fno-caller-saves (6 each; -fno-rerun-cse-after-loop 72). Exact remaining blocker: in the final packet block sched1 issues the 0x8000 coordinate constant in the free ALU slot beside t[1]'s store, so in local-alloc it overlaps 0xE and takes a2 (0xE -> t0, 0x30003 -> t2); the only source change that fills that slot (0x106 written in the block) makes 0x106 outrank the D_001A6480 la and take t2. No rule-compliant source orders la before an in-block 0x106 while keeping 0x8000 late. */
/* 6 November 2026 near-miss follow-up (checked 7 November 2026): retained
 * 680/680, 0/28 USA places, six real differing instruction rows, game -O2 -G8
 * -ffunction-sections. New controls: reusing an actual earlier header/selector
 * value for w or w2 ties at six or grows to 688 bytes; assigning w/w2 in both
 * mode arms grows to 684-688 bytes. A shared selector local across both packets
 * gives 7-14 rows at 680 bytes, or shrinks incorrectly to 676 bytes. Grouping a
 * real coordinate-bias initialization before t[0..8], with early or in-block
 * 0x106, gives 21-55 rows at 680 bytes. Twelve full-packet inline emitter
 * parameter orders tie at six; signed coordinate-packing helpers give 6-9 rows.
 * These helpers preserve the real stores and arithmetic, with no added accesses.
 * Discarded two bias-after-first-use trials and three C89 declaration-order
 * compile failures; neither is evidence of an improvement. No valid new form
 * improves the retained source. Remaining: early 0x8000 issue, 0xE/0x30003
 * allocation, and the alternative in-block 0x106/state-address priority tie.
 * Marker restored; no linked build or secondary-release check was run.
 */
/* 7 November 2026, decomp-permuter: best score 135 (base 225) only by giving 0x106 and 0 one variable (changes meaning); no rule-compliant gain. Setup: /tmp/claude-1000/-home-lynder063-rac2-decomp/lead/work/perm. */
/* 6 November 2026 (round 11c, prototype audit): func_00282A88() given its established (void *, int) prototype: same 6 rows. func_00125F20 really returns int (src/core/00125E58.c:63), so its unused result stays int. Other callees agree. */
/* 6 November 2026, round 11b: unchanged best, 680/680, 0/28, 6 rows. No matched sibling uses
 * func_00125F20 or 0x4410/0x30003; func_00285548 (00284FC0-g8.c, 0x106 packet) style with an
 * int * cursor gives 43. sched1 -dS: in block 3 0x8000 issues at cycle 6 with t[1]'s store
 * (one free slot); 0x106 in block fills it but ranks above the la (all packet constants share
 * one priority, store weight/luid break ties), so it is born before t[0]'s store (t2). Tied:
 * three separate 0x8000 locals (cse merges), x *= 8 coordinates, t[1]/t[2] swap. Worse:
 * t[1] before t[0] (14), one store after the if/else (49), 0x4410+0x106 literal (19), 0x106
 * literal (9), rotated/reversed store runs (11-26), x = 0x8000; x -= ... (688 bytes, 51).
 */
/* 6 November 2026, Codex packet-layout pass: unchanged retained C, game -O2 -G8
 * -ffunction-sections, 680/680 bytes, 0/28 USA places, six real instruction rows.
 * New controls: a ten-field packet and a tag plus three value/selector pairs both
 * tie at six (seven with 0x106 in the final block); scalar versus array DrawState
 * declarations and a two-element dimensions array also tie. Short/unsigned selector
 * locals tie; signed 32-bit selectors give 7-17 rows. A shared inline emitter for
 * real value/selector pairs gives 6-33 rows. The 42 adjacent middle-store groups
 * t[first..last], 1 <= first < last <= 7, with early or in-block 0x106, give
 * 24-138 rows and sometimes 688 bytes: loop-note barriers disturb the header/base
 * schedule instead of fixing 0x8000's allocation. No new form improves the retained
 * six-row source. Remaining: 0xE/0x30003 allocation and 0x8000's early issue.
 * No linked build or secondary-release check was run; source marker restored.
 */
/* 6 November 2026, round 10c: unchanged best, 680/680, 0/28, 6 rows. Unit flags change nothing
 * on the retained or the t[2]-before-t[1] form: -fno-sched-interblock, -fno-sched-spec,
 * -fno-expensive-optimizations, -frac2-keep-block-order, -frac2-qcopy (6 each); -fno-schedule-insns
 * gives 688 bytes; -fstrict-aliasing 125 rows, -fno-gcse 127. Call-as-argument forms of the
 * func_00125F20 cursor, three cursor spellings of the final packet and s2 set early (merges with s,
 * 668 bytes) tie or worsen. 0x8000 in an early s32 local stays a global register (51-138 rows).
 * q[2] stored once after the if/else: 48. With 0x106 in block (7 rows) the sched1 trace shows 0x106
 * outranks the la by its store-to-load edge, so it issues at cycle 5 beside the header store and
 * cannot take v1; a 60-step hill-climb of that block stays at 7.
 */
/* 6 November 2026, round 10: unchanged best, 680/680, 0/28, 6 rows. Exhaustive GCC 2.95.2 RTL
 * and scheduler trace analysis identifies the precise compiler conflict:
 * 1. Setting both 0x4410 and 0x106 in early locals (w and w2) allows reload rematerialization to
 *    give retail's exact la/0x4410/0x106 schedule (00285224, 00285228, 0028522C) and registers ($v0, $v1).
 * 2. However, because w and w2 are absent from block 3 during sched1, the ALU unit at cycle 6 is idle
 *    and eagerly schedules 0x8000 alongside t[1]'s store (insn 309).
 * 3. This causes 0x8000's extended fake_birth in local-alloc to conflict with 0xE and 0x30003; having
 *    3 references, 0x8000 takes $a2 first, forcing 0xE to $t0 and 0x30003 to $t2 (6 differing rows).
 * 4. Emitting 0x106 inside block 3 fills cycle 6 ALU and delays 0x8000 to cycle 8, yielding retail's exact
 *    $a2, $t0, $a2 allocation, but 0x106 is then scheduled before the la of &D_001A6480 and takes $t2 (7 rows).
 * 5. Swapping packet stores t[1] and t[2] yielded a 5-diff variant with 0x30003 in $t0, but the
 *    underlying priority tie between &D_001A6480 and 0x106 remains. Retaining best 680-byte 6-row source.
 */
/* 6 November 2026, round 9: unchanged best, 680/680, 0/28, 6 rows. With 0x4410 and 0x106 both in
 * early locals (retail la/0x4410/0x106 order), a 150-step hill-climb over the final packet order
 * stayed at 6. Also tied or worse: no s2 (6), s2 declared before t (6), 0xE as an early local (73,
 * 684 bytes), 0x8000L (39), one shared t for both packets (27-28), w/w2 set after the if (20).
 */
/* 6 November 2026, round 7: unchanged best, 680/680, 0/28, 6 rows. Setting 0x106 in a local
 * next to w (both moved by update_equiv_regs after sched1) gives retail's la/0x4410/0x106 order
 * and v1, but 0x8000 is then issued in the same sched1 cycle as t[1]'s store, so 0xE loses a2
 * (0xE t0, 0x30003 t2; 6 rows). Tied or worse: s2 as a top-level local (6), p or q reused for
 * the final packet (25-30), w reused for 0x106 (107), 0xE as an early local (72), t[1] moved
 * before t[0] or the cursor store (12-17), 0x4410 literal with 0x106 local (15; hill-climb 13).
 */
/* 6 November 2026, round 3: unchanged, 680/680, 0/28, 6 rows (0x106 before the
 * D_001A6480 la). Automatic hill-climb over the order of the final packet block
 * (s2 assignment, cursor store, t[0..9]; ~550 compiles, two seeds, also with t[8]
 * through a local) never went below 6 rows. Moving w = 0x4410 to four earlier
 * places ties; reusing s for s2 gives 132 rows. Original best C retained.
 */
/* 6 November 2026: USA v1.01 recheck, game -O2 -G8 -ffunction-sections:
 * 680/680 bytes, 0/28 placements, first +0x1F4; seven instruction rows differ
 * after ignoring relocation immediates. The older five-row measurement is historical.
 * New: grouping the final packet or its 0x4410 store grows to 688 bytes; grouping
 * its first store, 0x106 store, coordinates or state-base assignment worsens allocation.
 * Moving the actual 0x106 store before 0x4410, before the header or after coordinates
 * gives 15, 22 or 44 differing rows. RAC1's active setup_render_target donor in
 * src/game/render/framebuf.c confirms the packet structure; its literal 0x4410 and
 * unsigned draw-environment view give 17 rows here. Original best C retained.
 * Reopen with a source-supported reason for the state address to precede 0x106
 * while preserving the packet constants' allocation; no linked build was run.
 */
/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain the actual int return and pointer/signed-short inputs of func_00125F20.
 * The measured 680-byte USA near miss still differs in packet constant/address scheduling; no false call contract is used to close it.
 * Earlier measurements below describe earlier sources or toolchains.
 */
#include "common.h"
/* Closer C3, 1 November 2026: 680/680, 5 rows, plain -O2 -G8. 0xE and 0x8000 share a2 only when 0x8000 is born at least one
 * insn after t[1]'s store dies (a gap of none conflicts in local-alloc), and sched1 issues 0x8000 in the first free ALU slot,
 * so retail has one more ALU insn in the block's first six cycles than we do. t[6] = 0x106 written in the block gives that
 * and a2 comes right, but 0x106 then ranks p24 over the la of D_001A6480 (p22): it lands before the la and takes t2, not v1.
 * Set in the earlier block it moves by update_equiv_regs after sched1, so it counts for nothing. A reused constant
 * local is cse'd away; cursor alias forms and split addresses tie or are worse.
 * Earlier: no asm fence: the tex or-chain over separate statements, D_001B22A8 as an incomplete MACRO_ADDR array read [0].
 */
#include "common.h"

typedef struct { unsigned long lo : 9; unsigned long hi : 55; } TexBits;
typedef struct { u8 p0[0x160]; s16 h160; s16 h162; s16 h164; s16 h166; u8 p168[4]; u16 h16C; s16 h16E; } DrawState;
extern DrawState D_001A6480[];
extern s32 D_001B22A8[] MACRO_ADDR;
extern long D_001A7470;
extern void func_00282A88();
extern int func_00125F20(void *, short, short, short, short, short);

void func_00285030(s32 tw, s32 th, s32 tbp, s32 mode) {
    DrawState *s = D_001A6480;
    s32 tbw;
    long tex;
    u8 *p;
    long *q;
    long w;
    long w2;

    tbw = tw - 6;
    if (tbw <= 0) tbw = 1;
    s->h166 = tbp >> 13;
    s->h160 = 1 << tw;
    s->h162 = 1 << th;
    tex = (tbp >> 8) | ((long)(1 << tbw) << 14);
    tex |= (long)tw << 26;
    tex |= (long)th << 30;
    tex |= 0x8000UL << 19;
    D_001A7470 = tex;
    func_00282A88(D_001B22A8[0], 0xF0);
    *(u32 *)(D_001B22A8[0] + 0) = 0x1000000E;
    *(u32 *)(D_001B22A8[0] + 4) = 0;
    *(u32 *)(D_001B22A8[0] + 8) = 0;
    *(u32 *)(D_001B22A8[0] + 0xC) = 0x5000000E;
    w = 0x4410;
    w2 = 0x106;
    {
        long *t = (long *)(D_001B22A8[0] + 0x10);
        D_001B22A8[0] = (s32)t;
        t[0] = 0x1000000000000008UL;
        t[1] = 0xE;
    }
    p = (u8 *)D_001B22A8[0];
    q = (long *)(p + 0x10);
    D_001B22A8[0] = (s32)q;
    func_00125F20(q, s->h164, s->h160, s->h162, 3, 0);
    ((TexBits *)(p + 0x10))->lo = s->h166;
    if (mode == 0) {
        q[2] = s->h16E | ((long)(s->h16C & 0xF) << 24);
    } else {
        s32 n = tw + th;
        if (n > 16) n = 16;
        q[2] = ((tbp - (4 << n)) >> 13) | ((long)(s->h16C & 0xF) << 24);
    }
    {
        long *t = (long *)(D_001B22A8[0] + 0x80);
        DrawState *s2 = D_001A6480;
        D_001B22A8[0] = (s32)t;
        t[0] = 0x1000000000000001UL;
        t[1] = 0xE;
        t[2] = 0x30003;
        t[3] = 0x47;
        t[4] = 0x4400000000008001UL;
        t[5] = w;
        t[6] = w2;
        t[7] = 0;
        t[8] = (0x8000 - s2->h160 * 8) | ((long)(0x8000 - s2->h162 * 8) << 16);
        t[9] = (s2->h160 * 8 + 0x8000) | ((long)(s2->h162 * 8 + 0x7FF0) << 16);
    }
    D_001B22A8[0] += 0x50;
}
