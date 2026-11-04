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
extern s32 func_001157AC(char *);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern void func_L05_00303000(s32, s32, s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
s32 func_L10_004239A0(void) {
    char buf[128];
    f32 center = func_00283CE0(D_001A7340[0]) * 0.5f;
    u8 *sprite;
    char *text;
    s32 x, y, count, index, sy;
    f32 scaled, fy;
    if (D_L10_001A904C[0] != 0) {
        sprite = func_00336D50(D_L10_001A904C[0] + 0x8710, 0x45);
        sy = (s32)(D_L10_001B2D84[0] * 200.0f + 0.5f);
        fy = sy;
        func_00300968(sprite, 0x60442D00, center, fy, 1.0f, 0.0f);
        sprite = func_00336D50(D_L10_001A904C[0] + 0x8710, 0x44);
        sy = (s32)(D_L10_001B2D84[0] * 200.0f + 0.5f);
        fy = sy;
        func_00300968(sprite, 0x55F0C070, center, fy, 1.0f, 0.0f);
        func_00115DA8(buf, func_00288FB8(0x2F72), D_L10_001B143C + 1);
        text = func_00288FB8(0x2F93);
        x = func_00283CF0(center);
        scaled = D_L10_001B2D84[0] * 46.0f + 0.5f;
        if (D_L10_001B2D80[0] == 1)
            y = (s32)(scaled + -2.0f);
        else
            y = (s32)scaled;
        func_0027FB40(x, y, 0x80F0F0F0, text, func_001157AC(text));
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
        y = (s32)(D_L10_001B2D84[0] * 210.0f + 0.5f);
        func_L05_00303000(117, y, 280, 400, 0x80F0F0F0, text, func_001157AC(text));
        scaled = D_L10_001B2D84[0] * 294.0f + 0.5f;
        if (D_L10_001B2D80[0] == 1) y = (s32)(scaled + 3.0f);
        else y = (s32)scaled;
        func_0027F5B8(117, y, 0x80F0F0F0, func_00288FB8(0x31CC), -1);
        scaled = D_L10_001B2D84[0] * 294.0f + 0.5f;
        if (D_L10_001B2D80[0] == 1) y = (s32)(scaled + 3.0f);
        else y = (s32)scaled;
        func_0027F5B8(274, y, 0x80F0F0F0, func_00288FB8(0x31CD), -1);
    }
    return 1;
}
