/* 9 November 2026 (o101): body below unchanged (3008/3008, 2 rows, masked 1 at +0x758). label_y3 and label_y4 (owner-allowed) on each of the 5 label_y calls and on all of them: count 1 unchanged (the deciding sched1 LUID tie is in the block after label_y's tests, which the helper form does not touch); label_y3 on the bar/hint calls 6-18. The sprintf format takes exactly the one %d argument it gets. */
/* 9 November 2026 (o72, sched1 -dS -fsched-verbose-6 read against haifa-sched.c rank_for_schedule): count 1 is decided by the final LUID tie-break in block 39. colour load (insn 1024) and a0 = text (1028) are both ready at clock 1: priority 19/19 (both through the strlen call 1030, prio 18; 1024 also through the sign extension 1026, 17+2), reg weight 1/1 (r84 stays live for a3 and count 2, so no REG_DEAD), last-insn class 3/3, dependents 3/3 (1024: 1026, 1030 by memory anti-dependence, 1084; 1028: 1030, 1034 output on a0, 1084), so LUID 1024 < 1028 wins. sched2 repeats the same tie (deps 3/3) and reorg puts the later a0 copy in the slot. expand_call emits a0 = text right before the call, so any honest order that loads colour before the call gives the lower LUID. A flip needs 1028 >= 4 dependents (a later write of text in the block; cse deletes `text = textBuffer`) or 1024 <= 2 (only a const call skips the anti-dependence: a false prototype). `long colour` folds the extension but keeps 3 (1038). No honest C change flips the criterion. check.py (3008 bytes, 0 of 2): colour read after the call, `len = strlen(text); colour = ...;` (5 rows, at +0x754), the same with `colour = ref_30` in the draw call's argument list (5 rows), `colour = ref_30` inside the argument list with strlen nested (same 2 rows as the base, at +0x758). Reorg fills the slot from the insns before the call first, and the a0 copy is the nearest eligible one, so the colour load after the call is never used. */
/* 9 November 2026 (Sonnet round s45): label_y2 (one handle test, owner-allowed) swept on each of the 5 calls, pairs and all (both one-test forms tie): base 2 rows, best 12 single, 22 pair. No gain. */
/* 9 November 2026 (Sonnet round s42, lesson 52): scripted `do { real_op; } while (0)` groups around 1-3 consecutive statements at every position (85 singles + pairs, best 4, pairs of the near-base ones) and every -frac2-* switch / -freduce-all-givs on the unit: nothing below the base 2 rows (best only ties, most groups far worse); no switch changes it. */
/* 8 November 2026, Sonnet round (o24, lesson 49): re-measured 2 rows (local cc1). Retail keeps text in s2, value in s1, one2 in s4, colour reloaded into s0 per count: matches the locals. Count 1 handle text/textBuffer/ctl/one2 (13-14), count 2 handle text/obj/ctl/textBuffer (11-14), text = textBuffer as sprintf arg or before it (20), char *text = textBuffer init (467), label_y inline in the call (757), colour assigned in the arg list, strlen(textBuffer): all 2 or worse. */
/* 8 November 2026 (Sonnet round s16, lesson 48, scripted scorer): one2=1, text=textBuffer, one=1, y/x/width/ref_43++ and gauge-2 assignments moved to every legal slot (~350 compiles): none below 2 rows; one2=1 after the count 2 block gives 4. */
/* 8 November 2026, Sonnet round (o9, ~6 check.py runs, one 1500 s permuter run: no gain over 130). Still 2 rows (count 1). Colour read before label_y's value, before text = textBuffer, or before the first sprintf: all 3028 bytes (frame 0x100). */
/* 8 November 2026, o7b follow-up (~22 check.py runs): count 1's 2 rows unchanged by every honest order of the colour
 * load and the strlen argument: colour inside the draw call's argument list (also with `len =`), strlen through a
 * pointer local (`char *t = text`), colour read again after the call (3012), `len = strlen(text); colour = ...` (5 rows:
 * colour lands after the jal), colour `& 0xFFFFFFFF`, `(u64)colour`, a u64 style copy (same; a u64 style declared first
 * 3032), textBuffer as either argument with `text` re-set before count 2 (same or 7). sched1 dump: colour 1024 and
 * a0 = r84 1028 at clock 1, no notes on either; the source pseudo r84 stays live, so the register-weight tie-break
 * cannot flip. */
/* 8 November 2026, Sonnet round (o7b, ~45 check.py runs, two capped permuter runs). Gauges fixed: gauge 2 reads its
 * height into a local before the second colour store (`height = ref_L22_003A5018_11; colours.d[1] = D_L22_001AF428;`
 * then `y + height` in the call): gauge 1's addiu/sd tie and gauge 2's D_001A7340 order both go (permuter find,
 * hand-cleaned). Body below: 3008/3008, 2 rows left, both count 1 (lw s0 colour vs daddu a0,text before strlen's jal).
 * Count 1 cause (dumps -dS/-dR): sched1 block 39 issues colour (insn 1024) and a0 = text (1028) at clock 1, tie on
 * priority, weight and dependents, LUID picks colour; sched2 keeps that order and reorg puts a0 in the slot. Retail
 * needs a0 first. The permuter matched it only with dummy `ref_L22_003A5018_32++; ref_L22_003A5018_32--;` before the
 * colour (a memory op that takes sched1's clock-1 memory slot; reload drops the no-op store): 0 rows, not landable.
 * Not it: two-step forms (`t = x; t -= k`) on right/x/y/ratio/colour words (identical code), ref_32 in a local (3028),
 * text assigned after value or after colour (7), separate len (4), colour u64/long (3016), unsigned (3028), short (3),
 * textBuffer for strlen (same). */
/* 8 November 2026 (m2z, caller-save angle): global.c:1516 tries caller-saves only when find_reg found no register (best_reg < 0), so CALLER_SAVE_PROFITABLE (4*calls < refs) never decides s-register versus call-clobbered while an s-register is free. cc1 -S on the retained C with and without -fno-caller-saves: identical body (0 lines differ). Uses s0-s7 and fp across 48 calls, but no pseudo takes a caller-save slot (no call-clobbered save/restore pairs); a source change that forced one would add save/restore code that retail lacks. Its 14 rows are scheduling (see round two). Angle closed; no check.py runs. */
/* 8 November 2026, round two (6 check.py runs plus free cc1 -S scoring). Body: the same 14 rows, now
 * with plain MACRO_ADDR declarations in place of the `_base[0]` #define aliases (no-alias rule).
 * L23 sibling (func_L23_0041DA48, matched, so its compiled code is retail) against L22 retail:
 * - Gauge 1: L23 issues addiu (counter+1) before sd d[1], as L22 retail does. The sched2 dumps
 *   (-fsched-verbose-5) show both insns at the same priority. In L23 the addiu has 5 dependents,
 *   because gauge 2's first fix uses t2 as its scratch register (clobber t2, then t3). Ours has
 *   4, because both gauge 2 fixes use a2 as scratch. Reload picks a2 because sched1 sets
 *   $6 = right after the fixes. 138 of 240 gauge 2 statement orders give the t2/t3 scratch
 *   and fix gauge 1 (pp/073: no 0x5570 rows), but every one of them moves the a2 copy early and
 *   breaks gauge 2 (251-256 vs 243 lines). No order gives both.
 *   Gauge 1 statement order (2520 orders) and the L23 function-scope locals: no effect.
 * - Gauge 2: L22 differs from L23 only in its denominator (int global D_L22_001B2AA8, lwc1 + cvt,
 *   against L23's short field). Its D_001A7340 load comes after sd d[0], where L23 has it early.
 *   No statement order or flag (-fno-sched-interblock, -fmove-all-movables, alias, cse and peephole
 *   flags) reproduces this.
 * - Count 1: colour and a0 = text tie at t=1 (priority 19, 3 dependents each). The smaller LUID
 *   wins, so colour goes first. Count 2's handle as count 1's value, strlen's result or a global
 *   gives worse code; as func_0027FB40's result it adds a `move s0,v0`.
 */
/* 8 November 2026 (~55 check.py runs, own -O2 -G8 -ffunction-sections -g unit). Body below: 3008/3008
 * bytes, 0/2 places, 14 differing rows (was 23 by the same count: check.py --diff rows minus
 * relocation-only ones), first difference +0x558.
 * - Fixed: func_L00_0030CF60() is called after the `if (ref_31)` panel, not inside it (retail's
 *   beqz skips to that jal; the L23 sibling has it outside too): -2 rows.
 * - Fixed: saved registers (base copy s6 > ctl s7 > obj fp). Count 2's label_y handle is count 1's
 *   colour (one shared `colour` local), so obj loses 2 refs: obj 5 refs now ranks below ctl
 *   (regalloc: obj was 14/518 > ctl 12/565). All prologue/obj/ctl rows exact. Count 2's own colour
 *   as handle also fixes the registers but lifts its colour load above the rounding (+4 rows);
 *   sprintf's return as handle: 3012 bytes; scaled_coord (L23 form) for the counts: frame -0xE0.
 * Left: (1) gauge 1: sd d[1] issues before addiu (ref_43 + 1): sched2 t=24 ready list ranks the
 *   store (718) above the addiu (709). Per-gauge union locals (no slot reuse, -0x100 frame), L23
 *   statement order, NOT_SDA on D_L22_001AF418/AF428/D_001A7340: no fix or worse.
 *   (2) gauge 2: D_001A7340 load before the width mtc1/cvt (retail: after sd d[0]).
 *   (3) count 1: colour load issued with a0 = text in the same cycle and picked first (LUID tie);
 *   u64 colour (shorter chain), colour before the label, assignment inside the call, a t copy of
 *   text, one/one2 as active: no change. The L23 sibling's compiled code has the same order as ours,
 *   so this is L22-specific. const on ref_30 lets cse keep it across calls (frame -0x100).
 */
/* 7 November 2026, round two (~30 check.py runs; body below unchanged, 36 rows):
 * (1) Allocation, measured with tools/regalloc.py: base copy = pseudo 579 (4 refs/272), obj = 85, ctl = 86.
 *   Count 1 = ctl, count 2 = obj, box = obj gives obj 7/569 > ctl 6/526. One more loop-weighted ctl ref fixes
 *   it: `case 2: func_00288FB8(0x1241); do { func_0029CC50(0x1241, *(short *)(ctl + 0x32C), -1); } while (0);`
 *   gives retail's s6/s7/fp, but the group adds a nop in the switch arm (3012 bytes). Same nop with the whole
 *   arm grouped or only the lh grouped. Groups on the ctl load at entry (57 rows) or on either gauge ratio
 *   (size change), or on the icon ifs (to add base refs), are worse. No handle gives a working count 1 barrier
 *   without touching obj/ctl: constants fold (text, &D_L22_001B1910, the format string, one2), and
 *   func_00115DA8's result keeps a dead `daddu v1,v0` (3012 bytes).
 * (2) Gauges: sched2 dump shows gauge 1 picks sd d[1] (insn 718) before `ref_43 + 1` (709) in the same cycle,
 *   while retail pairs the addiu with `or`. Statement order and line joins have no effect.
 * (3) Count 1: sched1 and sched2 ready lists pick the colour load (LUID 1056) before `a0 = text` (1058). Colour
 *   as a direct argument, a separate len statement, colour first, func_001157AC(textBuffer) or one shared colour
 *   variable all give the same output.
 */
/* 7 November 2026, rounding pass (unit -O2 -G8 -ffunction-sections -g, own -g8.c file): 78 -> 36 masked
 * rows, 3008/3008 bytes, 0/2 places, first difference +0xC. Every rounding is now label_y or screen_coord:
 * - Y1/Y3 -> screen_coord(D_L22_001B2980, value, 1.0f / 3.0f), the L15_0042E1B0 shape: 62 -> 42
 *   (icon 2/4 argument order and the sprite 9/10 joins now exact).
 * - Box width -> label_y(handle, 320.0f, ref_06, 0.5f, 1) (value/scale this way round puts 320 in f2):
 *   the barrier after the rounding and the box/label s0/s1 are exact (42 -> 38).
 * - Gauge sprites 7/8: label_y(sprite, ...) with the func_0028E588 result as handle (38 -> 36).
 * Left: (1) allocation. Retail wants base-hi copy of D_L22_001B1910 (pseudo 579, 4 refs/272) > ctl
 *   > obj; here obj 7/518 > ctl 6/565 (s7/fp swapped). Each label_y handle adds 2 refs; no obj/ctl
 *   handle mix gives base > ctl > obj. Count 1 handle `text` (or a neutral box handle) fixes every
 *   register (first difference +0x558, 37-38 rows) but folds that label_y's tests, losing its barrier
 *   (colour load rises above the rounding). (void *)ref_31 as box handle folds too (inside if (ref_31));
 *   global reloads / ctl+K / x-coordinate handles change the size.
 * (2) Gauge 1: addiu (ref_43 + 1) issues after the d[1]/w[1] stores; gauge 2: D_001A7340 loads before
 *   the width cvt. Statement order and line joins in both blocks give identical output.
 * (3) Count 1: colour (ref_30) load before the func_001157AC call instead of in its delay slot.
 * ~105 check.py runs. Body below is the 36-row form. */
/* 7 November 2026, label_y sweep: Y0 is label_y(ctl, ...) for the two gauge sprites and label_y(obj, ...) for the two count texts: 123 -> 78 differences, 3008/3008 bytes (text as handle: 3012 bytes; Y1/Y3 keep their real mode tests). The body below is the retained C with that change (label_y is
 * the accepted HUD label idiom, definition as in src/levels/15_gorn/L15_00431590-g8.c). Counts are
 * masked aligned instruction differences from a cc1 -S diff harness, not check.py rows. */
/* 2026-11-03 w02 faithful-contract review, US object checks only.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * Current check.py: 3008/3008 bytes,0/2 places,first+0x3E8.
 * Restored real32-bit address-word results for font/sprite lookups with explicit pointer conversions, plus actual int message helper interface. Serial-rounding/control boundary and later saved roles remain unchanged.
 * Reopen: Natural rounding boundary surviving sched2 without a wrapper or invented condition.
 * No linked or cross-release match is claimed; earlier records follow.
 */
/* Claude Opus 5.5 xhigh tier, task v1817, 31 October 2026.
 * Retained complete behavioural draft: USA v1.01, 3008/3008 bytes, 0/2 places
 * (levels 22 and 23); 129 of 752 rows still differ beyond relocated values, none
 * before 0x3A5400 (the prologue and sprites 1-5 are exact).
 * No linked build, no PAL/us2 check (no match).
 * Compile in an isolated -g8.c unit with -O2 -G8 -ffunction-sections -g. Without
 * -g the pre-div.s nop pairs go (2992 bytes); -fno-schedule-insns is far worse.
 *
 * What this draft recovered, each measured:
 * - Y1/Y3 return int from an if/else with (int) in both arms. Retail's sprite 9
 *   looks like a single `if (...) sy += 1.0f` but is the same Y1 as sprite 10:
 *   jump2 (after sched2) cross-jumps its identical cvt/mfc1 tails. Its real join
 *   is what stops cse, so sprite 10 reloads 0.5, 1.0 and 1 into locals. This
 *   took the size from 2968 to 3008. A plain `if` lets cse-skip-blocks carry them.
 * - (float)Y3(sy) must convert after the join. A (float) on a ternary is folded
 *   into its arms, which moved mtc1/cvt.s.w before the label and broke sched2's
 *   first clock of each block (lwc1 f12/lui a1/mtc1 f16/ori a1).
 * - The saved constants 1 (retail s3, s4) are two locals assigned 1 and passed as
 *   func_0028E588's variant: cse keeps a1=1 literal and canonicalises the later
 *   `D_L22_001B2980 == 1` register to the local, so it lives across the calls.
 * - Icon 2/4: compute x before sy. func_0027FB40 takes u64 and returns int.
 *
 * Remaining blocker: retail has a scheduling barrier directly after five roundings
 * (sprites 7, 8, both counter values, the box width), all (int)(... + 0.5f). No
 * later instruction goes above the mfc1, even in free slots (sprite 7: `lwc1 f1;
 * daddu a0,v0; mul; add; cvt; mfc1 a2; lw a1; addiu t1; lw a3; jal; lw t0`), and
 * s1/f20 stay below sprite 8's barrier while s3/f21 rise above sprite 6's call.
 * cse must cross it (f21, f22, s3 reach sprite 9). The (int)(ratio * x) gauge
 * conversions have no barrier. Most other differences follow from it: colour's
 * lifetime sets s0/s1/s4/s5/s6, so value/colour/format/high-copy get other saved
 * registers, and the box and label swap s0/s1.
 *
 * Tried without the barrier: plain and full-expression inlines, statement
 * expressions, nesting func_0028E588 in the call, reordering gauge statements,
 * alternate integer/FP argument interleavings (same bytes). Diagnostics only, not
 * retained or landable: `do { } while (0)` after or around the rounding gives a
 * barrier but ends cse1 at LOOP_END (losing the saved 1) and puts sprite in v0,
 * so daddu a0,v0 lands after add.s, 3012-3016 bytes: not an exact-bytes form.
 * `if (iy) y = iy;` with a dead arm left the differing rows unchanged, so it gave
 * no barrier (its RTL was not inspected).
 * Next: a construct leaving a block boundary or barrier in sched1 and sched2,
 * crossable by cse (perhaps a branch that survives until jump2), then recheck the
 * remaining gauge and sprite 10 argument order, which may follow from it.
 *
 * Bounded investigation: 23 check.py compiles plus RTL dumps (-ds -dt -dG -dS -dR).
 * Retail GP offsets of refs: 00=0324; 01=0414; 02=0418; 03=0420;
 * 04=0430; 05=3AE0; 06=3994; 07..30=0440..049C (four-byte steps);
 * 31=0314; 32..41=04A4..04C8 (four-byte steps); 42=04D0;
 * 43=04E0; 44=04CC. Required declarations follow.
 */
/* 9 November 2026 (o72, sched1 -dS -fsched-verbose-6 read against haifa-sched.c rank_for_schedule): count 1 is decided by the final LUID tie-break in block 39. colour load (insn 1024) and a0 = text (1028) are both ready at clock 1: priority 19/19 (both through the strlen call 1030, prio 18; 1024 also through the sign extension 1026, 17+2), reg weight 1/1 (r84 stays live for a3 and count 2, so no REG_DEAD), last-insn class 3/3, dependents 3/3 (1024: 1026, 1030 by memory anti-dependence, 1084; 1028: 1030, 1034 output on a0, 1084), so LUID 1024 < 1028 wins. sched2 repeats the same tie (deps 3/3) and reorg puts the later a0 copy in the slot. expand_call emits a0 = text right before the call, so any honest order that loads colour before the call gives the lower LUID. A flip needs 1028 >= 4 dependents (a later write of text in the block; cse deletes `text = textBuffer`) or 1024 <= 2 (only a const call skips the anti-dependence: a false prototype). `long colour` folds the extension but keeps 3 (1038). No honest C change flips the criterion; no check.py runs. */
#include "common.h"

extern u8 * D_L22_001A904C MACRO_ADDR;
extern int D_L22_001B2980 MACRO_ADDR;
extern float D_L22_001B2984 MACRO_ADDR;
extern int D_0018B694 NOT_SDA;
extern int D_L22_001B2AA8 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR;
typedef struct HudCounters {
    int unknown[2];
    int rightCount;
    int rightIcons;
    int unknown10[2];
    int leftCount;
    int leftIcons;
} HudCounters;
extern HudCounters D_L22_001B1910 NOT_SDA;
extern char D_L22_001AF4D8[] NOT_SDA;
extern int D_L22_001B2AC8 MACRO_ADDR;
extern int D_L22_001B2ACC MACRO_ADDR;
extern int D_L22_001B2AD0 MACRO_ADDR;
extern u64 D_L22_001AF418 MACRO_ADDR;
extern u64 D_L22_001AF428 MACRO_ADDR;
extern u8 *ref_L22_003A5018_00 __attribute__((sda));
extern float ref_L22_003A5018_01 __attribute__((sda)), ref_L22_003A5018_02 __attribute__((sda));
extern u64 ref_L22_003A5018_03 __attribute__((sda)), ref_L22_003A5018_04 __attribute__((sda));
extern int ref_L22_003A5018_05 __attribute__((sda));
extern float ref_L22_003A5018_06 __attribute__((sda));
extern int ref_L22_003A5018_07 __attribute__((sda));
extern int ref_L22_003A5018_08 __attribute__((sda));
extern int ref_L22_003A5018_09 __attribute__((sda));
extern int ref_L22_003A5018_10 __attribute__((sda));
extern int ref_L22_003A5018_11 __attribute__((sda));
extern int ref_L22_003A5018_12 __attribute__((sda));
extern int ref_L22_003A5018_13 __attribute__((sda));
extern int ref_L22_003A5018_14 __attribute__((sda));
extern int ref_L22_003A5018_15 __attribute__((sda));
extern int ref_L22_003A5018_16 __attribute__((sda));
extern int ref_L22_003A5018_17 __attribute__((sda));
extern int ref_L22_003A5018_18 __attribute__((sda));
extern int ref_L22_003A5018_19 __attribute__((sda));
extern int ref_L22_003A5018_20 __attribute__((sda));
extern int ref_L22_003A5018_21 __attribute__((sda));
extern int ref_L22_003A5018_22 __attribute__((sda));
extern int ref_L22_003A5018_23 __attribute__((sda));
extern int ref_L22_003A5018_24 __attribute__((sda));
extern int ref_L22_003A5018_25 __attribute__((sda));
extern int ref_L22_003A5018_26 __attribute__((sda));
extern int ref_L22_003A5018_27 __attribute__((sda));
extern int ref_L22_003A5018_28 __attribute__((sda));
extern int ref_L22_003A5018_29 __attribute__((sda));
extern int ref_L22_003A5018_30 __attribute__((sda));
extern int ref_L22_003A5018_31 __attribute__((sda));
extern int ref_L22_003A5018_32 __attribute__((sda));
extern int ref_L22_003A5018_33 __attribute__((sda));
extern int ref_L22_003A5018_34 __attribute__((sda));
extern int ref_L22_003A5018_35 __attribute__((sda));
extern int ref_L22_003A5018_36 __attribute__((sda));
extern int ref_L22_003A5018_37 __attribute__((sda));
extern int ref_L22_003A5018_38 __attribute__((sda));
extern int ref_L22_003A5018_39 __attribute__((sda));
extern int ref_L22_003A5018_40 __attribute__((sda));
extern int ref_L22_003A5018_41 __attribute__((sda));
extern u8 ref_L22_003A5018_42[] SDATA(ref_L22_003A5018_42);
extern int ref_L22_003A5018_43 __attribute__((sda));
extern int ref_L22_003A5018_44 __attribute__((sda));

extern int func_00336D50(void *, int);
extern void func_00300A00(void *, unsigned int, float, float, float, float, float);
extern int func_0028E588(int, int);
extern void func_0028EA58(void *, int, int, int, int, void *);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_0027FB40(int, int, u64, char *, int);
extern char *func_00288FB8(int);
extern int func_L00_0030DD70(int, int);
extern void func_0029CC50(int, int, int);
extern int func_00282948(void *);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern void func_0029B888(void *, unsigned int, char *, int, int, int, int, char *, int, int);
extern void func_L00_0030CF60(void);

extern int D_L22_001B2980;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L22_001B2980;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int screen_coord(int mode, float value, float offset)
{
    float scaled = value * D_L22_001B2984 + 0.5f;

    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_L22_003A5018(void) {
    char textBuffer[64];
    char *text;
    union { u64 d[2]; u32 w[4]; } colours;
    u8 box[32];
    u8 *obj = ref_L22_003A5018_00;
    u8 *ctl = *(u8 **)(obj + 0x68);
    int y;
    int one, one2;
    int colour;
    char *label, *hint;

    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC3);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60442D00, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC4);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60241700, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC5);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x55F0C070, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC3);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60442D00, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC4);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x60241700, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)func_00336D50(D_L22_001A904C + 0x8710, 0xC5);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        func_00300A00(sprite, 0x55F0C070, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    one = 1;
    { void *sprite = (void *)(u32)func_0028E588(0xEAA4, one);
    func_0028EA58(sprite, ref_L22_003A5018_14, label_y(sprite, (float)ref_L22_003A5018_15, D_L22_001B2984, 0.5f, 1), ref_L22_003A5018_16, ref_L22_003A5018_17, ref_L22_003A5018_42); }
    { void *sprite = (void *)(u32)func_0028E588(0xEAA4, 0);
    func_0028EA58(sprite, ref_L22_003A5018_18, label_y(sprite, (float)ref_L22_003A5018_19, D_L22_001B2984, 0.5f, 1), ref_L22_003A5018_20, ref_L22_003A5018_21, ref_L22_003A5018_42); }

    {
        float ratio = (float)D_0018B694 / (float)*(short *)(ctl + 0x324);
        int x, width;
        colours.d[0] = ref_L22_003A5018_03;
        width = ref_L22_003A5018_12;
        x = ref_L22_003A5018_09 + ref_L22_003A5018_07 + ref_L22_003A5018_13;
        y = ref_L22_003A5018_10 + ref_L22_003A5018_08 / 2 - ref_L22_003A5018_11 / 2;
        ref_L22_003A5018_43++;
        colours.d[1] = D_L22_001AF418;
        colours.w[1] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        func_0027EAE8(x, y, x + (int)(ratio * (float)width), y + ref_L22_003A5018_11, 0xFFFFF1, &colours);
    }
    {
        float ratio = *(float *)(ctl + 0x20) / (float)D_L22_001B2AA8;
        int right, width, height;
        colours.d[0] = ref_L22_003A5018_04;
        width = ref_L22_003A5018_12;
        right = D_001A7340 - ref_L22_003A5018_09 - ref_L22_003A5018_07 - 4;
        colours.w[0] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        height = ref_L22_003A5018_11;
        colours.d[1] = D_L22_001AF428;
        func_0027EAE8(right - (int)(ratio * (float)width), y, right, y + height, 0xFFFFF1, &colours);
    }

    {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 0);
        func_0028EA58(sprite, ref_L22_003A5018_22, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_23, 1.0f), ref_L22_003A5018_24, ref_L22_003A5018_25, ref_L22_003A5018_42);
    }
    {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 0);
        func_0028EA58(sprite, ref_L22_003A5018_26, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_27, 1.0f), ref_L22_003A5018_28, ref_L22_003A5018_29, ref_L22_003A5018_42);
    }
    one2 = 1;
    func_00115DA8(textBuffer, D_L22_001AF4D8, D_L22_001B1910.leftCount);
    text = textBuffer;
    {
    int value = label_y(obj, (float)ref_L22_003A5018_33, D_L22_001B2984, 0.5f, 1);
    colour = ref_L22_003A5018_30;
    func_0027FB40(ref_L22_003A5018_32, value, colour, text, func_001157AC(text));
    }
    func_00115DA8(text, D_L22_001AF4D8, D_L22_001B1910.rightCount);
    {
    int value = label_y((void *)colour, (float)ref_L22_003A5018_35, D_L22_001B2984, 0.5f, 1);
    colour = ref_L22_003A5018_30;
    func_0027FB40(ref_L22_003A5018_34, value, colour, text, func_001157AC(text));
    }
    if (D_L22_001B1910.leftIcons) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, one2);
        func_0028EA58(sprite, ref_L22_003A5018_36, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_37, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.leftIcons >= 2) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 1);
        int x = ref_L22_003A5018_36 + ref_L22_003A5018_44;
        func_0028EA58(sprite, x, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_37, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.rightIcons) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 1);
        func_0028EA58(sprite, ref_L22_003A5018_38, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_39, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.rightIcons >= 2) {
        void *sprite = (void *)(u32)func_0028E588(0xEAA5, 1);
        int x = ref_L22_003A5018_38 - ref_L22_003A5018_44;
        func_0028EA58(sprite, x, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_39, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B2AC8 != -1 && obj[0x95] != 10) {
        switch (D_L22_001B2AC8) {
        case 0: func_L00_0030DD70((int)func_00288FB8(0x2FA3), -1); break;
        case 2: func_00288FB8(0x1241); func_0029CC50(0x1241, *(short *)(ctl + 0x32C), -1); break;
        case 1: func_00288FB8(0x1240); func_0029CC50(0x1240, D_L22_001B2ACC, -1); break;
        }
        ref_L22_003A5018_05 = 0;
        func_00282948(&D_L22_001B2AD0);
        if (D_L22_001B2AD0 <= 0) D_L22_001B2AC8 = -1;
    }
    if (ref_L22_003A5018_31) {
        func_002802E0(box, 240, 480, 44, 468, 256, label_y(ctl, 320.0f, ref_L22_003A5018_06, 0.5f, 1), 16, 3);
        label = func_00288FB8(0x9FC);
        hint = func_00288FB8(0x2F2C);
        func_0029B888(box, 0x80F0F0F0, label, 0, 0, -1, 0, hint, 0, 0);
    }
    func_L00_0030CF60();
    return 1;
}
