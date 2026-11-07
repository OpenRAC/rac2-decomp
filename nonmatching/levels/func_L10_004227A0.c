/* Round three, 7 November 2026 (USA v1.01): 3420/3420 bytes, 847/855 aligned, 8 rows left.
 * The C below replaces the earlier draft and scores the same in L05/L15 (their notes).
 * - MenuSpriteY (MenuY plus label_y's two dead handle tests, allowed by owner ruling) for the
 *   two 291 sprite rows: center loses priority (595 < 600), the $f22/$f23 swap is gone.
 * - func_00300968 declared as the majority of matched units have it,
 *   (void *, f32, f32, s32, f32, f32): x and y are expanded before the colour, so the
 *   `mov.s $f12` / `ori $a1` order in the 200 rows matches (EE ABI banks unchanged).
 * - Left: the four 101 rows (a0=x vs t0=len, 2 rows each). In sched1 the weight-0 moves go
 *   first; a0=x has weight 1 because x stays live to the 242 rows' label_y handle test.
 *   Retail's x dies at the 101 call (the 170 rows show that order). Tried this round as the 242
 *   handle: sprintf's result (fixes all 101 rows, but its pseudo spans the test blocks, so
 *   global-alloc gives it $3 after local-alloc puts label_y's mode load in $2: a dead
 *   `move $3,$2` stays, and sprintf's a0/a1 swap: 3432 bytes); the 101 row's result (moves x
 *   to $s1); MenuY with handle tests on every row (x, text or constant handle: 795-823/855); an
 *   inline title_line wrapper for the 101 row (no change).
 */
/* Round two, 7 November 2026 (USA v1.01, branch 30f91c91 with the real func_L05_00303000
 * contract). The C below is unchanged and also measured in L05/L15 (same 837/855 there).
 * 1. $f22/$f23 swap: global-alloc priority, center 5 refs/164 = 609 vs the shared 0.0f
 *    3 refs/50 = 600 (lreg/greg dumps). Retail needs center's range about 4 insns longer
 *    outside the 0.0f range, or the 0.0f range 1 shorter. No-op rewrites leave it at 609/600:
 *    own sprite locals, inline label_y in the call, 0.5f*x, split or merged early returns, store
 *    order, if/else colour, pulse order, master screen_coord, a sprite() wrapper (617), an
 *    image() wrapper (3408 bytes). What works (diagnostic, NOT in src, needs a ruling): the two
 *    291 rows with label_y's two dead handle tests added to MenuY, handle r:
 *      static __inline__ s32 MenuYH(void *handle, f32 y, f32 adjustment) {
 *          f32 scaled = y * D_L10_001B2D84 + 0.5f; s32 result; void *copy;
 *          if (D_L10_001B2D80 == 1) result = (s32)(scaled + adjustment);
 *          else result = (s32)scaled;
 *          if (handle != 0) scaled = y;
 *          copy = handle;
 *          if (copy != 0) scaled = adjustment;
 *          return result;
 *      }
 *    center falls to 595, the registers match, and the result is 845/855 with 12 rows left:
 *    two `mov.s $f12` / `ori $a1` order pairs in the 200 rows (present in the base draft too:
 *    a sched1 tie, not allocation) and the four 101 rows.
 *    A constant handle in row 2 also fixes the registers but loses that row's boundary; a
 *    D_L10_001A904C handle in row 1 fixes them but leaves a reload (3428 bytes).
 * 2. The 101 rows: x must die at the 101 call (sched1 weight: retail moves a0=x before
 *    t0=len, as in the 170 rows where x does die). The 242 handle keeps x alive. Tried as the
 *    242 handle: buf / 117 (tests fold, boundary lost, 3428), reward (row moves to $s1),
 *    the 131 row (its a1 order breaks), D_L10_001A904C / D_L10_001B143C (load stays),
 *    sprintf's result, named (written) or inline: fixes all four 101 rows but leaves a dead
 *    `move $3,$2` (label_y's copy, removed only at jump2) and swaps sprintf's a0/a1 (3432).
 *    Retail's 242 handle is probably sprintf's result, with no copy left.
 */
/* func_L10_004227A0: near miss, 3420/3420 bytes, 0 of 1 place (USA v1.01, 7 November 2026).
 *
 * Unit: its own src/levels/10_hrugis_cloud/L10_004227A0-g8.c, -O2 -G8 -ffunction-sections (no
 * cflags line). The MENU_ROW macro and its do-while barrier are gone: every unadjusted row goes
 * through the accepted label_y helper (handle: the sprite for the 200 rows, the text for the 131
 * rows, x for the 170 and 242 rows). MenuY (a real mode test with an adjustment) stays.
 * Size is exact; 20 of 208 differing rows are real (the rest relocations); aligned 837/855.
 * What closed the gap from 3260:
 * - Colour argument of func_L05_00303000 as u64 (retail's ori/dsll/ori; func_L05_00302CE8
 *   takes u64 color, u8 *text and returns int). A match would need the wrapper's definition in
 *   src/levels/shared/L05_003008C0.c changed to that interface too (check it still matches).
 * - Completion counts as master's L10_00423DC8-g8.c reads them: D_L10_001B1390[] sda plus the
 *   SDATA _gp view for [0]. [1..3] are CONST addresses, which simple_memory_operand rejects, so
 *   the unsplit lui/lw stays out of delay slots: retail's nop + lui/lw, with no volatile.
 * - Text rows' handle x (not buf): a constant handle folds the tests and loses the boundary.
 * - `if (D_L10_001A8F00) return 1; if (D_L10_001A904C) { ... } return 1;`: the label before
 *   `v0 = 1` keeps it out of the last call's sched2 block (fixes its a1/a3 order and the tail).
 * Left (both allocation/order, not shape):
 * - center in $f22 and 0.0f in $f23, retail the reverse (12 rows). global-alloc priority:
 *   center 5 refs/164 = 609, the shared 0.0f 3 refs/50 = 600. A constant handle in the second
 *   200 row gives retail's registers (0.0f 652) but loses that row's boundary.
 * - The four 101 rows: retail moves a0=x before t0=len; here t0 first, because x stays live to
 *   the 242 row's handle test (no REG_DEAD, sched1 weight). A reward, sprintf-result or
 *   previous-row handle fixes these rows but breaks the 242 rows (extra copy or register).
 * Ruled out today: -fno-sched-interblock (same), -fno-schedule-insns (681/855),
 * -mno-split-addresses (796/855), [3]/[] sda views of 1394 (gp or filled slot).
 */
/* Contract follow-up, 4 November 2026; retained, not linked.
 * The matched func_L05_00303000 definition in L05_003008C0.c is void
 * with seven signed32 EE arguments: x, y, width, height, packed color,
 * text-address word and length. All eight calls now keep that physical
 * interface; color is not widened and the text pointer is explicitly cast
 * to its real address word. The earlier s32/u64 declaration was false.
 * D_L10_001B1394/98/9C are ordinary words: there is no measured reload
 * witness supporting the inherited volatile diagnostic declarations.
 * Current -O2 -G8 -ffunction-sections check: 3260/3420 bytes, 0/1 USA.
 * This canonical name is absent from the current US2/PAL catalogues.
 * Real source/helper lifetimes and rounding/scheduling remain unresolved.
 * Earlier sizes and the inherited diagnostic choices below are historical
 * where superseded; no dummy controls, accesses or fields were introduced.
 */
/* Faithful-source review, 4 November 2026; retained, not linked.
 * 3312/3420 bytes, 0/1 USA placement.
 * Remove MENU_ROW's conditional scaled+1 assignment, which was overwritten without a read and existed only to leave a compiler block boundary. Keep the direct rounded row and the separate consumed display-mode coordinate helper. Actual HUD helper/control-flow evidence is needed before another scheduling experiment.
 * Measured in the assigned production unit with the profile recorded below.
 * Other-release checks were not rerun for this nonmatching source.
 * Earlier diagnostic measurements below are historical where superseded.
 */
/*
 * Claude Opus 5.5 (xhigh), task v1820, USA v1.01. Replaces the 3300-byte draft from v1754.
 * Game -O2 -G8 -ffunction-sections, in its own -g8.c unit (for example
 * src/levels/10_hrugis_cloud/L10_003170D0-menu-g8.c; no cflags line needed):
 * 3440/3420 bytes, 0/1 places. Relocation-masked sequence alignment: 802 of retail's 855
 * instructions (the v1754 draft scores 517 on the same script). No linked build was run.
 * No exact-bytes form was found with any wording, admissible or not.
 *
 * Main finding: the "block boundary with no instruction" in MenuRow is a vanished no-else test,
 * `row = (s32)scaled; if (D_L10_001B2D80 == 1) <body that flow1 deletes>`. The flow1, sched1 and
 * flow2 points were read in the gcse, sched and sched2 dumps; the cse points are inferred from bytes:
 * - The body has to be a set that cse cannot delete: `scaled` qualifies because it was already
 *   used by the conversion. Testing before the conversion loses the row: a `y` or unused-local
 *   body dies in cse, so jump removes the test before flow.
 * - The test is single-use and has no label in its body, so cse skips it and 200.0f, 0.5f, 1.0f,
 *   0.0f and 0x8710 stay shared. An `a && b` test gives the label two uses and loses the sharing.
 * - Flow1 deletes the body; sched1 and local-alloc still see the jump, the mode load and the 1.
 *   That alone gives retail's $v1 row, $f20-$f24, $s1, chain registers and the $s3 = 1 hoist.
 * - Flow2 then deletes the jump (tidy_fallthru_edge), merges the blocks and deletes the mode and
 *   1 loads, so this test can read a global and leave no word. This refines the rule in
 *   WORKER2.md, which covers tests that survive until jump2.
 *
 * What still differs, nearly all from one cause: retail keeps a block boundary at this test
 * through sched2, and this draft does not, because flow2 merged the blocks. So sched2 interleaves
 * the row with later arguments, which changes argument order and breaks tail merges such as case
 * 1's locked label into case 2's (20 extra bytes overall, net of 5 words).
 * Diagnostic, not admissible and not kept: the empty `do { } while (0);` after the test in
 * MENU_ROW adds loop notes, a sched2 barrier. It scores 833/855 at 3444 bytes. It has 7 more nops
 * than retail (48 against 41) at labels aligned by `.p2align 3`, for a net 6 surplus words; retail
 * has no such nops, so loop notes are probably not what retail had. `while (0) ;` and
 * `for (;0;) ;` score the same. What else differs: the order of 0.0f, %lo($a1) and $f12 in the
 * 200.0f rows, and a final row's argument order. With the test inside the do-while it scores 773.
 * Next: find what keeps that boundary through flow2 with no word left. It cannot be a jump
 * reading the mode load, since that load would then stay. flow.c merges unless the label has a
 * second predecessor or cannot be deleted.
 *
 * Unproven choices, for review:
 * - The body's `scaled + 1.0f` leaves no trace in retail: the test is measured, its body is a
 *   guess. A test whose body is dead may not be admissible; maintainers have not ruled on it.
 * - D_L10_001B1394/98/9C are volatile. Retail reads them with a lui/lw pair and leaves the branch
 *   slots empty, and volatile reproduces both. Plain, NOT_SDA, nosda and array forms fill the slot
 *   or split the load. Retail never rereads one on a path, so the guide's volatile test is not
 *   shown to be met. D_L10_001B1390 cannot be volatile: retail loads it in a delay slot.
 * - func_L05_00303000 returns s32 here. This gives retail's $v1 index and $v0 slti, because the
 *   call's value makes $v0 unavailable. Its epilogue leaves $v0 from its last call, which fits
 *   but does not prove a return value.
 * - MENU_ROW is a macro because an inline adds a copy of the row (`mfc1 $a1; daddu $s0, $a1`),
 *   7 extra words. Its local `y` gives retail's $f0 constant and $f1 chain.
 *
 * Ruled out (measured): -mno-split-addresses, -fno-schedule-insns2, -g,
 * -frac2-keep-block-order, -frac2-gcse-unsplit-edges, -frac2-no-null-pointer-checks, a -G0 unit;
 * an inline reward helper and ternary index forms (movn, not retail's movz).
 * All required declarations follow.
 */
#include "common.h"

extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern s32 func_00283D38(s32, s32, f32);
extern s32 func_00336D50(u8 *, s32);
extern void func_00300968(void *, f32, f32, s32, f32, f32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 func_0027FBD8(s32, s32, u64, char *, s32);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern s32 func_0027FAA8(s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
/* Retail builds the colour with the 64-bit ori/dsll/ori form, so the caller passes a u64, as
   func_L05_00302CE8 (which the wrapper forwards to) takes it; the wrapper's matched C still says int. */
extern s32 func_L05_00303000(s32, s32, s32, s32, u64, u8 *, s32);
extern s32 D_001A7340;
typedef struct { u8 pad[0x1A0]; s32 buttons; } MenuInput;
extern MenuInput D_00138180;
extern u8 D_001A7A0A;
extern s32 D_L10_001A8F00;
extern u8 *D_L10_001A904C;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80;
extern s32 D_L10_001B2048;
extern s32 D_L10_001B1454[] __attribute__((sda)), D_L10_001B1460[] __attribute__((sda)), D_L10_001B146C[] __attribute__((sda));
extern s32 D_L10_001B1F64 __attribute__((sda));
extern s32 D_L10_001B143C __attribute__((sda));
extern s32 D_L10_001B1390[] __attribute__((sda));
extern s32 D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
extern s32 D_L10_001B1448[] SDATA(D_L10_001B1448);

/* MenuY with label_y's two dead handle tests, for the two sprite rows (allowed by owner ruling,
   7 November 2026, as the dead-test helper). The tests do not change the result; they end blocks
   that allocation and both scheduling passes see. */
static __inline__ s32 MenuSpriteY(void *handle, f32 y, f32 adjustment) {
    f32 scaled = y * D_L10_001B2D84 + 0.5f;
    s32 result;
    void *copy;
    if (D_L10_001B2D80 == 1)
        result = (s32)(scaled + adjustment);
    else
        result = (s32)scaled;
    if (handle != 0)
        scaled = y;
    copy = handle;
    if (copy != 0)
        scaled = adjustment;
    return result;
}
static __inline__ s32 MenuY(f32 y, f32 adjustment) {
    f32 scaled = y * D_L10_001B2D84 + 0.5f;
    if (D_L10_001B2D80 == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

/* label_y: the accepted HUD label helper (src/levels/10_hrugis_cloud/L10_00421790-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L10_001B2D80;
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

s32 func_L10_004227A0(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 r, remainder, color, blink, x, headerX, reward;
    char *text;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_L10_001A8F00) return 1;
    if (D_L10_001A904C) {
    D_L10_001B1F64 = 0;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x45);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x44);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
    remainder = D_L10_001B2048 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = func_00283D38(0x80FFDE8D, 0x60442D00, pulse);
    color = (D_00138180.buttons & 0x2000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (D_00138180.buttons & 0x8000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    func_00115DA8(buf, func_00288FB8(0x2F72), D_L10_001B143C + 1);
    headerX = func_00283CF0(center);
    { s32 len;
    len = func_001157AC(buf);
    func_0027FBD8(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = func_00283CF0(center);
    switch (D_L10_001B143C) {
    case 0:
        text = func_00288FB8(0x2FE2);
        {
            s32 row = MenuY(101.0f, -2.0f);
            func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
        }
        text = func_00288FB8(0x2FE7);
        {
            s32 len;
            s32 row;
            row = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
            len = func_001157AC(text);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L10_001B1390_gp[0];
            if (index >= 3) index = 2;
            reward = D_L10_001B1448[index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
        {
            s32 len;
            s32 row;
            row = label_y((void *)x, 242.0f, D_L10_001B2D84, 0.5f, 1);
            len = func_001157AC(buf);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
        }
        }
        func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        break;
    case 1:
        if (D_L10_001B1390_gp[0]) {
            text = func_00288FB8(0x2FE3);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FE8);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L10_001B1390[1];
                if (index >= 3) index = 2;
                reward = D_L10_001B1454[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L10_001B1390_gp[0] && D_L10_001B1390[1]) {
            text = func_00288FB8(0x2FE5);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FE9);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L10_001B1390[2];
                if (index >= 3) index = 2;
                reward = D_L10_001B1460[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L10_001B1390_gp[0] && D_L10_001B1390[1] && D_L10_001B1390[2]) {
            text = func_00288FB8(0x2FE6);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FEB);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L10_001B1390[3];
                if (index >= 3) index = 2;
                reward = D_L10_001B146C[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    }
    func_0027F5B8(119, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F40), -1);
    func_0027F5B8(356, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F41), -1);
    func_0027F5B8(279, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F42), -1);
    }
    return 1;
}
