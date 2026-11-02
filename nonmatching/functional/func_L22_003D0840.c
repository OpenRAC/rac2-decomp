/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
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

extern void func_31FBB8();

void func_L22_003D0840(s32 a0) {
    s32 a3 = a0;
    if (*(u8 *)(a3 + 0x20) == 0) {
        u16 v = *(u16 *)(a3 + 0x34) | 0x41;
        *(u16 *)(a3 + 0x34) = v;
        func_31FBB8(a3, 1, -1);
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
