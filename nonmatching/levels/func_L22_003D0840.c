/* 8 November 2026 (Sonnet round): rewrite from retail asm re-measured 60/60, 0/1, object still $v1 vs $a3. Seven new wordings (state byte in a local, `t = x; t |= 0x41` two-step, u16 named local, `*p |= 0x41`, call with a local k, cast-to-int store) all still $v1. One decomp-permuter run (1500 s, -j2) only tied the base (score 25); its candidates use an uninitialised a3, so none kept. */
/* 8 November 2026 (Sonnet round): rewrite from retail asm gives the same 60/60, 0/1, $v1 vs $a3; 3 more wordings (4-param signature, flag/halfword in locals, int-returning callee) unchanged; one permuter run (1500 s, -j2) found nothing under base score 20. */
/* 8 November 2026 (m2z, caller-save angle): global.c:1516 tries caller-saves only when find_reg found no register (best_reg < 0), so CALLER_SAVE_PROFITABLE (4*calls < refs) never decides s-register versus call-clobbered while an s-register is free. cc1 -S on the retained C with and without -fno-caller-saves: identical body (0 lines differ). The object pseudo dies at the only call (crosses 0 calls), so caller-saves cannot touch it; $v1 versus $a3 is find_reg order. Angle closed; no check.py runs. */
/* 8 November 2026 (m3, round 3 permuter): 35-minute decomp-permuter run (-j3) on the retained C: no candidate beat the base (best ties only); object still in $v1. */
/* 8 November 2026 (m8e): re-measured on master's compiler (sticky volatile default, mtc1 fix): unchanged, 60/60, 0/1, object in $v1 vs $a3 (4 words). New, still $v1: `register` parameter with `|=` flags. Sibling func_L22_00385F40 (s32 param, switch case 0) gives no new form; its object also takes $v1 by the same rule. Marker kept. */
/* 7 November 2026, round 12 (follow-up to 6 November): 96 source variants,
 * no improvement; retained C is 60/60 bytes, 0/1 places in each of US, PAL
 * and US2 with default -O2 -G0 -ffunction-sections. Four real words differ:
 * the object copy, state load, flag load and flag store use v1, retail a3;
 * the unresolved jal in --diff is a relocation, not an instruction mismatch.
 * New lifetime experiments: next/none initialized before the state test plus
 * a parameter copy after its first use; flags read before the state test in
 * all six read/copy orders; state/flags locals reused for the frame argument;
 * nested one-pass state-read/copy groups; all six inline initializer formal
 * orders (object, next state, frame) with grouped flag update or state call.
 * Early constants/helpers tie the baseline; preloaded flags give eight word
 * differences; state-read/copy groups add an epilogue nop (64/60 bytes).
 * No forbidden constructs or changed external interfaces were used. The next
 * useful experiment needs a real second lifetime that survives CSE without
 * adding accesses or changing the callback/SetState contracts. Marker kept.
 */
/* 6 November 2026, round 11: still $v1 (60/60, 0/1), 33 compiles. Level 22 vtbl.bin +0x394 lists this function as the update slot of moby class 0xA6C (like matched func_L22_00385F40), so the signature is void (Moby *): no extra parameter and no return value. New, still $v1: a typed Moby struct (u8 state +0x20, u16 modeBits +0x34) with ->state / ->modeBits |= 0x41; int and Moby * return types with no return statement; early `return moby->state` (16 insns); `return state` (18); an unused second parameter; volatile modeBits, volatile state, volatile Moby *; u32 handle and void * parameters; state read into a local and passed as state + 1 / state - 1 (also with `state < 1`, both fold to 1/-1); `moby->state + 1` as the argument (16); switch with default; empty else; ternary/comma; return-in-both-arms; u16 * and u8 * interior pointers; int flags temp; do-while around the whole if (14 insns), around the call or around the flag store (14, no copy). RTL reading (greg: pointer refs 5, conflicts v0 a0 a1 a2 sp): the pointer has the most refs, so it is the first global allocno and takes the first free register; $v1 can only be excluded by a hard register or a local-alloc pseudo that is live with it, and a block-1 local copy used as the call argument is suggested $a0 (free there) by local-alloc, while cse canonicalises every same-mode copy to the parameter. No legal source form found. */
/* 6 November 2026, round 10: still $v1 (60/60, 0/1). RTL (-dl/-dg, unit flags): only one global pseudo, the object (84), conflicting with $v0 (local 86/88/90), $a0 (call-arg set before the sh), $a1, $a2; no allocno prefers $v1, so find_reg takes $v1. Matched func_L22_00385F40 gives its object pseudo $v1 by the same rule ($v0 holds the case-1 constant, $a0 the switch value), so it adds no new constraint. Retail needs $v1 excluded with no trace: reload_cse_simplify_operands never rewrites register operands (reload1.c), so the only fitting path is a second copy Q of the object in $v1 used only as the call argument (`a0 = Q` becomes a no-op, then flow2 deletes the dead `Q = a0`, flow.c:2732). Q can avoid $a0 only if $a0 is live while Q lives; cse always merges a same-mode copy. A DImode union copy (`union { u8 *p; unsigned long q; }`) does put the object in $a3 but adds dsll/dsrl/and/or insert code. Also still $v1: -flive-range, the sibling flags (-mno-split-addresses, -G8 -malign-loops=2), the two new -frac2 flags, 28 single -f flags, an SImode union copy, a comma expression in the call argument, `while (...) { ...; break; }`. */
/* 6 November 2026, round 9: compiler-difference hypothesis falsified. Probe cc1 (global.c find_reg, env-gated, all 8893 non-SDK src/ and nonmatching/ units compiled to .s and diffed): (a) a0-a3 before v1 in global alloc only: 2826 src units change; same order also in local alloc (REG_ALLOC_ORDER): 5384; (b) a pseudo with a copy preference for a0-a3 takes a free argument register over v1: 52 src units change; narrowest, a parameter pseudo (incoming a0-a3) takes a free argument register over v1: target becomes $a3 but 20 other matched functions change (12 USA, 6 PAL, 2 US2), including matched func_L22_00385F40 (same level, same `func_002A7750(obj, 1, -1)` call, retail keeps the parameter in $v1). No allocator-order rule explains this $a3; the cause is upstream of global alloc (a conflict or preference retail has that this RTL lacks). */
/* 6 November 2026, round 8: still $v1 (60/60, 0/1). Donors: RAC4 has many callers of its state setter with (obj, 1, -1) (e.g. overlays/shared/L01_004E5DD0.c switch on +0x20 with case 0 calling it), and the 0x41 flag only as `(f | 0x41) & 0xEFFF` before a different call (L01_00489448.c, L08_004CFDC0.c, RAC2 func_L20_00440460); none has this ori-only shape. RAC1 has `|= 0x41` at +0x34 but no (obj, 1, -1) setter call. New, still $v1: `*(short *)` flags with `|=`; the RAC4 form `void *object` + `switch (*((u8 *)object + 0x20)) { case 0: ...; break; }`. */
/* 6 November 2026, round 6: still $v1 (60/60, 0/1). Tried: a block-local `self = object` used only as the call argument after a one-pass flag group (cse merges it; the object stays in $a0 with no copy, the sh moves before the call setup); flags in a named u16 set then or-ed; `self` set after an early return; a switch with an empty `case 1`; the callee's mode parameter as `unsigned char` (00300618-state.c precedent); an unused `work = object[0x68]` load. An opaque asm copy (probe only) shows a second global copy just takes $a0 and leaves the object in $v1, so $a3 needs a local in $v1 across the object's life that reload_cse/flow2 then delete; no legal source found. The callee returns void, so an unused return value is not available. */
/* 5 November 2026, round 5: still $v1. No sched1/allocator tie-break change was found that covers this allocation; the L00 sibling matched through a single-set data pointer (sched1 birthing priority), which has no counterpart here (the pointer is set once already). */
/* 5 November 2026, round 4: still $v1. `-1` as a `long` argument gives the same addiu and $v1. `state = object[0x20]` with call(object, state + 1, state - 1): cse folds both through the jump equivalence, same bytes. `long`/`u64` flag temps: $a3 but dli/or/andi (DImode ior takes no immediate here). Sibling func_L20_00440460 uses default -G0 flags and the same 3-int callee prototype; its $a3 comes from a second live pointer. Needed: a block-1 local that local-alloc puts in $v1 and reload then deletes (e.g. a constant arg reload_cse turns into li). */
/* 5 November 2026: still $v1 (60/60, 0/1). global.c prune_preferences counts only lower-priority conflicting allocnos' full prefs; no RTL here names $v1, so none prefers it. Inline helpers, bitfields, -g/qcopy flags: all $v1. Any do-while (update, s=1, flags) is a sched barrier: sh before a0 setup, pointer stays in $a0, 56 B.
 * `unsigned long long f` gives $a3 (0x41 lands in $v1 via dli) but adds dli/or/andi. */
/* 5 November 2026: new, still $v1 (60/60, 0/1): K&R definition; the call through a 4-argument view passing the object again as a3 (64 bytes, still $v1, and a false prototype anyway). Remaining: the object pointer in $v1, retail $a3. */
/* 5 November 2026: lesson-3 copy (`self = object; object += 0x34; *(u16 *)object |= 0x41; call(self)`) keeps a second pointer but cse/combine do not fold the +0x34 back: 64/60 bytes, still $v1. global.c find_reg skips regs_someone_prefers first, so $a3 needs a conflicting pseudo that prefers $v1 or a block-local copy that local-alloc puts in $v1; no legal source found for either. */
/* 4 November 2026: a real one-pass flag-update/state-change group, as seen
 * in current RAC1 game C, gives 64/60 bytes and 0/1 USA. The object still
 * uses v1 rather than a3 and an extra alignment nop remains. No improvement;
 * the probe is retained privately. Keep the meaningful pointer-based baseline
 * and canonical three-argument state setter below. Its declaration cleanup
 * is not a new matching measurement; older results remain historical.
 */
/* Near miss from src/levels/22_dobbo_orbit/L22_00358778.c — 1 word (4 bytes) differ.
 *
 * Kept as a starting point; not linked, not counted.
 *
 * The body below compiles to retail's exact size (60 bytes) and instruction for
 * instruction, except the one `daddu` that copies the parameter, where GCC
 * allocates $v1 and retail has $a3:
 *
 *   003D0844  daddu $v1, $a0, $zero   |  daddu $a3, $a0, $zero
 *
 * Two things the retail bytes settle, both easy to get backwards:
 *   - `bnez $v0` at 0x3D0850 carries `ld $ra, 0x0($sp)` in its delay slot, so the
 *     branch leaves the early return already half done.
 *   - `sh $v0, 0x34($a3)` at 0x3D086C is in the delay slot of `jal`, so it runs
 *     *before* the call. Reading the halfword, OR-ing 0x41 and storing it are all
 *     ahead of func_31FBB8, not after it.
 *
 * An earlier draft here passed four arguments to func_31FBB8 and came out 64
 * bytes; the call takes three.
 *
 * Ten wordings were tried and all produce $v1: `if (...) { }` and early-return
 * shapes, `|=` against a separate temporary and against a stored value, a `u16 *`
 * alias, and the whole body with `s32` in place of `char *`. Getting $a3 needs
 * whatever makes GCC treat $a3 as an ordinary temporary rather than an incoming
 * argument register, which this source shape does not: the call takes exactly one
 * pointer, so $a0-$a2 are seeded first and $v1 is the next free hard register.
 *
 * Not yet tried: a wording where the copy is not a plain assignment (a cast
 * through a wider type, or the parameter being read once before it is copied).
 */

/* Standalone declarations recovered from src/levels/22_dobbo_orbit/L22_00358778.c. */
typedef unsigned char u8;

typedef unsigned short u16;

typedef int s32;

extern void func_002A7750(u8 *, int, int);

void func_L22_003D0840(u8 *object) {
    if (object[0x20] == 0) {
        u16 flags = *(u16 *)(object + 0x34) | 0x41;
        *(u16 *)(object + 0x34) = flags;
        func_002A7750(object, 1, -1);
    }
}
/* Second attempt (wave 24, worker 15): the same one word off, same check line
   ("22_dobbo_orbit: instruction at +0x4 differs").  Ten more wordings tried
   and all still $v1: the parameter in a named local; the parameter as
   char * / u8 * / u16 *; two pointers spelled separately (they are CSE'd into
   one); the call argument taken from the local instead of the parameter; the
   halfword or through a named local; the byte test through a named local;
   the store written out longhand; the callee declared with and without a
   parameter list; and the unit at -G0 and at -G8 (the profile makes no
   difference here).  The retail's own matched func_L20_00440460 gets the
   same copy in $a3 and it has a second pointer in its body, so the
   allocation seems to want a second live value - that is the next thing to
   try. */
/* Opus 5.5 xhigh, 31 October 2026: best is still this draft, 60/60 bytes, 0/1
   places, four slots differ, all the object pointer in $v1 against $a3.  The
   callee is func_002A7750 (level 22 place 0x31FBB8), three parameters.

   Measured: regalloc gives the pointer conflicts with $v0, $a0, $a1, $a2 and
   $sp only, so the allocator's next free register is $v1; retail needs $v1
   excluded.  Same bytes, still $v1: single-case switch; inlined flag setter;
   inlined setter plus call; call through a named copy with `p = obj` as the
   argument; argument read through `*pp`; struct by value; typed struct
   parameter; u32 temporary; u16 * view; interior pointer; s32 result returned
   (18 instructions, adds $s0).  A fourth argument (false prototype, not usable)
   gives 64 bytes and still $v1.  An s64 parameter adds a shift pair.  None of 24
   single extra flags on the plain wording gives $a3 (-O1 and -fno-schedule-insns
   lose the copy altogether).
   Retail scan: of the level catalogue's functions up to 160 bytes that copy $a0
   to $a3 near the start, this is the only one that never touches $v1.

   Hypothesis, not demonstrated: a local pseudo held $v1 during allocation and its
   instructions were deleted after reload: `$v1 = pointer`, then `$a0 = $v1`
   removed as a no-op by reload_cse (entry copy means $a0 already holds it), then
   the first move removed as dead.  That needs a copy CSE does not merge, and no
   wording here keeps one. */
