/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Claude Fable 5.1 fable tier, task v0811, 2026-10-29: C below unchanged, not matched.
 * Recompiled on this checkout as its own unit (L10_00424028-hud-g8.c, -O2 -G8
 * -ffunction-sections): 1836/1852 bytes, 0/1 places; with -fno-cse-skip-blocks (probe only)
 * 1840/1852, 0/1. No new C wording was tried: every residual difference below is a decision
 * of this cc1's allocator, reload or schedulers that no source shape reaches, so the notes
 * are the deliverable. Measured on this cc1's dumps (cc1 -dj -ds -dG -dL -dt -df -dc -dS
 * -dl -dg -dR) and the archive sources (/tmp copies of gnu-ee-binutils-gcc-1.1).
 *
 * 1. Register roles. Retail: state $s0, each block's 0x8710 constant $s1 where state or
 *    the compare constant 1 is live ($s0 elsewhere), the else arm's constant 1 in $s0, ghost
 *    $s2, second/third/fourth in $s3/$s4/$s5. This cc1: the 0x8710 pseudo of every draw block
 *    is block-local (lreg: "Register 98 used 3 times across 50 insns in block 4; crosses 2
 *    calls") and local-alloc runs before global-alloc, so find_free_reg hands it the first
 *    callee-saved register, $s0, before `state` (a global pseudo, reg_renumber still -1 and so
 *    absent from regs_live_at) gets anything; state then takes $s1. Retail's roles are what
 *    global-alloc gives when it allocates everything in allocno_compare order: state (4 refs /
 *    65 insns), then the 1 (2 refs / 18 insns), then the 0x8710 pseudos (3 refs / ~50 insns),
 *    then a pseudo born at the else arm's head and live across the sprintf call (the ghost,
 *    $s2), then second/third/fourth. That order also needs the 1 to be a pseudo with a
 *    callee-saved home although its only use is the `bne` (reorg can move `addiu $s0,$zero,1`
 *    from in front of the compare into the first jal slot: it is the first candidate in the
 *    forward scan that sets no call-clobbered register and reads no memory), which this cc1
 *    never does: update_equiv_regs keeps `(set r 1)` next to its single use and local-alloc
 *    gives it $a1 (`addiu $a1,$zero,1`), which in turn blocks x-0x33 from being computed
 *    straight into $a1 (retail `addiu $a1,$v1,-0x33`, here `addiu $v1,$v1,-0x33` +
 *    `daddu $a1,$v1`). The `beql` at the early return follows from state being in $s0 (live on
 *    the fall-through, so the `ld $s0` restore must be annulled); here $s0 is dead there.
 * 2. The ghost $s2 is a pseudo with a frame-address or constant REG_EQUIV that global-alloc
 *    allocated and reload then replaced by its equivalence at every use (the sibling record
 *    nonmatching/levels/func_L02_003FF6E8.c, same family: retail `addiu $t1,$sp,0x80` at the
 *    func_0028EA58 call, `daddu $a0,$sp,$zero` / `daddu $a3,$sp,$zero` at the sprintf and
 *    func_0027F5B8 calls, all rematerialised). In this cc1 every reg_equiv_constant /
 *    reg_equiv_address substitution in reload1.c requires reg_renumber < 0, and reload only
 *    takes a callee-saved register from its pseudo when every call-clobbered one is live or
 *    allocated at the insn (order_regs_for_reload per insn; greg: the fix_truncsfsi2 SI scratch
 *    takes $v1 at every cvt.w.s here). The retail fix output in $a0 (`mfc1 $a0,$f0`, here $v0)
 *    is the same story: with `daddu $a0,$v0` after the chain, $v1 should be the first free
 *    register for it; something invisible held $v1.
 * 3. cse. The draft's cse1 (x.i.cse) merges the text position's 0.5 (insn 659) into the arm's
 *    shared 0.5 (r217) and the func_0028EA58 &colors (insn 616, fp+128) into the block move's
 *    address pseudo (r243), because cse_end_of_basic_block skips the `if (D_L10_001B2D80 == 1)
 *    y += 1.0f` block (AROUND: no label between the bne and its target, LABEL_NUSES 1). Retail
 *    has a fresh `lui $at,0x3F00; mtc1 $at,$f1` for the text and `addiu $t1,$sp,0x80` in the
 *    call slot, exactly the -fno-cse-skip-blocks output (1840 bytes); nothing in the C puts a
 *    label in that block. If the ghost were r243 it would need the skip, so the two retail
 *    facts conflict unless the ghost is the text pointer (sp+0) or the format address.
 * 4. Scheduling. In all five draw blocks retail issues the y chain (lwc1 Y, cvt, lwc1 scale,
 *    [lwc1/cvt X], mul, add, cvt.w, mfc1, mtc1, nop, cvt.s.w) with no filler and only then
 *    the -1/1/0 (1.35/1/0) constant sets, lui a1, a0 = v0, ori a1, f14-f16: RTL order except
 *    that `f12 = (float)X` (insn 92) and `f13 = (float)fix` (94) were pulled up. In this cc1
 *    both schedulers fill the chain's latency gaps (sched1 trace, block 4: the constants are in
 *    the ready list at t=1 since REG_N_CALLS_CROSSED > 0, 82 issues with the call at t=3, 84/86
 *    on the memory unit at t=5/6 while the chain waits); -fno-schedule-insns and both
 *    schedulers off were re-measured (sched2 alone still hoists `li.s $f21,-1.0` to the first
 *    instruction after the jal; with both off X is not in the chain, so retail did schedule).
 *    No dependence in haifa-sched.c links a constant set to the chain; the matched sibling
 *    func_002D2918 shows the same scheduler interleaving `lui/mtc1 $f14` into its chain. So
 *    retail's constants were not ready during the chain for a reason this tree does not model
 *    (the same gap as func_L02_003FF6E8's last block and the 444-byte family).
 * Unblocking is compiler-side only: (a) an allocation pass in which block-local call-crossing
 * constant pseudos are ordered after global pseudos (retail's $s0/$s1 roles), (b) reload
 * rematerialising REG_EQUIV pseudos that hold a hard register (the 21 ghost functions),
 * (c) constant and argument setup kept behind the conversion chain. A C that is exact would
 * still need all three; do not retry source wordings for this family (func_L05_00421B98,
 * func_L15_00431590, func_L25_0040DE40 are byte-identical twins).
 */
/* Claude Opus 5.5 opus-2 tier, task v0772, 2026-10-29: C below unchanged, not matched.
 * Recompiled on this checkout: 1836/1852 bytes, 0/1 places (own -G8 unit, default profile).
 * New measurements (probes only, never landed):
 *  - The draw-block order is retail's RTL expansion order: after the y chain, retail emits
 *    the const pseudos (-1/1/0 or 1.35/1/0, insns 82/84/86 in the .loop dump), then
 *    a0/a1/f14-f16 (88-100). Neither scheduler leaves them there here: both put them into
 *    the chain's stalls. -fno-schedule-insns, -fno-schedule-insns2, both, -fno-sched-interblock,
 *    -fno-sched-spec and -fno-expensive-optimizations (constants then go straight to
 *    f14-f16) are all worse. An `asm volatile("")` after a standalone y does not help either:
 *    combine moves the f12/f13 conversions to the post-barrier arg moves.
 *  - The pattern is family-wide: retail func_00326A10 (unused saved $s0) also sets its
 *    -0.5/1/0 constants after the chain, and it reloads 454.0 straight into $f12 at each draw
 *    (`lui $at,0x43E3; mtc1 $at,$f12`). That is a constant-equivalent pseudo with no hard
 *    register, rematerialized by reload. This cc1 keeps it in a sixth saved FPR. The unused
 *    saved GPR fits the same picture: a pseudo marked live, then spilled to its equivalence.
 *  - Retail's fix temporaries: $a0 here (v0 holds the sprite) and $v1 in func_00326A10.
 *    Both look like reload taking the SI scratch first (lowest free GPR) and then the output.
 *    Here, local-alloc chooses the output before reload chooses the scratch.
 *  - `y = (D_L10_001B2D80 == 1) ? y + 1.0f : y;` folds to the same RTL as the if (1836).
 * Claude Opus 5.5 opus-1 tier, task v0663, 2026-10-28: C below unchanged, not matched.
 * Best: 1836/1852 bytes, 0/1 places as its own -G8 unit (L10_00424028-hud-g8.c, default
 * profile); with `-fno-cse-skip-blocks` on that unit (probe only) 1840/1852, 0/1.
 * New measurements, this cc1 (cc1 -dS -dR -dl -dg):
 *  - Box call: retail's `daddu a3,v0 ... jal func_0028EA58 ; addiu t1,sp,0x80` is exactly
 *    what -fno-cse-skip-blocks gives. By default cse1 skips the `if (D_L10_001B2D80 == 1)
 *    y += 1.0f` block and replaces the call's &colors (insn 616, fp+128) with the block
 *    move's address pseudo, which then crosses func_0028E588 in $s0. Retail recomputes it at
 *    the call but still saves the unused $s2: either reload evicted that pseudo from $s2 and
 *    rematerialised it (as for ctx in func_L02_003FF6E8), or $s2 was an unprinted reload
 *    scratch. This cc1 (reload1.c from 2.95.2, patch 0047) never does either: its fix and
 *    block-move scratches are $v1/$v0/$a2/$a3/$t0 (greg "Spilling for insn" lines).
 *  - Retail keeps the constant 1 of the D_L10_001B2D80 compare in $s0. Reorg moved it into
 *    the first func_00336D50 jal slot from just before the compare, which is legal only
 *    because $s0 is untouched in between; a non-call-crossing pseudo in $s0 is again an
 *    allocation this cc1 does not make. That frees $a1 for x - 0x33 in retail.
 *  - Scheduling: in every draw and in the func_0027F5B8 call, retail interleaves plain
 *    pseudo arithmetic (the x load and x+5) with the y chain, but every hard-register
 *    argument setup (a0 = v0, the colour, a3 = sp, t0) and the -1/1/0 or 1.35/1/0 argument
 *    constants come after the chain, in RTL order. Both sched1 and sched2 here (fmac 3,
 *    loads 2, issue 2) fill the chain's latency gaps with them; -fno-schedule-insns gives
 *    1792 bytes, and an inline rounding helper changes nothing. Compiler-side; no C wording
 *    found that orders them.
 */
/* GPT-6.1 Sol high tier, task v0494, 2026-10-28.
 * USA v1.01, -O2 -G8 -ffunction-sections: 1836/1852 bytes, 0/1 places.
 * Adapted the retained func_L05_00421B98 counterpart to this level's symbols,
 * +0x4C timer and 1.35f scale. The text style is a real u64 argument; the
 * 16-byte colour copy and format string name the measured level data.
 * Retail retains an unused saved s2 (0xF0 frame); this C has a 0xE0 frame.
 * State/0x8710 allocation is s1/s0 instead of s0/s1. FP constants and sprite
 * argument setup fill conversion latency slots that retail leaves untouched;
 * retail keeps the sprite in v0 and uses a0 for the conversion temporary.
 * Canonical nested calls, standalone sprite results, float/int rounding
 * temporaries and three bank-preserving argument interleavings tied at the
 * draw sequences. Moving a nested lookup after the FP arguments evaluates the
 * coordinates before the lookup, grows to 1924 bytes and is worse. Allocator
 * dumps confirm the 0x8710 pseudo gets s0 locally before state gets s1 globally.
 * The older counterpart's notes also rule out the individual scheduling flags
 * and an inline draw helper. A new hypothesis for late constant setup and the
 * unused saved s2 is needed. Required declarations are included below.
 */
#include "common.h"

extern char *D_L10_001B13F0 __attribute__((sda));
extern int D_L10_001B3548 __attribute__((sda));
extern int D_L10_001B3544 __attribute__((sda));
extern int D_L10_001B14A8 __attribute__((sda));
extern int D_L10_001B14AC;
extern int D_L10_001B14B0 __attribute__((sda));
extern int D_L10_001B14B4;
extern int D_L10_001B14B8 __attribute__((sda));
extern int D_L10_001B14BC;
extern int D_L10_001B14C0 __attribute__((sda));
extern int D_L10_001B14C4;
extern int D_L10_001A904C;
extern int D_L10_001B2D80;
extern float D_L10_001B2D84;
extern int D_001A79FC;
extern int func_00336D50(int, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, void *);
typedef struct { u8 bytes[16]; } Packed16;
extern Packed16 D_L10_001B1520;
extern char D_L10_001B1530[];
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);

void func_L10_00424CD0(int first, int second, int third, int fourth)
{
    char text[0x80];
    char *state = *(char **)(D_L10_001B13F0 + 0x68);
    float scale;
    int time;

    if (D_L10_001B3548 == 0) {
        D_L10_001B3548 = 1;
        D_L10_001B3544 = D_001A79FC;
    }
    if (D_L10_001A904C == 0)
        return;
    if (first) {
        func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xBD), 0x60442D00, (float)D_L10_001B14A8,
                      (float)(int)((float)D_L10_001B14AC * D_L10_001B2D84 + 0.5f), -1.0f, 1.0f, 0.0f);
        func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xBE), 0x55F0C070, (float)D_L10_001B14A8,
                      (float)(int)((float)D_L10_001B14AC * D_L10_001B2D84 + 0.5f), -1.0f, 1.0f, 0.0f);
    }
    if (second && D_L10_001B3544 < D_001A79FC) {
        if (func_00282948(state + 0x4C) == 0) {
            time = *(int *)(state + 0x4C);
            if (time >= 0x123) {
                scale = func_00283CE0(300 - time) * 0.1f;
                if (scale > 1.0f)
                    scale = 1.0f;
                else if (scale < 0.0f)
                    scale = 0.0f;
                func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xBF), 0x60442D00, (float)D_L10_001B14B0,
                              (float)(int)((float)D_L10_001B14B4 * D_L10_001B2D84 + 0.5f), scale, scale, 0.0f);
                func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC0), 0x55F0C070, (float)D_L10_001B14B0,
                              (float)(int)((float)D_L10_001B14B4 * D_L10_001B2D84 + 0.5f), scale, scale, 0.0f);
            } else if (time < 10) {
                scale = func_00283CE0(time) * 0.1f;
                if (scale > 1.0f)
                    scale = 1.0f;
                else if (scale < 0.0f)
                    scale = 0.0f;
                func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xBF), 0x60442D00, (float)D_L10_001B14B0,
                              (float)(int)((float)D_L10_001B14B4 * D_L10_001B2D84 + 0.5f), scale, scale, 0.0f);
                func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC0), 0x55F0C070, (float)D_L10_001B14B0,
                              (float)(int)((float)D_L10_001B14B4 * D_L10_001B2D84 + 0.5f), scale, scale, 0.0f);
            } else {
                func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xBF), 0x60442D00, (float)D_L10_001B14B0,
                              (float)(int)((float)D_L10_001B14B4 * D_L10_001B2D84 + 0.5f), 1.0f, 1.0f, 0.0f);
                func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC0), 0x55F0C070, (float)D_L10_001B14B0,
                              (float)(int)((float)D_L10_001B14B4 * D_L10_001B2D84 + 0.5f), 1.0f, 1.0f, 0.0f);
                {
                    Packed16 colors = D_L10_001B1520;
                    {
                        int id = func_0028E588(0xEAA2, 3);
                        int x = D_L10_001B14B0 - 0x33;
                        float y = (float)(D_L10_001B14B4 - 13) * D_L10_001B2D84 + 0.5f;
                        if (D_L10_001B2D80 == 1)
                            y += 1.0f;
                        func_0028EA58(id, x, (int)y, 0x1C, 0x1C, &colors);
                    }
                    func_00115DA8(text, D_L10_001B1530, D_001A79FC);
                    func_0027F5B8(D_L10_001B14B0 + 5, (int)((float)(D_L10_001B14B4 + 2) * D_L10_001B2D84 + 0.5f),
                                  0x80808080ULL, (unsigned char *)text, 0x80);
                }
            }
        } else {
            D_L10_001B3544 = D_001A79FC;
            *(int *)(state + 0x4C) = 300;
        }
    }
    if (third) {
        func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC1), 0x60442D00, (float)D_L10_001B14B8,
                      (float)(int)((float)D_L10_001B14BC * D_L10_001B2D84 + 0.5f), 1.35f, 1.0f, 0.0f);
        func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC2), 0x55F0C070, (float)D_L10_001B14B8,
                      (float)(int)((float)D_L10_001B14BC * D_L10_001B2D84 + 0.5f), 1.35f, 1.0f, 0.0f);
    }
    if (fourth) {
        func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC1), 0x60442D00, (float)D_L10_001B14C0,
                      (float)(int)((float)D_L10_001B14C4 * D_L10_001B2D84 + 0.5f), 1.35f, 1.0f, 0.0f);
        func_00300A00(func_00336D50(D_L10_001A904C + 0x8710, 0xC2), 0x55F0C070, (float)D_L10_001B14C0,
                      (float)(int)((float)D_L10_001B14C4 * D_L10_001B2D84 + 0.5f), 1.35f, 1.0f, 0.0f);
    }
}
