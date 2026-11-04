/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 752/752 bytes, 0/1 placements; first difference 0xc.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* 2026-11-03 w02 source-contract review (USA v1.01 only).
 * Profile: -O2 -G8 -ffunction-sections.
 * Current check.py: 752/752 bytes, 0/1 places, first mismatch +0x0C.
 * Corrected sprintf (func_00115DA8) to its actual int return. Current faithful candidate reaches retail size, but prologue, serial-coordinate scheduling and the retained context-pointer lifetime differ.
 * Reopen: A real rounding/block and context-lifetime witness; no synthetic barriers or unused saves.
 * No linked match or cross-release qualification is claimed. Earlier notes follow.
 */
/* func_L11_004456A0 - 752 bytes, level 11 only (draws a title line, a box with one of three
   messages chosen by state +0x1E8, and a footer box).  opus-1 (Claude Opus 5.5), 30 October 2026.
   Best tools/check.py (USA v1.01, own -G8 unit, default -O2 -G8 -ffunction-sections):
   756/752 bytes, 0/1 places; 125 of retail's 188 words in a normalized common subsequence
   (relocations masked), against 114 for the orch/main draft and 77 for the earlier retained
   draft (which now compiles to 784 bytes).

   This is the level-11 twin of func_L02_003FF6E8 (same body with an extra 0x2F97 branch, see
   that record and MATCHING-BLOCKERS "A register saved and never used").  With `ctx = buf1`
   set just before the first box (an earlier set gives state $s2), the frame (0xF0), the saves
   (s0-s3, ra, f20-f22) and the register roles are retail's: ctx $s2, state $s3, the texts
   $s1, the colours / D_001395B8 base / buf2 $s0 (the format block's colour $s1), 0.5 in $f22.
   The three message blocks and the footer draw are retail's word for word apart from ctx.

   Still different:
   - ctx: retail never sets or reads $s2 (it saves it and rebuilds `addiu $a0,$sp,0x10` at
     each of the six draw calls); here ctx stays in $s2 (one `addiu $s2,$sp,0x10`, six
     `daddu $a0,$s2,$zero`): the extra word.  Compiler-side per the blocker entry; every
     ctx-free spelling (buf1 passed directly) gives 3 GPR saves and a 0xE0 frame.
   - box coordinates: one reused float `t` (per box) keeps the three
     `(int)((float)D * D_L11_001B3E04 + 0.5f)` chains sequential like retail, but sched1 still
     issues the other argument loads (D_1838/183C/181C/1840, the stack 3, the ctx move) inside
     the chains, where retail has them after the third chain; and t is a global pseudo (it
     dies three times) so local-alloc gives the scale $f0 and t $f1 (retail t $f0, scale $f1).
     Separate per-chain variables or one-expression arguments interleave the chains.
   - first block: retail has `daddu $s0,$a0` in the prologue, `swc1 $f20` in the first call's
     slot, `addiu $a0,0x2F45` before the text lookup with the state load in its slot, and the
     colour load `lw $s0,D_180C` after the y conversion; the func_0027F640 argument moves come
     in another order.
   Measured and not better: -g, -fno-schedule-insns (chains still grouped by sched2 and the
   first block's f20/f21/f22 roles swap), branch-free single `text` variable (orch/main).

   Declarations: as below (standalone -G8 unit; the gp-relative scalars need -G8). */
#include "include_asm.h"

typedef unsigned char u8;
typedef short s16;

extern void func_L11_00443940(char *, int);
extern int func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(long long, char *, float, float, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern int func_L11_0043E108(int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern int func_00115DA8(char *, char *, ...);

extern float D_L11_001B1808 __attribute__((sda));
extern int D_L11_001B180C __attribute__((sda));
extern int D_L11_001B1810 __attribute__((sda));
extern int D_L11_001B1814 __attribute__((sda));
extern int D_L11_001B1818 __attribute__((sda));
extern int D_L11_001B181C __attribute__((sda));
extern int D_L11_001B1820 __attribute__((sda));
extern int D_L11_001B1824 __attribute__((sda));
extern int D_L11_001B1828 __attribute__((sda));
extern int D_L11_001B182C __attribute__((sda));
extern int D_L11_001B1830 __attribute__((sda));
extern int D_L11_001B1834;
extern int D_L11_001B1838;
extern int D_L11_001B183C;
extern int D_L11_001B1840 __attribute__((sda));
extern float D_L11_001B3E04;
extern char D_L11_001B15A0[];
extern char D_L11_002A3AD0[];
extern u8 D_001395B8[0x100];

void func_L11_004456A0(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *ctx;
    char *state;
    char *text;
    char *msg;
    float t;
    float u;
    int r1;
    int r2;
    int r3;

    func_L11_00443940(a0, 0);
    state = *(char **)(a0 + 0x68);
    text = ((char *)func_00288FB8(0x2F45));
    func_0027F640(D_L11_001B180C, text, (float)D_L11_001B1810,
                  (float)(int)((float)D_L11_001B1814 * D_L11_001B3E04 + 0.5f), D_L11_001B1808, -1,
                  func_0027C878(1), D_L11_002A3AD0);
    ctx = buf1;
    t = (float)D_L11_001B1830;
    t = t * D_L11_001B3E04;
    t = t + 0.5f;
    r1 = (int)t;
    t = (float)D_L11_001B1834;
    t = t * D_L11_001B3E04;
    t = t + 0.5f;
    r2 = (int)t;
    t = (float)D_L11_001B1820;
    t = t * D_L11_001B3E04;
    t = t + 0.5f;
    r3 = (int)t;
    func_002802E0(ctx, r1, r2, D_L11_001B1838, D_L11_001B183C, D_L11_001B181C, r3,
                  D_L11_001B1840, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && D_001395B8[func_L11_0043E108(0)] < 2) {
        text = ((char *)func_00288FB8(0x2F96));
        func_00280270(ctx, D_L11_001B1818, text, func_001157AC(text));
    } else if (*(s16 *)(state + 0x1E8) == 1 && D_001395B8[func_L11_0043E108(1)] < 2) {
        text = ((char *)func_00288FB8(0x2F97));
        func_00280270(ctx, D_L11_001B1818, text, func_001157AC(text));
    } else {
        text = ((char *)func_00288FB8(0x2F62));
        msg = ((char *)func_00288FB8(0x2F5E));
        func_00115DA8(buf2, D_L11_001B15A0, text, *(int *)(state + 0x1E0), msg);
        func_00280270(ctx, D_L11_001B1818, buf2, func_001157AC(buf2));
    }
    text = ((char *)func_00288FB8(0x2F47));
    u = (float)D_L11_001B1830;
    u = u * D_L11_001B3E04;
    u = u + 0.5f;
    r1 = (int)u;
    u = (float)D_L11_001B1834;
    u = u * D_L11_001B3E04;
    u = u + 0.5f;
    r2 = (int)u;
    u = (float)D_L11_001B182C;
    u = u * D_L11_001B3E04;
    u = u + 0.5f;
    r3 = (int)u;
    func_002802E0(ctx, r1, r2, D_L11_001B1838, D_L11_001B183C, D_L11_001B1828, r3,
                  D_L11_001B1840, 3);
    func_00280190(ctx, D_L11_001B1824, text, func_001157AC(text));
}
