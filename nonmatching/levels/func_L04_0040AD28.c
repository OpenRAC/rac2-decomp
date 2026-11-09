/* 9 November 2026 (o140, dump-driven, 17 cc1 compiles): body unchanged, 32 masked words. time/60: the 60 pseudo 498 (10 refs/110 insns, 0.273) is allocno 216, time 98 (13/31, 1.258) allocno 5 and conflicts with hard s0, so it takes s1; retail needs time below 0.273 (live > 143 insns at 13 refs) or a higher-priority s1 holder over its life. time reusing the dead `one`: pseudo 18 refs/250 insns = 0.288, still just above 498, and `one` then occupies s1 over the 283 rows (input moves to s3): 37; reusing count 57 (count+time s1), reward 40; single-set time via a times select 40. 0x96 row: `scale = D_L04_001B2D44;` reused before label_y 33 (scale gets $f15, lwc1 still issues with the str copy), float py for (150-shift) 35, label reused for that row 36. Name row: str via reused input 45, via icon breaks size. */
/* 9 November 2026 (o139, dump-driven): body below updated, 3388/3388 bytes, 32 relocation-masked word diffs (was 40), first diff +0x4f0. 0xD2/0xBE rows fixed: retail gives the 210-shift/190-shift li $v1 (li before the str copy in sched1), which needs the str pseudo to lose sched1's birthing boost (REG_N_SETS > 1): one function-level-in-block `char *label` now carries 0x2f7c/0x2f7b, 0x2f9b/0x2f9c and both 0x2fc5 strings (reused dead local), and the else-arm 0x2fc5 row passes label straight to label_y/strlen/draw (via TEXT's str_ copy cse kept a set-once pseudo 417). Measured, still open: 0x96 row: sched2 issue loop (haifa-sched.c 6952) puts a newly ready insn into the slot of the one just issued, so li (anti-dep on the copy) can never pair with the copy; retail pairs copy alone then li+lwc1, so in retail the lwc1 was not ready/issuable at the copy's cycle (no block boundary: 0x40B33C is no branch target); label for that row 36. 0x2F79/0x2F99 order: the arm whose source order is second-then-first emits second first; both arms first-then-second flips the result reg (movz, a0 = first): 35; mirrored 32 (moves the diff to arm 1); lang after the pair breaks size, between 35. Name row: hud_coord1 on ROW(279)/ROW(181)/name Y 37; race pointer / name local 32 (no change); MACRO_ADDR table breaks size. time/60: minutes local breaks size. */
/* 9 November 2026 (o136, dump-driven): body below updated, 3388/3388 bytes, 40 relocation-masked word diffs (was 44), first diff +0x4f0. (1) 0x2f72 draw t0/a0: sched2 key 5; the next ROW's fix_trunc scratch got $a0 (v0/v1 held hud_coord's mode and literal 1), giving the a0 move an extra dependent. ROW(119) now uses hud_coord1 (hud_coord with label_y's `active` parameter) with the set-once `one`, so the 1 is not in v1 and the scratch takes v1: exact. (2) else-arm TEXT(center,shift+210,buffer) a1/t0: label_y(buffer) folded its tests, so the fix and the strlen call shared a sched2 block and a1 (latency 3 after the fix) issued after t0; label_y((void *)center, ...) keeps the block boundary: exact. Measured, still open: name-row base s2/s7: gcse inserts high(D_L04_002C63C0) as an edge insertion at the end of the hud_coord block ("PRE/HOIST: end of bb 63", not a copy after insn 857), so the copy kills the hi (weight 0) and both birthing insns tie, copy wins over the lo_sum; retail needs the copy placed after the hi. 0x96/0xD2/0xBE li order: sched1 has retail's order, sched2 issues the lwc1 with the str copy and the li (anti-dep on v0) a cycle later; y-local, scale-local, float-y, two-step str, hud_coord1/one handles on those rows: no gain. time/60: not retried. */
/* 9 November 2026 (o134): body below updated, now 3388/3388 bytes, check.py 0 of 2 (first diff +0x3f0), 44 relocation-masked word diffs (was 3384, 63 aligned rows). Steps: (1) icon 1.0s: cse1 (not cse2) shared icon 1's 1.0 pseudo; icon 1 now passes a local w = 1.0f set after the scale join, and icon 2 reuses w for its y (the label_y result), which kills the 1.0 equivalence, and passes a fresh v = 1.0f set before its scale test: both icons exact. (2) D_001A7368 declared MACRO_ADDR (one la insn, not eligible for the b slot), so reorg fills arm 1's b slot from the target sll as retail: time lookup exact. (3) 0x2f72 CENTER row: label_y3((void *)n_, ...) (handle test first) drops the dead daddu a0,v0 and keeps the sprintf arg order. Left: t0/a0 order at the 0x2f72 draw (len/center; j1-j3 forms tie); name row base s2/s7: sched1 ranks the gcse hi copy r1007=r268 (insn 2558, end of block, REG_DEAD) above the lo_sum 862 at t=2 (idx-local / pointer-sum forms tie); the 0x2F79/0x96 and 0x2fc5 TEXT rows' li-before-copy order (label_y3/y4/hud_coord/y-local tie); time/60 s1/s2 swap. */
/* 9 November 2026 (o132, HUD-panel recipe of L02_003FDDE8/L11_00443940): body below updated. func_00300A00 declared (void *, float x, unsigned int colour, float y, ...) (bank-preserving, owner-allowed) and a set-once `int one = 1;` (set right after the func_00283D38 colour, before `input`) as label_y active for the two 283 sprites: the label_y dead mode test no longer holds $v1, so the 283 rows' mfc1 is $v1 and 0x8710 is $s4 as retail. Masked aligned harness (o132, relocation-masked difflib): 71 -> 63 rows, still 3384/3388. Measured, no gain: `one`/k2 on TEXT/CENTER/0x2f72 rows (27 combos), set-once 1.0f locals (w/w2, reused dead angle/tangent) for the 200 icons at every position (retail: icon 1 direct $f14, icon 2 fresh $f20 before its scale test; cse2 re-shares icon 1's 1.0 pseudo in every form, best 62 with a different icon-1 order), do-while(0) w (3388 bytes only via an alignment nop), a set-once `sixty` for the time divisions (67-75, loses the dead li 60s), -fno-gcse 128, -fno-sched-interblock and the -frac2-* switches 70 (prototype only). */
/* 9 November 2026 (Sonnet round o88, dump-driven, 6 compiles): time/60 swap decided by global-alloc order: .lreg time = pseudo 98 (13 refs, 31 insns, 2 sets, crosses 2 calls) priority 3*13/31 = 1.258, the 60 = pseudo 503 (10 refs, 110 insns) 3*10/110 = 0.273; time is 2nd of 86 allocnos (after 97 in s0 by preference, time has a hard conflict on s0), so it takes s1 and 60 gets s2. Retail needs 60 allocated first or s1 blocked for time: a 4.6x priority flip, or an earlier allocno in s1 that conflicts with time but not with 60. Tried: time reusing dead `count` (aligned 114) or `reward` (97), against base 89 (o88 aligned count, relocations masked), `&table[idx]` per arm then `*tp` (93), per-arm idx then one load (97), per-arm byte offset (97): time stays s1 in all. Retail's per-arm sll is the last insn before arm 1's b (backward slot fill), so jump2 merged only addu+lw there. Best stays the C below. */
/* 9 November 2026 (Sonnet s50, lesson 53): no gain (base 525 masked). Tried `one` int for the 7 label_y active args (all / icon sites only / 200-only / 283-only; set at top, after AB40, before x) 525-556, `half` local per icon row 525-577, float `f1 = 1.0f` for the icon draws' 1.0f args (top 555, before second icon 523 = noise, same diff shape). */
/* 9 November 2026 (label_y2 sweep (owner ruling 2026-11-09, Sonnet s46): all 11 label_y sites (macros count once), singles in both one-test forms and all pairs/all-at-once: base 52 aligned rows (3384/3388) stays best, singles 52-61, no gain. */
/* 8 November 2026 (Sonnet round o25, lesson 49 audit): unchanged body, 3384/3388 bytes, 55 masked aligned differences (cc1 harness). Every local checked against retail: m $s6, p $s7, center $s5, input $s1, tint $s0, count $s2, shift $s6, x $s4, reward $s0 already hold one register as in retail; only time/60 are swapped ($s1/$s2, allocation order). Measured, no gain: a `RaceChallenge *races` local for the name row and flags tests at 5 placements (cse folds the constant address back, 55-73); CENTER handle = center/m/p/icon/input/count/buffer/D_L04_001B0904 (55-74; the global leaves an lw instead of the daddu); a minutes local (73, 3360); per-arm or ternary time lookups (57-61); y via hud_coord on the 0x2fc5 rows (63); all 5040 orders of the int declarations (no change); (float)1 / (float)0 / label_y in the call for the icons (55-76); TEXT/ROW with label_y or strlen inside the call (55); a cosine/tangent local in the m[0x20] block (55-73). One 1500 s permuter run: only dishonest outputs (time=1 / reward=1 reused as constants). */
/* 8 November 2026 (Sonnet round, lesson 48 sweep): scripted moves of every block-local statement by 1..6 (197 singles + 63 pairs), top-level items by 1..6 (370), and the TEXT/ROW/CENTER/name-row macros expanded to single statements by 1..4 (316): best is the base, 3384/3388, 61 aligned differences; no move or pair reduces it. */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_L04_0040A1D0 is declared int but src/levels/shared/L04_00402D90.c returns unsigned int: corrected, 3376/3388 bytes and 796 masked rows unchanged. */
/* 8 November 2026, Sonnet round (o1, ~75 cc1 compiles + one 1500 s permuter run), USA v1.01: one
 * change, the colour from func_00283D38 now lives in the existing `count` local (no separate colour
 * variable): input/colour regs ($s1/$s2) and count's $s2 now match retail; aligned harness 774 -> 792
 * exact of 847, 3384/3388 bytes. Reusing `time` instead gives 779, `reward` 773, `x` 756.
 * Measured, no gain: per-arm idx local for the time lookup gives retail's sll per arm and 3388 bytes
 * but swaps the compare registers (781); plain or label_y rounding on the name row (789/790);
 * CENTER(60) with hud_coord/center/fmt handles drops the dead daddu but swaps a0/a1 (790, 3380);
 * y local or inline text_row for the 0x2fc5 rows (776). The 0x2fc5 rows' str copy is glued to the
 * call (SCHED_GROUP); retail computes 210-shift in $v1 first, so retail has an extra value pseudo.
 * Name row: sched1 puts gcse's hi copy (s7) before the lo_sum, so base ties to hi's $s0. */
/* 8 November 2026, HUD-recipe rewrite (Claude Opus 5.5), USA v1.01, re-measured on master's
 * compiler: the 7 November body was 280 masked differences at 3360/3388 bytes; the body
 * below is 84 at 3384/3388 (same cc1 diff harness, relocations masked). Steps that paid:
 * - hud_coord (dead-test helper, owner ruling 8 November 2026) on every ROW and the name row:
 *   280 -> 211; label_y(str_) on every TEXT row: -> 150.
 * - time / 60 % 60 written in each sprintf call and the < 10 test (no minutes local): retail's
 *   three dead li 60 come back, 3356 -> 3380 bytes; per-arm times pointer: -> 126 / 90.
 * - per-draw string locals (label in each flags arm, fmt, str in both reward branches): -> 92.
 * - CENTER's handle: buffer is a constant address, so label_y(buffer) folds its tests and
 *   loses the block boundary (li.s 286.0 hoisted above the 0x2f72 call). Using sprintf's
 *   return as the handle puts 286.0 after the mfc1 as retail: -> 84 (it leaves one dead
 *   daddu $a0,$v0; a global handle gives 3388 bytes but an extra lw).
 * - Title select: lang loaded in both arms, then {first; second} / {second; first} order
 *   gives retail's beqz delay-slot lw and $a0/$v1; one 2-insn order difference left.
 * Still open: the first icon's 1.0 (retail: direct $f14, new 1.0 in $f20 at the second icon;
 * here one $f20 pseudo for both, width/rot locals no help); the 283 sprites' mfc1 $a1 vs $v1
 * and input/colour $s1/$s2 swap; table base $s2 / flags pointer $s3 / count $s2 in retail vs
 * $s0/$s0/$s3 here (cascades into the name row, count, reward); time vs 60 ($s2/$s1 swapped);
 * the time lookup's sll is cross-jumped into the join (retail keeps one sll per arm).
 * Profile: own unit src/levels/shared/L04_0040AD28-g8.c, -O2 -G8 -ffunction-sections -g. */
/* 7 November 2026, label_y sweep: the two icon ys use label_y(icon, 200.0f, ...) and CENTER uses label_y(str_, ...): 319 -> 281 differences, 3360/3388 bytes (TEXT and ROW with label_y: no gain). That body (since replaced by the 8 November one above) was the retained C with that change (label_y is
 * the accepted HUD label idiom, definition as in src/levels/15_gorn/L15_00431590-g8.c). Counts are
 * masked aligned instruction differences from a cc1 -S diff harness, not check.py rows. */
/* opus-1 (Claude Opus 5.5, xhigh) retained attempt, 31 October 2026, USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections -g, in a separate -g8.c unit.
 * check.py: 3356/3388 bytes, 0 of 2 places (Barlow and Joba). No linked build.
 * Kept over the sol-high draft (3368/3388) because more of it is right: with
 * relocations masked, 616 of 847 retail instructions align in order against
 * 547, and the code through 0x40AE00 is exact.
 *
 * Recovered here: per-draw scoped text locals (they keep the opening register
 * map), an inline helper so the coordinate constant loads before the scale, a
 * plain absolute scalar D_001A79F0 next to the $gp alias D_001A79F0_1, the format
 * pointer loaded before the localization call, column locals before the time
 * text, and a two-arm time lookup.
 *
 * What still differs: retail behaves as if a basic block ends right after every
 * coordinate's (int) conversion, yet no branch remains. Evidence: sprite Y uses
 * mfc1 $v1 with the D_001A7B90 load only after it; li.s 286.0 sits just after the
 * row's mfc1; the table high half first appears in the fourth ROW; shift's 5 and
 * the flags pointer appear at the 110 row. YS() marks the sprite coordinates.
 * Without that boundary those values hoist to the block start, and the table
 * lifetimes then rename most saved registers from 0x40B0C8 to the end.
 *
 * Measured, none landable:
 * - Single arm on the four sprite Ys, placeholder test and dead store:
 *     float y = v * S + 0.5f; int r = (int)y; if (center) y = 0.0f; return r;
 *   638 of 847 align. It restores the $f24/$f22/$s1 constants, $v1/$v0 and the
 *   empty delay slot, because cse skips the arm. But flow deletes the arm, so the
 *   test is gone by sched2 (the .sched dump has li.s $f15 in place, the sched2
 *   timeline has merged the block and fills a load stall with it).
 * - Two arms: if (center != 0) return (int)y + 0; return (int)y;
 *   Retail's order of conversion, D_001A7B90 load, float and li.s in the first
 *   sprite, and the value is written straight to its target, because the arms
 *   merge only after sched2. But the join label ends the cse table and every
 *   constant reloads: 3508 bytes with the helper on all coordinates.
 * - do { } while (0) forms (forbidden): 3360 and 3452 bytes, not exact either.
 * - A volatile asm conversion (forbidden): worse, it fills the delay slot retail
 *   leaves empty, so the boundary is a real branch and not a barrier.
 * - Testing center at the text rows moves it to $s3 (retail $s5): it is not the
 *   tested value. -frac2-keep-block-order and -frac2-gcse-unsplit-edges: no help.
 * Needed next: a real single-arm test on an already-live value whose arm survives
 * until after sched2 and then vanishes. No such wording was found.
 *
 * Also open: the first sprite loads 1.0 directly into $f14 while its 0.0 is a
 * pseudo shared with the second sprite ($f23), and retail's second sprite starts a
 * new 1.0 in $f20. Title selection is a tie: retail has movn $a0(second), $v1(first)
 * with the D_001A79F0_1 load in the branch delay slot; first == 11 / second != 11
 * overwrites and both ternaries give movz with the registers swapped. Data bindings
 * remain unqualified: no equal-size relocation check or linked build was reached.
 */
#include "common.h"
extern int D_001A7340, D_001A7B90;
extern int D_001A79F0;
extern int D_001A79F0_1 __attribute__((sda));
extern unsigned char D_00138180[];
extern unsigned char D_001A7A0A;
extern int D_L04_001B0904 __attribute__((sda));
extern unsigned char *D_L04_001B0914 __attribute__((sda));
extern unsigned char *D_L04_001A904C;
extern float D_L04_001B2D44;
extern int D_L04_001B2008;
extern float D_L04_001BDB80[];
extern int D_001A7368[] MACRO_ADDR;
extern int D_001A737C[];
typedef struct { int name, flags, rewards[3]; unsigned char reserved[44]; } RaceChallenge;
extern RaceChallenge D_L04_002C63C0[];
extern char D_L04_001B0940[], D_L04_001B0950[], D_L04_001B0958[], D_L04_001B0968[];
extern float func_00283198(float), func_00283180(float);
extern void func_0027AB40(void);
extern void *func_00336D50(void *, int);
extern void func_00300A00(void *, float, unsigned int, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_001157AC(const char *);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern int func_0027FBD8(int, int, unsigned long, char *, int);
extern void func_0027F5B8(int, int, unsigned long, char *, int);
extern int func_L04_0040A1D0(int);
extern void func_002FC560(int, unsigned long);
extern int D_L04_001B2D40;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
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

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}
static __inline__ int label_y4(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result;
    void *copy;
    if (mode == active) value = scale;
    result = (int)scaled;
    if (handle != 0) value = scale;
    copy = handle;
    if (copy != 0) value = half;
    return result;
}
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord1(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;
    if (mode == active) scaled = scale;
    if (result != 0) scaled = scale;
    copy = result;
    if (copy != 0) scaled = half;
    return result;
}
#define Y(v) hud_coord((float)(v), D_L04_001B2D44, 0.5f)
#define YS(v) Y(v)
#define TEXT(x,y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define CENTER(y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FBD8(center,row_,0x80f0f0f0UL,str_,len_); }
#define ROW(x,id) { int row_ = Y(286); char *str_ = func_00288FB8(id); func_0027F5B8(x,row_,0x80f0f0f0UL,str_,-1); }
int func_L04_0040AD28(void)
{
    char buffer[128];
    unsigned char *m = D_L04_001B0914;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    int center = (int)((float)D_001A7340 * 0.5f);
    float angle = 0.56217057f, tangent;
    unsigned int tint;
    unsigned char *input;
    int count, shift, reward, time, minutes, x, row;
    void *icon;
    float scale, centerf, py;
    int one;
    float w, v;
    tangent = func_00283198(angle);
    tangent /= func_00283180(angle);
    centerf = (float)center;
    D_L04_001BDB80[44] = tangent;
    func_0027AB40();
    icon = func_00336D50(D_L04_001A904C + 0x8710,0x45);
    py = (float)label_y(icon, 200.0f, D_L04_001B2D44, 0.5f, 1);
    scale = 0.92f;
    if (D_001A7B90) scale = 0.9f;
    w = 1.0f;
    func_00300A00(icon,centerf,0x60442d00,py,w,scale,(float)0);
    icon = func_00336D50(D_L04_001A904C + 0x8710,0x44);
    w = (float)label_y(icon, 200.0f, D_L04_001B2D44, 0.5f, 1);
    v = 1.0f;
    scale = 0.92f;
    if (D_001A7B90) scale = 0.9f;
    func_00300A00(icon,centerf,0x55f0c070,w,v,scale,0.0f);
    x = D_L04_001B2008 % 50;
    count = func_00283D38(0x80ffde8d,0x60442d00, x >= 25 ? 1.0f-(float)(x-25)*0.04f : (float)x*0.04f);
    one = 1;
    input = D_00138180;
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x2000)) tint = count;
    icon = func_00336D50(D_L04_001A904C+0x8710,0x4a);
    func_00300A00(icon,259.0f,tint,(float)label_y(icon, 283.0f, D_L04_001B2D44, 0.5f, one),1.0f,1.0f,0.0f);
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x8000)) tint = count;
    icon = func_00336D50(D_L04_001A904C+0x8710,0x4b);
    func_00300A00(icon,251.0f,tint,(float)label_y(icon, 283.0f, D_L04_001B2D44, 0.5f, one),1.0f,1.0f,0.0f);
    if (m[0x20] != 3) {
        float projection_angle = *(float *)(p+0x28c)*0.008726647f;
        float sine = func_00283198(projection_angle);
        D_L04_001BDB80[44] = sine / func_00283180(projection_angle);
        func_0027AB40();
    }
    { int n_ = func_00115DA8(buffer,func_00288FB8(0x2f72),D_L04_001B0904+1); int row_ = label_y3((void *)n_, 60.0f, D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FBD8(center,row_,0x80f0f0f0UL,buffer,len_); }
    { int row_ = hud_coord1(286.0f, D_L04_001B2D44, 0.5f, one); char *str_ = func_00288FB8(0x2f40); func_0027F5B8(119,row_,0x80f0f0f0UL,str_,-1); }
    ROW(356,0x2f41);
    ROW(181,0x2f3f);
    ROW(279,0x2f42);
    { char *str_ = func_00288FB8(D_L04_002C63C0[D_L04_001B0904].name); int row_ = Y(110); int len_ = func_001157AC(str_); func_0027FAA8(center,row_,0x80f0f0f0UL,str_,len_); }
    shift = D_001A79F0 == 11 ? 10 : 5;
    count = func_L04_0040A1D0(D_L04_001B0904);
    if ((D_L04_002C63C0[D_L04_001B0904].flags & 0x10000000) ||
        (D_L04_001B0904 > 0 && func_L04_0040A1D0(D_L04_001B0904-1)>0)) {
        int first, second, lang;
        if (D_L04_002C63C0[D_L04_001B0904].flags & 4) { lang = D_001A79F0_1; first=0x2f7a; second=0x2f9a; }
        else { lang = D_001A79F0_1; second=0x2f99; first=0x2f79; }
        if (lang != 11) second = first;
        TEXT(center,150-shift,func_00288FB8(second));
        { char *label; if (D_L04_002C63C0[D_L04_001B0904].flags&1) label=func_00288FB8(0x2f7c);
        else label=func_00288FB8(0x2f7b);
        TEXT(center,170-shift,label);
        if (D_001A79F0==11) {
            if (D_L04_002C63C0[D_L04_001B0904].flags&16) label=func_00288FB8(0x2f9b);
            else label=func_00288FB8(0x2f9c);
            TEXT(center,190-shift,label);
            if(D_L04_002C63C0[D_L04_001B0904].flags&2) { label=func_00288FB8(0x2fc5); TEXT(center,210-shift,label) }
        } else if(D_L04_002C63C0[D_L04_001B0904].flags&2) { label=func_00288FB8(0x2fc5); { int row_ = label_y(label, (float)(190-shift), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(label); func_0027FAA8(center,row_,0x80f0f0f0UL,label,len_); } } }
        if(count>=3) count=2;
        if(D_L04_002C63C0[D_L04_001B0904].rewards[count]) {
            char *fmt = D_L04_001B0940;
            char *str = func_00288FB8(0x2f7d);
            { unsigned char boost = D_001A7A0A;
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(boost) reward*=10; }
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2f5e));
        } else { char *fmt = D_L04_001B0950; func_00115DA8(buffer,fmt,func_00288FB8(0x2f7d)); }
        TEXT(center,shift+210,buffer);
        { int *times; if (D_001A79F0==4) { times = D_001A7368; time = times[D_L04_001B0904]; } else { times = D_001A737C; time = times[D_L04_001B0904]; } }
        x = 0;
        if(time) {
            x = 110;
            if (time / 60 % 60 < 10) func_00115DA8(buffer,D_L04_001B0958,func_00288FB8(0x31c8),time/3600%60,time/60%60,time/6%10);
            else func_00115DA8(buffer,D_L04_001B0968,func_00288FB8(0x31c8),time/3600%60,time/60%60,time/6%10);
            { int col = center+46; TEXT(col,shift+230,buffer); }
        }
            { int col = center-x;
            char *fmt = func_00288FB8(0x2f7e);
            func_00115DA8(buffer,fmt,func_L04_0040A1D0(D_L04_001B0904));
            TEXT(col,shift+230,buffer); }
    } else {
            char *fmt;
            CENTER(150,func_00288FB8(0x2f73));
            fmt = D_L04_001B0940;
            { char *str = func_00288FB8(0x2f7d);
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(D_001A7A0A) reward*=10;
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2f5e)); }
            { int row_ = label_y((void *)center, (float)(shift+210), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FAA8(center,row_,0x80f0f0f0UL,buffer,len_); }
    }
    func_002FC560(71,0x5360b);
    return 1;
}
