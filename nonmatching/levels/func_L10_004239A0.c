/* 6 November 2026: retained best, legal C. 1064/1064 bytes, 0/1, own -g8 unit with -O2 -G8 -ffunction-sections -fno-gcse (without -fno-gcse: 1048 bytes). 18 of 266 lines still differ with relocations masked (29 before, and that needed the rejected dead-store wrappers). This supersedes the do/while(0) reading below: the invisible boundary is the display-mode helper of func_0032F3D0 and func_L08_003DB518 (hud_coord, whose dead test goes at flow2), with half/one and half2/one2 locals, and y passed in the call (a separate y statement gives 1068 bytes, 103 lines). Left: row 1 mov.s f12/ori a1 order; the strlen result move, last in retail's 46 and 131 rows but early here (a0 last on 46, t1 on 131); 210 row f0/f1 swapped. No change (18 lines): y or x in the call on other rows, value*scale in screen_y or a separate 210 helper, len local, UL colour, z before the call, a float y local, real strlen declaration, int strlen, inline draw wrappers. Worse: hud_coord on the 131 row (23), value*scale in hud_coord (19). Next: find what orders the strlen move. func_L05_00420360 and func_L15_00430168 are the same body. */
/* Faithful-source review, 4 November 2026; retained, not linked.
 * 1064/1064 bytes, 0/1 USA placement, first mismatch +0xC.
 * Remove all three do/while(0) wrappers and their dead conditional float assignments. Keep the real display-mode adjustments that affect a consumed coordinate. FP save/allocation, rounding and argument scheduling remain open.
 * Measured in the assigned production unit with the profile recorded below.
 * Other-release checks were not rerun for this nonmatching source.
 * Earlier diagnostic measurements below are historical where superseded.
 */
/* Opus-2 tier (v0777); USA v1.01. Needs a -G8 unit: measured as an appended function of
   src/levels/10_hrugis_cloud/L10_003170D0-g8.c (default -O2 -G8 -ffunction-sections, no
   .rodata, no same-file callee). Declarations below are the ones needed.
   Best check: 1064/1064 bytes, 0 of 1 places; 29 of 266 lines differ once relocations are
   masked (the opus-1 draft gives 91 with the same count). Prologue, frame, the FPR roles
   center f20, 0.5 f21, 200 f24 (1.0/0.0 are swapped, see below), every GPR role (s0 = the
   early 1 and later y, s1 = 0x8710 and later text, s2 = x and the EBB3 1) and the sprite
   rows' instruction order now match.

   What retail has, and what reproduces it here (ARTIFICIAL, not landable as written):
   - Between each sprite row's rounded y and its func_00300968 call, and between the 210-row
     rounding and its func_001157AC call, retail has (a) a basic-block boundary that exists
     when flow first runs (it makes 200.0, 1.0, 0.0, 0x8710 and the compare's 1 global, so
     global-alloc orders them after center and 0.5 as retail does; local-alloc would take
     f20/f21 first) and (b) a scheduling barrier in sched1 and sched2 (the draw's argument
     set-up is not interleaved with the rounding chain). No instruction remains of either.
   - `if (D_L10_001B2D80[0] == 1) do { <dead float store> } while (0);` gives exactly that:
     the SFmode store is not if-converted by jump (an SImode one is), survives cse because
     `scaled` has other uses, and is deleted by flow as dead after the CFG is built; flow2
     tidies the jump (the D80 load then dies) but the loop notes stay as barriers; cse2
     links the later real `== 1` compares to this compare's 1, which is retail's early
     `addiu $s0,$zero,1` after the first func_00336D50 and `addiu $s2,$zero,1` at the
     210-row. The int y must be used in the then-block (`scaled = sy - 2`) so it is a
     global pseudo and lands in $v1 as retail's; the float conversion must come before the
     if (row 2's argument order then matches retail exactly).
     The same invisible boundary after a D_001B23A4 scale-and-round exists in the boot
     (func_002900B8 sprite rows, func_0033A520, func_0033C028), so the original probably
     has a shared macro/helper there (a language-conditional adjustment with no effect for
     these elements); finding it is the way to a landable match.
   Still different: 1.0/0.0 land in f23/f22 (global-alloc tie: 1.0's live range is one
   insn longer after sched1); row 1's `ori $a1` vs `mov.s $f14` order; after each
   func_001157AC (46-, 131- and 210-row) retail moves the length last (delay slot) and the
   other arguments first (a3,a1,a0,a2 / a1,a0,a2,a3,t1,t0), here the length move is taken
   first (class-3 preference after the call); in the 210-row and the first 294-row retail
   allocates the 210/294 constant f0 and the D84 chain f1 (elsewhere the reverse). */
#include "common.h"
extern s32 D_001A7340[] __attribute__((sda));
extern u8 *D_L10_001A904C[] __attribute__((sda));
extern f32 D_L10_001B2D84[] __attribute__((sda));
extern s32 D_L10_001B2D80[] __attribute__((sda));
extern s32 D_L10_001B355C[] __attribute__((sda));
extern u8 D_001A7A0A[] __attribute__((sda));
extern s32 D_L10_001B143C __attribute__((sda));
extern s32 D_L10_001B1390[] SDATA(D_L10_001B1390);
extern s32 D_L10_001B1448[][3] SDATA(D_L10_001B1448);
extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern char *func_00288FB8(s32);
extern u8 *func_00336D50(u8 *, s32);
extern void func_00300968(u8 *, u32, f32, f32, f32, f32);
extern s32 func_00115DA8(char *, char *, ...);
extern u32 func_001157AC(char *);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern void func_L05_00303000(s32, s32, s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real (as func_L11_004456A0). */
static __inline__ s32 hud_coord(f32 value, f32 scale, f32 half, s32 active)
{
    f32 scaled = scale * value + half;
    s32 result = (s32)scaled;

    if (result != 0 && D_L10_001B2D80[0] == active)
        scaled = 1.0f;
    return result;
}

/* A screen y scaled for the display and rounded, moved by adjust in display mode 1. */
static __inline__ s32 screen_y(f32 value, f32 scale, f32 half, s32 active, f32 adjust)
{
    f32 scaled = scale * value + half;

    if (D_L10_001B2D80[0] == active)
        return (s32)(scaled + adjust);
    return (s32)scaled;
}

s32 func_L10_004239A0(void) {
    char buf[128];
    f32 half = 0.5f;
    f32 center = func_00283CE0(D_001A7340[0]) * half;
    u8 *sprite;
    char *text;
    s32 x, y, count, index, one, one2, entry;
    f32 w, sc, z, half2;
    if (D_L10_001A904C[0] != 0) {
        entry = 0x8710;
        w = 200.0f;
        one = 1;
        sprite = func_00336D50(D_L10_001A904C[0] + entry, 0x45);
        y = hud_coord(w, D_L10_001B2D84[0], half, one);
        sc = 1.0f;
        func_00300968(sprite, 0x60442D00, center, (f32)y, sc, z = 0.0f);
        sprite = func_00336D50(D_L10_001A904C[0] + entry, 0x44);
        y = hud_coord(w, D_L10_001B2D84[0], half, one);
        func_00300968(sprite, 0x55F0C070, center, (f32)y, sc, z);
        func_00115DA8(buf, func_00288FB8(0x2F72), D_L10_001B143C + 1);
        text = func_00288FB8(0x2F93);
        x = func_00283CF0(center);
        func_0027FB40(x, screen_y(46.0f, D_L10_001B2D84[0], half, one, -2.0f), 0x80F0F0F0, text, func_001157AC(text));
        text = func_00288FB8(0x31CB);
        y = (s32)(D_L10_001B2D84[0] * 131.0f + 0.5f);
        func_L05_00303000(117, y, 280, 400, 0x80F0F0F0, text, func_001157AC(text));
        index = D_L10_001B1390[D_L10_001B355C[0]] - 1;
        if (index >= 3) index = 2;
        count = D_L10_001B1448[D_L10_001B355C[0]][index];
        if (D_001A7A0A[0] != 0) count *= 10;
        text = buf;
        if (count == 0) func_00115DA8(buf, func_00288FB8(0x11FB));
        else func_00115DA8(buf, func_00288FB8(0x2FC6), count);
        half2 = 0.5f;
        one2 = 1;
        func_L05_00303000(117, hud_coord(210.0f, D_L10_001B2D84[0], half2, one2), 280, 400, 0x80F0F0F0, text, func_001157AC(text));
        y = screen_y(294.0f, D_L10_001B2D84[0], half2, one2, 3.0f);
        func_0027F5B8(117, y, 0x80F0F0F0, func_00288FB8(0x31CC), -1);
        y = screen_y(294.0f, D_L10_001B2D84[0], 0.5f, 1, 3.0f);
        func_0027F5B8(274, y, 0x80F0F0F0, func_00288FB8(0x31CD), -1);
    }
    return 1;
}
