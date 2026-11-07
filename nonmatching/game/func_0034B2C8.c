/* 7 November 2026: compile as its own unit (src/game/0034B2C8.c) with -O2 -G0 -ffunction-sections
 * -frac2-keep-float-pun-source. 6048 of 6048 bytes, 1508 of 1512 instructions aligned, 12 words differ
 * in place, 0 of 28 places. All 16 colours are right with the one helper hud_bits_34B2C8, the double-use
 * colours and 0x1EFF included (docs/COMPILER-NOTES.md), and the spill slots and FPR numbers follow. The two
 * items left are not colours. In both, sched2 puts a set of a saved register into a jal slot where retail
 * has the store that reads the old value there, and the set after the jal:
 *   1. before func_00335F20: ours `sw $s5,0x48($sp); sw $v1,0x30($sp); jal; move $s5,$0`,
 *      retail `sw $v1,0x30($sp); jal; sw $s5,0x48($sp)`, then `move $s5,$0`.
 *   2. loop 1, before the second sprintf: ours `sw $s3,0($v0)` right after the hi of a1 and
 *      `lui $s3,0xF0` in the jal slot; retail has that sw in the slot and the lui after the jal.
 * After sched1 ours has the set after the jal, as retail; sched2's anti-dependence from the store raises
 * the store's priority, so it goes first and the set moves up. Moving `color = 0xF0F0B0` makes no
 * difference. A separate local, or a literal, costs another saved register or the spill slots. None of
 * -fno-sched-interblock, -fno-sched-spec, -fno-sched-spec-load, -fno-force-mem or the -frac2- switches
 * changes either item. Older notes below describe the colour blocker this option resolved.
 */
/* Measured in v3770 (Opus 5.5, opus-2, 2026-11-07). C below unchanged: 6028 of 6048 bytes, 0 of 28 places,
 * 1476/1512 aligned with relocations ignored. Build it as its own unit (src/game/0034B2C8.c, default flags)
 * with the func_0034B2C8 marker in src/game/00345358.c commented out.
 * Why no allowed C gives the three normal double-use colours (0x60442D00, 0xF0F0B0, 0x55F0C070):
 *   - Pin: retail's lui/ori v0 comes right after the previous call, while sched1 hoists 0.3f/1.0f/2.0f above
 *     several calls in the same block. So the GPR set is a pseudo with REG_N_CALLS_CROSSED == 0
 *     (sched_analyze_1), and the copy into the call-crossing $f20 is a separate insn. That copy is real movsf
 *     RTL: retail's mov.s $f13,$f20 waits out the mtc1 transfer latency, which an asm mtc1 does not.
 *   - This cc1 folds K into the float on every path. cse2 folds it (fold_rtx SUBREG, cost tie 16 = 16, the
 *     folded form wins). combine folds it whenever G dies in the copy (gen_lowpart_for_combine, or
 *     expand_field_assignment for the write-side pun). update_equiv_regs substitutes a once-set, once-used
 *     global init whenever the result is valid; only denormals such as 0x1EFF get moved instead. G cannot
 *     keep a second use through cse2: make_regs_eqv canonicalises same-mode copies, and a second
 *     (subreg:SF G) becomes the first copy. Checked and not applicable without an always-true test or extra
 *     code: cse's 1000-insn table flush, cygnus_merge_blocks after cse2 (cse2-only boundaries), and flow's
 *     LOG_LINK, which is made only to the first use.
 *   - Tested in small units and here: union, pointer and u64 reads fold or become per-use li.s; a TImode union
 *     stays on the stack; s64 or s128 low-word writes add and/or plus dsll32/dsra32; an SF read of an s64 or
 *     s128 ICEs (expr.c:566); an assignment inside an argument (`k(.., c = x, ..)`) is canonicalised by cse2.
 *   - Forbidden forms that hide the value (diagnostics only, never land), each used as
 *     `{ f32 c = pin(K); key1(.., c, ..); key2(.., c, ..); }` for the three colours, make the function 1512
 *     instructions (T moves off 711, so the spill slots rotate and need retuning):
 *       static inline f32 pin(s32 i) { __asm__("" : "+r"(i)); return *(f32 *)&i; }
 *         1494/1512 with slots ignored; each colour block is off by one row (mtc1 after mov.s $f12).
 *       static inline f32 pin(s32 i) { f32 f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(i)); return f; }
 *         1500/1512 with slots ignored; only mov.s $f13,$f20 sits two rows early in each block.
 *     The other rows left in both are the three items listed below (loop-1 sw $s3, the sw $s5 swap, 0x1EFF in v1).
 */
/* Near miss (Opus 5.5, opus-1, task v3567, 2026-11-07): func_0034B2C8, 6,048 bytes, boot + 27 levels.
 * Best check.py: 6028 bytes, expected 6048, 0 of 28 places. Frame 0x160 (= retail).
 * Sequence-aligned with relocations ignored and spill slots NOT ignored: 1480 of 1512 identical
 * (best before: 1449 with slots treated as equal, about 1230 without). Own unit, as below.
 *
 * Solved here:
 *   Spill slots: all 35 now equal retail. `self` is a copy of the parameter (`char *self = o`), and
 *     `o` has its address taken in the 0x131C block, so put_var_into_stack gives it pseudo 779
 *     (window 757..783). cprop rewrites self to it. T must stay 711 (max_cuid 1420..1423).
 *     This file: `(void)&o;` plus `s32 color = 0;` (one declaration init; needed for T = 711).
 *     Alternative with no no-code statement: `func_00349970(*&o + 0x131C, arg);` and no init: same
 *     slots and T, but that call keeps `addiu a0,s4,0x131C` for `lw a0,0x80(sp)` (1478 of 1512).
 *     A bare `*&o` at 0x144C (first bare use after the window) gives 799, 16 too late; a late copy
 *     local `p = *&o` keeps p + K out of PRE; `self = *&o` makes self two-set (T 713, cprop lost).
 *   Tail: `extern s32 D_001A79F8[] __attribute__((sda))` = unsplit la, retail's lui/addiu pair and
 *     store order. Also removes the insn that kept T at 713 for `*&o + K`.
 *   Fade-store v0/v1 parity: follows from reading 0x1EFF through hud_rbits_34B2C8 (read-side pun).
 *   That form is pinned after the previous call, as retail, except it takes v1 for v0.
 *
 * Left (32 rows, three items):
 *   1. Normal double-use colours 0x60442D00, 0xF0F0B0, 0x55F0C070. This accounts for the 20 bytes,
 *      the nop in two beqz slots, and $f20/$f21 numbering. A whole-game scan (boot and all 27
 *      levels) for lui/ori/mtc1 GPR to $f20+ with a normal float finds only this function and
 *      func_00349D58, so no matched C shows the form.
 *      Retail's set stays after the previous call, which in sched_analyze_1 needs
 *      REG_N_CALLS_CROSSED == 0 on the lui/ori destination (FP constants, unpinned, hoist to block
 *      start in retail). So it is a GPR pseudo G apart from the crossing float c, and G must survive
 *      cse2 and combine. Combine folds whenever G dies in the mtc1 (it does at K with non-zero low
 *      mantissa bits too, where cse2 keeps the subreg, so the cost tie alone is not the blocker).
 *      No block boundary can sit between: a0/a1 setup interleaves with lui/ori/mtc1, and 0.3f in
 *      $f21 hoists across the place.
 *      Nearest form: share the loop's float, `f32 x` at function scope, `*(s32 *)&x = K;`, read x
 *      twice. Loop-weighted refs make regclass choose FP, and reload's inherited output reload gives
 *      `lui v0; ori v0; mtc1 v0,$f25` plus `mov.s $f13,$f25`, 6044 bytes, exactly retail's words,
 *      but the set is hoisted to the block start (x crosses calls, so no pin), and v0/v1 rotate.
 *      Untested: regmove's optimize_reg_copy_1 would give c + uncrossed G if (set c G) survived with
 *      G read after it, but cse2 unifies the two in the same extended block in every form tried.
 *   2. Loop 1: `sw $s3,0($v0)` must be last before the sprintf jal (slot), then lui s3 ... ori s3
 *      later. A separate local for 0xF0F0B0 does not do it (6044 bytes, worse).
 *   3. `sw $s5,0x48($sp)` must follow `sw $v1,0x30($sp)` (one swap, jal slot).
 *
 * Text below: older notes. "Still different" item 1 is solved as above; items 2 and 3 are 1 and 2 here;
 * item 4 is solved.
 */
/* Measured in v3574 (Opus 5.5, opus-2, 2026-11-07; C below unchanged, still 6028 bytes, 0 of 28):
 *   Colours (item 1), placement: diagnostics only, none landable.
 *   - A basic-block boundary right after key 0 (identical-arm if/else around the 0xBEC key-0 call)
 *     puts the 0x60442D00 set right after key 0's jal, as in retail. But it also moves 0.3f, 1.0f
 *     and 2.0f out of the post-loop block start, which retail does not, and the pseudo stays in s0.
 *   - One-pass groups `do { key 0 } while (0);` then `do { keys 1, 2 } while (0);`. The loop notes
 *     are sched1 barriers, and the loop depth weights the two uses, so regclass picks FP ($f20).
 *     With the write-side pun this MISCOMPILES: sched1 splits the subreg set into hi/ior, and
 *     reload drops the ior's output reload (`lui v1,0x6044; mtc1 v1,$f20`, no ori). With the
 *     read-side pun it folds to li.s $at into $f20. Either way the barrier stops 0.3f/1.0f/2.0f from
 *     hoisting above key 0 (retail hoists them to rows 540..550). So retail has no barrier or block
 *     boundary before key 1.
 *   - Retail loop 1 places its crossing s3 constants right after a call by priority alone, with no
 *     free issue slot earlier. At 0xBEC, though, the same-priority float constants are hoisted and the
 *     colour is not, so its set really depends on key 0's call. That means a GPR temp with
 *     REG_N_CALLS_CROSSED == 0, copied into a crossing FP pseudo. This confirms item 1's model.
 *   0x1EFF v1/v0 (item 3 of the older list): pseudo 660 (SI, REG_EQUIV 0x1EFF, "pref FP_REGS, else
 *     GR_REGS", 6 insns) gets v1 in local-alloc although no insn in its range names v0. Pseudo 680 (the
 *     0x80001EFF write-side pun, user var, 4 refs) gets v0. Cause not found.
 */
/* Measured in v3608 (Opus 5.5, opus-2, 2026-11-07; C below unchanged, still 6028 bytes, 0 of 28):
 *   Colours (item 1), compiler paths, measured on small test units with the game cc1 (-O2 -G0):
 *   - Read-side pun: purge_addressof (after cse1) gives (set c (subreg:SF G)), and cse2 folds it
 *     (fold_rtx SUBREG, cost tie 16 = 16). With nonzero low 3 mantissa bits (0x60442D01), cse2 keeps the
 *     subreg and a REG_EQUAL note, and combine folds 20 -> 26 instead. Both fold through
 *     gen_lowpart_common's REAL_ARITHMETIC `mode == SFmode && CONST_INT` case (emit-rtl.c ~846). That
 *     case depends on the target config, not the host, so the original compiler folds too.
 *   - Combine and sched1 share flow1's blocks (no CFG rebuild until flow2), and flow1 merges blocks at
 *     unreferenced labels. So a cse2-only boundary is gone by combine, and a boundary that survives
 *     combine also splits sched1 and sched2 (jump2 runs after sched2). That boundary is v3574's result:
 *     0.3f/1.0f/2.0f leave the post-loop block. Only a jump that combine itself deletes would fit
 *     (boundary in combine and sched1, merged at flow2 so sched2 can hoist), which needs an impossible
 *     test. Not allowed.
 *   - update_equiv_regs moves a once-set, once-used REG_EQUIV init next to its use and zeroes
 *     REG_N_CALLS_CROSSED. That needs REG_BASIC_BLOCK < 0 (set and use in different blocks), and
 *     sched1 splits every large SI constant first (haifa-sched.c:8433, split_block_insns). So it can
 *     only apply to 16-bit or lui-only values (0x1EFF), never to the three normal colours.
 *   - flow makes a LOG_LINK only from the first use after a set (flow.c:3386). A G whose first use is
 *     not the copy would therefore never combine into it, but cse2 folds before combine runs.
 *   - These fold or regress (whole-function not tried): a TImode union (u128 + f32[4]) stays on the
 *     stack (sw + l.s); union {u64; f32[2]} .f[0] folds to li.s; `*(f32 *)&u64` ICEs (expr.c:566,
 *     convert_move); a one-member struct read through `*(f32 *)&s` folds to li.s.
 *   Conclusion: no in-block C form survives both cse2 and combine for a normal float bit pattern. The
 *   missing cause is something upstream of cse2 that hides G's value (not a label, a call, or the mode).
 */
/* Near miss / handoff (Opus, last tier, task b0786, 2026-10-27): func_0034B2C8
 * (InitAmmoBoltQuickSelectHud), 6,048 bytes, boot + 27 level places.
 *
 * Profile: default -O2 -G0 -ffunction-sections, compiled as its own unit (copy this file to
 * src/game/0034B2C8.c and turn the INCLUDE_ASM line in src/game/00345358.c into a comment).
 * A separate unit because 00345358.c defines several callees with conflicting prototypes
 * (func_003494D0 and func_00349970 take one argument there; retail passes arg in $a1 too;
 * func_003495D8 and func_00349A70 are defined float-first there).
 * Best tools/check.py: 6028 bytes, expected 6048, 0 of 28 places. Frame 0x160 (= retail).
 * Sequence-aligned against retail with spill slots 0x2C..0xA0 treated as equal: 1443 of
 * 1512 instructions identical (the b0761 draft scores 1394 by the same measure).
 *
 * New in b0786 (keep):
 *   - func_003495D8 and func_00349A70 are declared object/index first, `(o, index, f32 x5)`
 *     and `(o, row, group, f32 x4)`: ABI-identical to the float-first definitions (each
 *     register bank keeps its order; the neighbour func_003494D0 already calls
 *     func_003495D8_1(o, n, ...)). Argument loads are emitted in prototype order, and this
 *     gives retail's a0/a1-before-floats setup at about 25 call sites (+49 instructions).
 *
 * Kept from b0761 (each measured): loop 2 has its own counter `j`; loop 1 has separate BI
 * and Ico pointers; the fade fields (+8/+C, +0/+4) and the 0x7E8 +0xC clear go through
 * static inline helpers taking the object pointer; v[1],v[2],v[3],v[0] zeroing after
 * publishing the vector; D_001A7B90 declared sda.
 *
 * Still different:
 *   1. Spill-slot order is retail's rotated by one: self+0x604 takes the last slot (0xA0),
 *      every other slot is in the same order. Slots follow regno; the 35 PRE reaching regs
 *      are created in pre_delete's bucket order, bucket = (14029 + base regno + K) mod T,
 *      T = 711, base = self = pseudo 84, so 0x604 is bucket 11 (first) and 0x358 bucket 38.
 *      Brute force over T = 301..1601 and every base: only T = 711 with base regno = 46..72
 *      (mod 711) gives retail's order, i.e. retail hashed self+K on a pseudo numbered
 *      757..783 (this function has ~895 pseudos before gcse). Taking self's address
 *      (put_var_into_stack -> gen_mem_addressof gives the variable a new pseudo where the
 *      address is taken; purge_addressof keeps it) at the self+0x1288 block renames self
 *      to pseudo 741, but fixup_var_refs adds a copy for every earlier use (T 711 -> 931,
 *      no self-based PRE at all), so retail did not do that. No C spelling found that gives
 *      self a late pseudo without extra insns (a C++ `this` handling difference?).
 *   2. Double-use colours: retail keeps 0x60442D00 (0xBEC keys 1,2), 0xF0F0B0 (0xE0C keys
 *      0,1), 0x55F0C070 (0xCFC keys 1,2) and 0x1EFF (0x10D8 keys 0,1) in ONE float set
 *      right after the previous call: `lui/ori v0; mtc1 v0,$f20`, then `mov.s $f13,$f20` per
 *      use. Single-use normal colours are li.s ($at) and single-use denormals v0->$f13 in
 *      retail as here (the per-use helper below). The retail RTL must be a GPR temp that
 *      does not cross a call, copied once into a call-crossing float, with the copy left
 *      uncombined. A block-local float from a union or pointer-param helper (or a
 *      function-scope float from the store helper below) gives exactly that for the
 *      denormal 0x1EFF (the 0x10D8 block then matches retail byte for byte), but every
 *      form folds a normal value to li.s: cse2 fold_rtx SUBREG or combine's
 *      expand_field_assignment both call gen_lowpart_common(SF, const_int), and only
 *      mips_const_double_ok (1e-38 < |x| < 1e38) rejects the result. A subreg-stored float
 *      with 3+ uses becomes FP class but is hoisted above the call; with 2 uses regclass
 *      picks GR (the lui/ori split in sched1 adds 3 GR-only references), giving
 *      `mtc1 s0,$f13` per use (this file). func_00349D58 (also unmatched) contains the same
 *      0xBEC sequence with the same $f20 shape, so it is a shared construct.
 *      These colours also take $f20, so retail's other FP constants sit one register
 *      higher (0.3f in $f21), and the reload-register parity (v0/v1 in the lw/swc1 fade
 *      stores) follows from the extra reloads.
 *   3. Loop 1: sched1 issues the 0x442D00 colour store first after func_00335E20 (it
 *      carries REG_DEAD notes, lowest weight); retail issues it last, so it fills the
 *      sprintf jal slot, and the 0xF0F0B0 lui/ori come after the call.
 *   4. Tail: retail stores &D_001A79F8 to +0x2BC before the six 0/-1 stores; here the
 *      zero stores take the memory slot first. Two beqz slots of the D_001A7B90 ?: keep a
 *      nop in retail.
 *
 * Measured in b0810 (Opus, opus-3; C above unchanged, still 6028 bytes, 0 of 28):
 *   Slots (1): only self+0x604's PRE bucket must move above 680 (the last self-based
 *      bucket, self+0x4C). Writing the post-loop icon base as `w5 + 0x4C`, w5 = self+0x5B8 a
 *      top-declared local (pseudo 90), gives bucket 686 and the last reaching reg, as in
 *      retail. But w5 is set in bb 2, so block LCM inserts at the loop-2 preheader, not
 *      before loop 1 as retail does (frame 0x150, worse). Retail's base is therefore not
 *      killed in bb 2. No widget pointer that already exists in bb 0 (pseudos 98..192 here)
 *      falls in the pseudo range that would give bucket 681..710.
 *   Colours (2): cse2 folds (subreg:SF G) when G's constant is in its extended block: the
 *      costs tie at 16 (non-tieable SUBREG vs SF CONST_DOUBLE with a zero low word) and the
 *      folded form wins ties. An SF reg-to-reg copy (cost 1) survives cse2. combine then
 *      folds (set G K)+(set c (subreg:SF G)) through gen_lowpart_for_combine whenever G
 *      dies there, and (set (subreg:SI f) K)+(set c f) through expand_field_assignment
 *      (it refuses only to substitute a non-tieable SUBREG). local-alloc update_equiv_regs
 *      would move a once-set, once-used constant down to the conversion (retail's local
 *      v0 + one mtc1), but sched1 splits lui/ori SI constants first (two sets, no
 *      REG_EQUIV). A u64 union member stays one dli and does move, but adds dsll32/dsra32.
 *      One function-scope `f32 c` for all four double-use colours puts c in an FPR
 *      (retail has all four in $f20, which is why every other FP constant sits one
 *      register higher there), but its set still folds to li.s $at and is hoisted to the
 *      block start (1317 vs 1449 aligned with spill slots treated as equal).
 */
#include "common.h"

typedef union {
    s32 i;
    f32 f;
} HudBits_34B2C8;

extern char D_001AE668[];
extern char D_001AE678[];
extern char D_001AE688[];
extern char D_001AE690[];
extern char D_001AE6A0[];
extern char D_001AE6B0[];
extern char D_001AE6C0[];
extern char D_001AE6D0[];
extern char D_001AE6E0[];
extern char D_001ADFE0[];
extern char D_001ADFF0[];
extern char D_001AE000[];
extern char D_001AE010[];
extern char D_001AE020[];
extern s32 D_001A7B90 __attribute__((sda));
extern s32 D_001A79F8[] __attribute__((sda));

extern void func_003361E0(char *o, char *text, s32 arg);
extern void func_00336390(char *o, char *font, s32 n);
extern void func_00335E38(char *o, f32 x, f32 y, f32 z, f32 w);
extern void func_00335F88(char *o, f32 x, f32 y, f32 z, f32 w);
extern s32 *func_00335E20(char *o);
extern s32 *func_00335E18(char *o);
extern s32 *func_00335E10(char *o);
extern void func_00115484(void *dst, s32 c, s32 n);
extern void func_003369A8(char *o, char *text, s32 arg);
extern void func_00336A38(char *o, char *buf);
extern void func_00336A30(char *o, s32 n);
extern void func_00336710(char *o, char *text, s32 arg);
extern void func_00336920(char *o, s32 id, s32 n);
extern s32 func_00336E40(s32 arg);
extern f32 *func_00336DA8(s32 n, s32 a);
extern void func_00335F20(char *o, f32 *v);
extern void func_00335E68(char *o, s32 n);
extern void func_00115DA8(char *buf, char *fmt, s32 n);
extern f32 func_00283B98(f32 a, f32 b);
extern f32 func_00283180(f32 a);
extern f32 func_00283198(f32 a);
extern void func_00335EB0(char *o, s32 *v);
extern void func_00349D58(char *o, char *font, s32 arg);
extern void func_0034AFE8(char *o, f32 x, f32 y);
extern void func_003494D0(char *o, s32 arg);
extern void func_00349628(char *o, s32 n);
extern void func_003495D8(char *o, s32 index, f32 weight, f32 x, f32 y, f32 z, f32 w);
extern void func_00349610(char *o, s32 n, f32 a, f32 b);
extern void func_00349590(char *o, void *v);
extern void func_00349670(char *o, s32 v);
extern void func_003495C0(char *o, char *v);
extern void func_00349630(char *o, s32 v);
extern void func_00349678(char *o, f32 v);
extern s32 func_003495C8(char *o, s32 v);
extern void func_00349970(char *o, s32 arg);
extern void func_00349A60(char *o, s32 n, void *v);
extern void func_00349AA8(char *o, s32 n, s32 v);
extern void func_00349A70(char *o, s32 row, s32 group, f32 x, f32 y, f32 z, f32 w);
extern void func_00349B18(char *o, f32 v);
extern void func_0034CA90(char *o, s32 mode);
extern s32 func_002B0D70(void);

static inline f32 hud_bits_34B2C8(s32 i)
{
    f32 f;

    *(s32 *)&f = i;
    return f;
}

/* Two float fields of a fade/blend object (+0x8, +0xC). */
static inline void hud_fade_range_34B2C8(char *o, f32 lo, f32 hi)
{
    *(f32 *)(o + 0x8) = lo;
    *(f32 *)(o + 0xC) = hi;
}

/* Two float fields of a fade/blend object (+0x0, +0x4). */
static inline void hud_fade_start_34B2C8(char *o, f32 lo, f32 hi)
{
    *(f32 *)(o + 0x0) = lo;
    *(f32 *)(o + 0x4) = hi;
}

/* An int field at +0xC. */
static inline void hud_clear_0C_34B2C8(char *o)
{
    *(s32 *)(o + 0xC) = 0;
}

/* The ammo/bolt HUD setup: initialises the HUD's text, sprite and fade widgets. */
void func_0034B2C8(char *o, char *font, s32 arg)
{
    char *self = o;
    char buf[16];
    s32 i;
    s32 color = 0;
    f32 *v;

    *(s32 *)(self + 0x157C) = 0;
    *(s32 *)(self + 0x1580) = 0;
    func_003361E0(self, D_001AE668, arg);
    func_00336390(self, font + 0x8710, 1);
    func_00335E38(self, 10.0f, 10.0f, 0.0f, 0.0f);
    func_003361E0(self + 0x4C, D_001AE678, arg);
    func_00335E38(self + 0x4C, 10.0f, 10.0f, 0.0f, 0.0f);
    func_00336390(self + 0x4C, font + 0x8710, 2);
    func_003361E0(self + 0x98, D_001AE688, arg);
    func_00335E38(self + 0x98, 10.0f, 18.5f, 0.0f, 0.0f);
    func_00336390(self + 0x98, font + 0x8710, 5);
    func_00115484(self + 0xE4, 0, 0x18);
    func_003369A8(self + 0x100, D_001AE690, arg);
    func_00335F88(self + 0x100, 0.9f, 0.0f, 0.0f, 0.0f);
    func_00336A38(self + 0x100, self + 0xE4);
    func_00335E38(self + 0x100, 64.0f, 15.0f, 0.0f, 0.0f);
    func_00336A30(self + 0x100, 0);
    func_00336710(self + 0x148, D_001AE6A0, arg);
    func_00335F88(self + 0x148, 32.0f, 32.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x148, 20.0f, 15.0f, 0.0f, 0.0f);
    *func_00335E20(self + 0x148) = 0x60F0F0B0;
    func_003361E0(self + 0x184, D_001AE6B0, arg);
    func_00335E38(self + 0x184, 498.0f, 10.0f, 0.0f, 0.0f);
    func_00336390(self + 0x184, font + 0x8710, 3);
    func_003361E0(self + 0x1D0, D_001AE6C0, arg);
    func_00335E38(self + 0x1D0, 498.0f, 10.0f, 0.0f, 0.0f);
    func_00336390(self + 0x1D0, font + 0x8710, 4);
    func_00115484(self + 0x21C, 0, 0x18);
    func_003369A8(self + 0x238, D_001AE6D0, arg);
    func_00335F88(self + 0x238, 0.9f, 0.0f, 0.0f, 0.0f);
    func_00336A38(self + 0x238, self + 0x21C);
    func_00335E38(self + 0x238, 440.0f, 15.0f, 0.0f, 0.0f);
    func_00336A30(self + 0x238, 2);
    func_00336710(self + 0x280, D_001AE6E0, arg);
    func_00335F88(self + 0x280, 32.0f, 32.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x280, 457.0f, 15.0f, 0.0f, 0.0f);
    func_00336920(self + 0x280, 0x7567, 0);

    if (arg != 0) {
        v = func_00336DA8(0x10, func_00336E40(arg));
        *(f32 **)(self + 0x7E4) = v;
        v[1] = 0.0f;
        v[2] = 0.0f;
        v[3] = 0.0f;
        v[0] = 0.0f;
    }

    func_003361E0(self + 0x2C0, D_001ADFE0, arg);
    func_00336390(self + 0x2C0, font + 0x8710, 7);
    func_00335F88(self + 0x2C0, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x2C0, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0x442D00;
    *func_00335E20(self + 0x2C0) = color;
    func_00335F20(self + 0x2C0, *(f32 **)(self + 0x7E4));
    func_003361E0(self + 0x30C, D_001ADFF0, arg);
    func_00336390(self + 0x30C, font + 0x8710, 6);
    func_00335F88(self + 0x30C, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x30C, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xF0C070;
    *func_00335E20(self + 0x30C) = color;
    func_00335F20(self + 0x30C, *(f32 **)(self + 0x7E4));
    func_003361E0(self + 0x5B8, D_001AE000, arg);
    func_00336390(self + 0x5B8, font + 0x8710, 0x10);
    func_00335E38(self + 0x5B8, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xFFFEED;
    *func_00335E20(self + 0x5B8) = color;
    func_00335E68(self + 0x5B8, 0);

    for (i = 0; i < 8; i++) {
        char *w;
        char *ico;
        f32 angle;
        f32 x;

        func_00115DA8(buf, D_001AE010, i);
        w = self + (i * 0x4C + 0x358);
        func_003361E0(w, buf, arg);
        func_00336390(w, font + 0x8710, i + 8);
        func_00335F88(w, 1.0f, 1.0f, 0.0f, 0.0f);
        func_00335E38(w, 125.0f, 208.0f, 0.0f, 0.0f);
        func_00335F20(w, *(f32 **)(self + 0x7E4));
        color = 0x442D00;
        *func_00335E20(w) = color;
        func_00115DA8(buf, D_001AE020, i);
        ico = self + (i * 0x3C + 0x604);
        func_00336710(ico, buf, arg);
        func_00335E68(ico, 0);
        angle = func_00283B98((f32)i * 2.0f * 0.39269909f - 3.14159274f, 1.57079637f);
        x = (s32)(func_00283180(angle) * 82.14f) + 109;
        func_00335E38(ico, x, (s32)(func_00283198(angle) * 76.442f) + 189, 0.0f, 0.0f);
        func_00335F88(ico, 32.0f, 32.0f, 0.0f, 0.0f);
        color = 0xF0F0B0;
        *func_00335E20(ico) = color;
    }
    {
        s32 j;

        for (j = 1; j < 8; j++) {
            func_00335EB0(self + 0x358 + j * 0x4C, func_00335E18(self + 0x358));
            func_00335EB0(self + 0x604 + j * 0x3C, func_00335E18(self + 0x604));
        }
    }
    func_00335EB0(self + 0x2C0, func_00335E18(self + 0x358));

    func_00349D58(self + 0x7E8, font, arg);
    func_0034AFE8(self + 0x7E8, 147.0f, 10.0f);
    hud_clear_0C_34B2C8(self + 0x7E8);

    func_003494D0(self + 0xBEC, arg);
    func_00349628(self + 0xBEC, 3);
    func_003495D8(self + 0xBEC, 0, 0.0f, hud_bits_34B2C8(0x442D00), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xBEC, 1, 0.3f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xBEC, 2, 1.0f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f);
    func_00349610(self + 0xBEC, 1, 0.0f, 2.0f);
    func_00349590(self + 0xBEC, func_00335E20(self + 0x358));
    func_00349670(self + 0xBEC, 0);
    func_003495C0(self + 0xBEC, self + 0x1448);
    func_00349630(self + 0xBEC, -1);
    func_00349678(self + 0xBEC, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xBEC, 0);

    func_003494D0(self + 0xC74, arg);
    func_00349628(self + 0xC74, 3);
    func_003495D8(self + 0xC74, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xC74, 1, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xC74, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00349590(self + 0xC74, func_00335E18(self + 0x358));
    func_00349670(self + 0xC74, 0);
    func_003495C0(self + 0xC74, self + 0x1444);
    func_00349630(self + 0xC74, -1);
    func_00349678(self + 0xC74, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xC74, 0);

    func_003494D0(self + 0xE0C, arg);
    func_00349628(self + 0xE0C, 3);
    func_003495D8(self + 0xE0C, 0, 0.0f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xE0C, 1, 0.5f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f);
    func_00349610(self + 0xE0C, 0, 0.0f, 0.0f);
    func_003495D8(self + 0xE0C, 2, 1.0f, hud_bits_34B2C8(0x60F0F0B0), 0.0f, 0.0f, 0.0f);
    func_00349610(self + 0xE0C, 1, 0.0f, 0.0f);
    func_00349590(self + 0xE0C, func_00335E20(self + 0x604));
    func_00349670(self + 0xE0C, 0);
    func_003495C0(self + 0xE0C, self + 0x1448);
    func_00349630(self + 0xE0C, -1);
    func_00349678(self + 0xE0C, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xE0C, 0);

    func_003494D0(self + 0xCFC, arg);
    func_00349628(self + 0xCFC, 3);
    func_003495D8(self + 0xCFC, 0, 0.0f, hud_bits_34B2C8(0xF0C070), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xCFC, 1, 0.3f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xCFC, 2, 1.0f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f);
    func_00349610(self + 0xCFC, 1, 0.0f, 3.0f);
    func_00349590(self + 0xCFC, func_00335E20(self + 0x30C));
    func_00349670(self + 0xCFC, 0);
    func_003495C0(self + 0xCFC, self + 0x1448);
    func_00349630(self + 0xCFC, -1);
    func_00349678(self + 0xCFC, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xCFC, 0);

    func_003494D0(self + 0xD84, arg);
    func_00349628(self + 0xD84, 3);
    func_003495D8(self + 0xD84, 0, 0.0f, 1.2f, 1.2f, 0.0f, 0.0f);
    func_003495D8(self + 0xD84, 1, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xD84, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00349590(self + 0xD84, func_00335E18(self + 0x30C));
    func_00349670(self + 0xD84, 0);
    func_003495C0(self + 0xD84, self + 0x1444);
    func_00349630(self + 0xD84, -1);
    func_00349678(self + 0xD84, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xD84, 0);

    func_003494D0(self + 0xE94, arg);
    func_00349628(self + 0xE94, 3);
    func_003495D8(self + 0xE94, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xE94, 1, 0.01f, 1.0f, 1.0f, 0.0f, 0.0f);
    func_003495D8(self + 0xE94, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00349590(self + 0xE94, *(f32 **)(self + 0x7E4));
    func_00349670(self + 0xE94, 0);
    func_003495C0(self + 0xE94, self + 0x1444);
    func_00349630(self + 0xE94, -1);
    func_00349678(self + 0xE94, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xE94, 0);

    func_00349970(self + 0xF1C, arg);
    func_00349A60(self + 0xF1C, 0, func_00335E20(self));
    func_00349AA8(self + 0xF1C, 0, 0x442D00);
    func_00349AA8(self + 0xF1C, 1, 0x60442D00);
    hud_fade_range_34B2C8(self + 0xF1C, 0.0f, 2.0f);
    func_00349A60(self + 0xF1C, 1, func_00335E18(self));
    func_00349A70(self + 0xF1C, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    func_00349A70(self + 0xF1C, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00349A60(self + 0xF1C, 2, func_00335E10(self));
    func_00349A70(self + 0xF1C, 2, 0, 50.0f, 25.0f, 0.0f, 0.0f);
    func_00349A70(self + 0xF1C, 2, 1, 10.0f, 10.0f, 0.0f, 0.0f);

    func_00349970(self + 0xFB0, arg);
    func_00349A60(self + 0xFB0, 0, func_00335E20(self + 0x4C));
    func_00349AA8(self + 0xFB0, 0, 0xF0C070);
    func_00349AA8(self + 0xFB0, 1, 0x55F0C070);
    hud_fade_range_34B2C8(self + 0xF1C, 0.0f, 3.0f);
    func_00349A60(self + 0xFB0, 1, func_00335E18(self + 0x4C));
    func_00349A70(self + 0xFB0, 1, 0, 1.2f, 1.2f, 0.0f, 0.0f);
    func_00349A70(self + 0xFB0, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00349A60(self + 0xFB0, 2, func_00335E10(self + 0x4C));
    func_00349A70(self + 0xFB0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    func_00349A70(self + 0xFB0, 2, 1, 10.0f, 10.0f, 0.0f, 0.0f);

    func_00349970(self + 0x1044, arg);
    func_00349A60(self + 0x1044, 0, func_00335E20(self + 0x100));
    func_00349AA8(self + 0x1044, 0, 0xF0F0F0);
    func_00349AA8(self + 0x1044, 1, 0x80F0F0F0);
    hud_fade_range_34B2C8(self + 0x1044, 0.0f, 3.0f);

    func_003494D0(self + 0x10D8, arg);
    func_00349628(self + 0x10D8, 3);
    func_003495D8(self + 0x10D8, 0, 0.0f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0x10D8, 1, 0.5f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0x10D8, 2, 1.0f, hud_bits_34B2C8(0x80001EFF), 0.0f, 0.0f, 0.0f);
    func_00349590(self + 0x10D8, func_00335E20(self + 0x98));
    func_00349670(self + 0x10D8, 0);
    func_003495C0(self + 0x10D8, self + 0x1448);
    func_00349630(self + 0x10D8, 1);
    func_00349678(self + 0x10D8, 0.06666f);

    func_00349970(self + 0x1160, arg);
    func_00349A60(self + 0x1160, 0, func_00335E20(self + 0x148));
    func_00349AA8(self + 0x1160, 0, 0xF0F0B0);
    func_00349AA8(self + 0x1160, 1, 0x60F0F0B0);
    hud_fade_range_34B2C8(self + 0x1160, 0.0f, 3.0f);
    func_00349B18(self + 0x1160, 0.06666f);

    func_00349970(self + 0x11F4, arg);
    func_00349A60(self + 0x11F4, 0, func_00335E20(self + 0x184));
    func_00349AA8(self + 0x11F4, 0, 0x442D00);
    func_00349AA8(self + 0x11F4, 1, 0x60442D00);
    hud_fade_range_34B2C8(self + 0x11F4, 0.0f, 2.0f);
    func_00349A60(self + 0x11F4, 1, func_00335E18(self + 0x184));
    func_00349A70(self + 0x11F4, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    func_00349A70(self + 0x11F4, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00349A60(self + 0x11F4, 2, func_00335E10(self + 0x184));
    func_00349A70(self + 0x11F4, 2, 0, 458.0f, 25.0f, 0.0f, 0.0f);
    func_00349A70(self + 0x11F4, 2, 1, 498.0f, 10.0f, 0.0f, 0.0f);

    func_00349970(self + 0x1288, arg);
    func_00349A60(self + 0x1288, 0, func_00335E20(self + 0x1D0));
    func_00349AA8(self + 0x1288, 0, 0xF0C070);
    func_00349AA8(self + 0x1288, 1, 0x55F0C070);
    hud_fade_range_34B2C8(self + 0x1288, 0.0f, 3.0f);
    func_00349A60(self + 0x1288, 1, func_00335E18(self + 0x1D0));
    func_00349A70(self + 0x1288, 1, 0, 1.2f, 1.2f, 0.0f, 0.0f);
    func_00349A70(self + 0x1288, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    hud_fade_start_34B2C8(self + 0x1288, 0.0f, 3.0f);
    func_00349A60(self + 0x1288, 2, func_00335E10(self + 0x1D0));
    func_00349A70(self + 0x1288, 2, 0, 514.0f, 4.0f, 0.0f, 0.0f);
    func_00349A70(self + 0x1288, 2, 1, 498.0f, 10.0f, 0.0f, 0.0f);

    (void)&o;
    func_00349970(self + 0x131C, arg);
    func_00349A60(self + 0x131C, 0, func_00335E20(self + 0x238));
    func_00349AA8(self + 0x131C, 0, 0xF0F0F0);
    func_00349AA8(self + 0x131C, 1, 0x80F0F0F0);
    hud_fade_range_34B2C8(self + 0x131C, 0.0f, 3.0f);

    func_00349970(self + 0x13B0, arg);
    func_00349A60(self + 0x13B0, 0, func_00335E20(self + 0x280));
    func_00349AA8(self + 0x13B0, 0, 0xF0F0B0);
    func_00349AA8(self + 0x13B0, 1, 0x60F0F0B0);
    hud_fade_range_34B2C8(self + 0x13B0, 0.0f, 3.0f);

    func_003494D0(self + 0x144C, arg);
    func_00349628(self + 0x144C, 2);
    func_00349590(self + 0x144C, func_00335E20(self));
    func_003495C0(self + 0x144C, self + 0x1448);
    func_00349678(self + 0x144C, 0.02f);
    func_003495D8(self + 0x144C, 0, 0.0f, hud_bits_34B2C8(0x70202080), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0x144C, 1, 1.0f, hud_bits_34B2C8(0x70242335), 0.0f, 0.0f, 0.0f);
    func_00349670(self + 0x144C, 2);
    func_00349630(self + 0x144C, 1);
    func_003495C8(self + 0x144C, 0);

    func_003494D0(self + 0x14D4, arg);
    func_00349628(self + 0x14D4, 2);
    func_00349590(self + 0x14D4, func_00335E20(self + 0x4C));
    func_003495C0(self + 0x14D4, self + 0x1448);
    func_00349678(self + 0x14D4, 0.02f);
    func_003495D8(self + 0x14D4, 0, 0.0f, hud_bits_34B2C8(0x606060C0), 0.0f, 0.0f, 0.0f);
    func_003495D8(self + 0x14D4, 1, 1.0f, hud_bits_34B2C8(0x60424162), 0.0f, 0.0f, 0.0f);
    func_00349670(self + 0x14D4, 2);
    func_00349630(self + 0x14D4, 1);
    func_003495C8(self + 0x14D4, 0);

    *(s32 **)(self + 0x2BC) = D_001A79F8;
    *(s32 *)(self + 0x1564) = 0;
    *(s32 *)(self + 0x1568) = -1;
    *(s32 *)(self + 0x156C) = 0;
    *(s32 *)(self + 0x1570) = -1;
    *(s32 *)(self + 0x1574) = 0;
    *(s32 *)(self + 0x1578) = -1;
    func_0034CA90(self, 0);
    *(s32 *)(self + 0x1588) = func_002B0D70();
}
