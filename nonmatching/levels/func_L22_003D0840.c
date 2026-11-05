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
