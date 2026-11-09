/* 9 November 2026 (o125, L11/L02 HUD idioms): func_00300A00 as (int, float x, int colour, ...) (bank-preserving): no change (local scorer, 1 row/2476 kept). y3 helper sweep in the group: label_y3 (mode test last) on `(void *)e` drops the `daddu v1,v0` copy and the loop-1 nop (2468 bytes, x/i/s5 slots right) but swaps $f0/$f1 in the y3 rounding (187.0 in $f1, scale in $f0; 7 rows). Cause: with label_y the mode load is a local REG_EQUIV qty in block 125 (v0), which pushes e to v1 (the copy) but gives retail's $f0/$f1; with mode last, mode goes global and FP flips. label_y3 on text/&corners keeps the FP right but puts li a0,0x2D4F in the 288FB8 slot and i=0 in the FAA8 slot (12). Also no gain: all M/H/C test orders, rounding before/after the tests, late mode read, label_y4, call result as handle, group extents (g1-g8), hud_coord/hud_coord3, plain `color` at all rects with/without -fno-gcse (12). Rect 2 still passes cB. */
/* 9 November 2026 (o114, set-once constant sweep after func_L06_00382608): moved each of one/one2/on2/on3 from its initializer to every statement position before its first use (75), split every one/one2/on2/on3 use into its own set-once local at the 12 positions before it (265), and every literal in the rect/label/y3 region (609) and both loops (101) as a set-once local within 6 statements of its use: best still 2476 bytes with row 0x390 (rect-2 cB), the e copy and the loop-1 nop (local scorer, aligned). The only 2468-byte results change loop 2's range test (6 rows). */
/* 9 November 2026 (round o70): 6 rows/2468 -> 1 row/2476 (check.py 0/28, temporary unit; local scorer 1 retail row). C below is new: loop 2 reuses the loop-1 column `x` (x = 291; x += 56): merged x (14 refs) ranks below y3 (0.21-0.239 vs 0.222) and conflicts with it, so y3 s1, x and loop-2 column s2, base2 s1, and A/C/text s2 as retail; `x = 235;` after the r = func_0027FAA8(445, ...) call; y3 in a group `do { y3 = label_y((void *)e, ...); } while (0);`, whose loop notes keep the dead copy test of e to sched2, so x/i/s5 land in retail's delay slots; cC = cB before the rect-1 call (no effect alone). Left: row 228 (rect 2 passes B: cse make_regs_eqv keeps cB canonical because cC does not outlive cB; a later (void *)cC use costs a truncation), plus 2 extra words: `daddu v1,v0` copy of e (label_y's copy test) and the loop-1 align nop that follows from it. Handles without the copy (label_y2/label_y3 e, text, 0, &corners, y1/y2, call result passed directly, e set inside the group, second = 288FB8 split, explicit i = 0) give 2468 bytes but x lands after the 288FB8 call and i in the FAA8 slot (4 rows); uninitialised handles give 1 row/2468 (not allowed). Measured without gain: col2 as color (A prio 0.1385 > base2 0.125), ghosts one/one2 as col2, do-while around cC = cB (loop notes break f20-f22), dead-test L padding (dead tests do not count in L). */
/* 9 November 2026 (round o67): body unchanged (6 rows); new 9-row form (2476 bytes) gets C, text, A, B and 0x8710 all as retail. Recipe (from o60's y.c): every handle after rectangle 1 non-A, ya/yb via hud_coord (A refs drop to 2, so A is allocated after `one`), y1/y2/text-18 hud_coord, y3 label_y((void *)e) with e = text-18 FAA8 result, active on3 for text-18/y3; loop-2 column its own dead local yb. global.c then: `one` (ghost, sprites..y2) takes s1, A s2 (s0 excluded by 0x8710), C s2, text s2. Left: rect 2 passes B (row 228), loop-2 column/base s1/s2 swap (column 7 refs/82 insns outranks base 5/80; reusing color as column fixes it but gives A 9 refs/194 = prio 0.139 > `one` 0.112 and loop-2 base 0.125, so A takes s1: A needs prio < 0.125, e.g. 8 refs), v1 copy of e (row 446), loop-1 nop + 8 bytes. Priority = floor_log2(refs)*refs/live_length, refs weighted by loop depth (read with -dl: "Register N used R times across L insns"). Permuter seeded from y.c interrupted (disk full). */
/* 9 November 2026 (round o60): still 6 masked rows, 2468 bytes (check.py 0/28 in a temporary unit). func_0028EA58 now declared void as in src (no code change). Why C/text miss s2: global.c picks the first used, conflict-free saved reg, so A (pseudo color) only avoids s1 when it is live across the local-alloc s0/s1 uses near sprintf/y3; that same life blocks C and text. Measured: with every late handle non-A (rect hud_coord, EA58/E868 handle t, y1 hud_coord: these are free, still 6 with A live), A and C share s1 and text gets s2 (15-17); color reassigned to the FAA8 result as y3 label_y2 handle gives A s2 and text s2 but C s1 (25). Scripted: uniform and per-call handles (color/cB/cC/int cB,cC/long/0/one/on2/on3/ya/yb/&corners/t/call results/text/y1/y2, label_y vs label_y2, hud_coord), 3 coordinate descents per space, full cartesian of the last three handles (1728), split active locals (no effect: one2 is not used), color handles on sprites/post-loop (no effect); permuter 1500 s (best 10). Next: something conflicting with C that prefers s1 (regs_someone_prefers) or keeps s1 out of regs_used_so_far until C is allocated. */
/* 9 November 2026 (round o57): 27 -> 6 masked rows, size now right (2468 bytes) with -O2 -G8 -ffunction-sections -fno-gcse -frac2-frame-pointer-liveness. The switch lets flow2 delete a dead set of $fp, so a third ghost forms: the first post-loop call is label_y2 (label_y with ONE handle test; NEEDS AN OWNER RULING) whose handle is the result r of the last func_0027FAA8. That gives the s6/s7/fp ghosts, drops the loop-1 nop, and the used result frees $v0 for loop 1's lui (a REG_UNUSED call result keeps v0 from the next insn in local-alloc). Plain label_y with that handle keeps `daddu s6,v0`. Left: C in s1 (retail s2) and text in s3 (retail s2): A stays live through the late (void *)color handles. Measured without gain: late handles as cB/cC (int or unsigned long: truncation or copies), t = func_0028E588 result, call results r of FB40/FAA8/sprintf (v1 copies), hud_coord per call, 0, text, y2, ya; `color = cB` reassignment; copy-chain order; permuter 1500 s. */
/* 9 November 2026 (switch sweep s40): -frac2-frame-pointer-liveness (+ -fno-expensive-optimizations): size 2476 -> 2468 matches, 194 differing rows; still far. */
/* 9 November 2026 (round o34): 29 -> 27 masked aligned rows (617 words): the second post-loop label_y takes handle `(void *)i` (i is 12+ after loop 2), which puts `li a0,30` after both roundings as retail. Measured without gain: every late (after rectangle 1) handle as cB/cC/one/on2/on3/0/ya/yb/&corners/text, per call and as suffixes (35-143; A then moves to s1 or a set survives); random local declaration order (150, all 29); moving each statement 1-3 lines (best 29); x/for-init/unsigned range forms in loop 1; post-loop y locals; permuter 1500 s (best 46). Left: C in s1 and text in s3 (A live through the late color handles), fp save (flow2 never deletes a set of the hard fp, so retail fp pseudo had no set before reload), loop-1 lui v1 and align nop. */
/* 9 November 2026 (round o32): 45 -> 29 masked aligned rows (617 words): rectangle 1 takes its y values in locals ya/yb, then `cB = color` (unsigned long) and `cC = cB` after the call, rectangles 1/4 pass cB and 2/3 cC (retail's B/C copy order now exact); loop 2 reuses the dead `color` as its column (permuter find, as func_002FA270's dead-local reuse), fixing the x2/base swap. Left: C in s1 not s2 and text in s3 not s2 (A stays live through the later (void *)color handles; handles one/0/cB/cC/unsigned-long handle variants all worse, 47-139), fp save, loop-1 lui v1 and nop, li a0,30 order. */
/* 8 November 2026 (Sonnet round o28, lesson 49): re-measured 2464/2468. Retail's color copies are three values: A (call result, s2) -> B = A (s0, made just before rectangle 1) -> C = B (s2, jal delay slot); rectangles 1 and 4 pass B, 2 and 3 pass C, so A dies at rectangle 1. A second local `int color2 = color;` after rectangle 1 used by rectangles 2-3 (permuter find, hand-cleaned) gives the right length (617 words) and the copy chain, but with `(void *)color` handles A stays live and C lands in s1 (same masked row count, 45 -> 45-47); handles on color2 or an unsigned long copy cost 8-30 rows. Still missing: fp save, copy order, text pointer s2. */
/* 8 November 2026 (Sonnet round, lesson 48 sweep o14): every movable single-line statement (460 variants, 1-6 places within its block) and 10206 pairs of the near-best moves (local cc1, -fno-gcse): none beats the base (still 2464/2468). */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_0028EA58 is declared int but src/game/0028EA58-g8.c is void: corrected, unchanged (2464/2468 bytes, 480 masked unaligned rows before and after). */
/* 8 November 2026, Sonnet round (o2): the two post-loop label_y calls take their own `active`
 * locals on2/on3 (= 1, set at the top, handle 0). Their dead mode tests go at flow2, so on2/on3
 * become ghosts s6+s7 and the loop pseudos now take s1-s5 as retail. Still 2464/2468 bytes; 23
 * aligned rows (the 55-row form scores 30 on the same counter). Left: fp save, color copy at
 * rectangle 1/3, text pointer s3 (retail s2), loop-2 x2/base swap (x2 is allocated before the
 * base), `li a0,30` order, and the loop-1 align nop (goes with fp). Measured: flow2 never deletes a
 * set of $fp (flow.c insn_dead_p), so retail's fp pseudo had no set left after reload; a ghost
 * only forms from an `active` test (handle tests are threaded and survive flow2, keeping the set).
 * Tried without gain: post-loop handles = text-draw results, &corners, format address, y2, x2;
 * a third post-loop active (dead label_y, int helper, mode read before the loops); const mode;
 * single x for both loops (32); x2 set earlier (fp then holds a kept li 1); one as post-loop
 * active (29); handles 0/y1/y2/text after sprintf (39-129). Permuter (1500 s) best 27 rows. */
/* 8 November 2026, round 2: the second loop gets its own column variable x2 (x only in the first
 * loop). Retail's y3 then takes s1 before x, so loop 1 is exact apart from s4/s5 and loop 2 apart
 * from x2/base (s1/s2) and s4/s5: 55 masked rows (was 71), still 2464/2468 bytes with -fno-gcse.
 * Ghost saved registers: `one` is ghost s4 and the post-loop handle y2 keeps y2 in s5. With `one`
 * at only <= 8 label_y calls the ghost drops to s6/s7 but other rows get worse (61-69). A handle with
 * no set at all (an uninitialised local, NOT landable) gives ghosts s6+s7 and 49 rows, so retail's
 * post-loop handles are values whose set is deleted after allocation. Tried without gain:
 * -fmove-all-movables (with or without -fno-gcse: hoists 0x14 out of both loops, 84-86 rows),
 * h = y1/y2/y3 copies as handles (cse follows jumps and merges them), handle = a D_001A7340 load
 * or color copy made before the loops (load not deleted, 2472 bytes), (void *)one / color / text /
 * y3 handles, separate i/index in loop 2, hud_coord on rectangles 2-4 or text. Loops hold no
 * label_y and no float constants, and retail rebuilds the table base in each loop preheader. */
/* 8 November 2026, HUD recipe pass: build as its own unit src/game/002D3FA0-g8.c with
 * `-O2 -G8 -ffunction-sections -fno-gcse` (config/cflags.txt line). 2464/2468 bytes, 0/28, frame
 * 0xA0 and saved set s0-s7 + f20-f22 now as retail (fp still missing). Aligned masked diff: 71
 * unmatched rows (the 7 November label_y form scores 254 on the same counter). What closed it:
 * - each sprite draw passes the func_00336D50 call directly as the first argument (no `t =`):
 *   retail's copy to $a2 then the 7344/7340 loads in $v0/$v1, all four sprite blocks exact;
 * - sprite y through hud_coord (result as handle), rectangles/textures/text through label_y with
 *   color as handle, `active` the local `one` (= 1) at every call;
 * - y1/y2/y3 as separate locals per text draw (retail mfc1 straight into the saved register);
 * - the sprintf call with both func_00288FB8 calls inline (format address held in a saved reg);
 * - -fno-gcse keeps `one` a ghost saved register (only s4 here) and fixes the rectangle copies.
 * Left: retail has three ghost saved registers (s6, s7, fp, all live across both loops, so they
 * are values made before the loops and only read by the post-loop label_y tests); here one ghost
 * (s4) and the post-loop handle y2 holds s5, so loop pseudos land on s1/s2/s6/s7 instead of
 * s1-s5 (x and the table base swap s1/s2). Color: retail `s0 = s2; t0 = s0; s2 = s0` at the
 * first rectangle (color dies there, its 64-bit copy lives on); here the copy is remade at the
 * third rectangle. One texture block moves `a0 = v0` early. Tried this round without gain:
 * -fmove-all-movables (2476 bytes), -fno-schedule-insns, -fno-sched-interblock, plain extern
 * globals (no change), u64/long color (2504 bytes), several `one`-like locals (cse merges them
 * without -fno-gcse), first-sprite pointer or loop variables as the post-loop handle, hud_coord
 * on rectangles/text. */
/* 7 November 2026, label_y sweep: every y rounding goes through label_y (the four centred sprite ys with handle t, every rectangle/text y with handle (void *)color). Same profile: 2460/2468 bytes (was 2428), masked aligned-diff rows 547 -> 174 (m1d h.py count). Retail still saves two more GPRs (s7, fp) and orders the sprite y conversion before the move of t. */
/* 2 November 2026: retained nonmatching C; no linked matching credit.
 * Profile: -O2 -G8 -ffunction-sections.
 * USA v1.01 check: 2428/2468 bytes, 0/28 placements.
 * Matched text functions 0027FAA8/0027FB40 and helper 002D3D88 return int. The rectangle helper
 * 0028FC48 takes a full 64-bit unsigned-long style argument, and 0027C540 takes int. Restoring
 * these actual contracts leaves 2428/2468 bytes and 0/28 placements. Rounding boundaries, FP
 * hoisting and the saved-register set remain unresolved.
 */
/*
 * func_002D3FA0 (2468 bytes, boot + 27 levels). Tier: Opus 5.5 xhigh (opus-1), task v1900.
 * Build it as its own -G8 unit (src/game/002D3FA0-g8.c): $gp is needed for D_001ABA74 outside delay
 * slots, and every other global stays absolute because it is an incomplete sda array.
 * Best check.py: 2428/2468 bytes, 0 of 28 places, 605 of 617 rows differ (most of them shifted). No
 * linked build was run. All required declarations are below.
 *
 * Settled, correcting the earlier draft:
 * - Both table loops now have retail's control flow; every branch offset agrees, and the rest is
 *   registers. x only steps when an entry was drawn or the index was out of range. Retail's first test
 *   is a folded range test, `index >= 0 && index < 12`; its second `bltz`/`slti` is the top test of
 *   the inner `while`, rotated and threaded past the `if`.
 * - Scalars read as `lui $r; lw $r` are `D[] __attribute__((sda))` and read as D[0]. The plain `extern`
 *   of the old draft hoists %hi into saved registers; that was part of its "lifetime" difference.
 * - The 40-byte gap is not lost code. Retail does not interleave the rounding chains, so it keeps a nop
 *   between each mtc1 and its mul.s, and that accounts for the difference.
 *
 * What still differs, measured: retail has a block boundary that leaves no instruction, at each
 * rounding (after `mfc1 r`, before the use of r):
 * - The float constants are not hoisted past it. Here all of them rise to the top, and that alone
 *   gives f20-f27 and the 0xB0 frame.
 * - The coordinates are evaluated left to right and never interleave.
 * - t, x and y are global pseudos: t in $a2, x and y already in $f12/$f13 before the block ends.
 * Yet 0.5f ($f20), 1.0f, 0.0f, 0x8710 ($s0) and the D_001B23A4 load are shared across those boundaries,
 * so cse1 and cse2 do not see them. No wording tried gives both.
 *
 * Tried, in this unit or in -G0 and small scratch units (none landable, none exact):
 * - `do { } while (0)` before each call: gives frame 0xA0, f20-f22 and retail's 1.0f/0.0f placement, but
 *   combine sinks the cvt.s.w into the later part (the note is no block), so t and the conversions
 *   stay wrong. With barriers after every coordinate as well: 2428 bytes, frame 0x90. A non-empty wrapper
 *   around x and y blocks retail's 0.5f position. All of these are forbidden forms anyway.
 * - `if (t != 0) return (int)(v*S+0.5f) + adjust; return (int)(v*S+0.5f);` with adjust 0: leaves no word
 *   and gives retail's exact part-B order and t in $a2, but cse loses every constant at the join
 *   (`ori $a0,0x8710` per draw, 0.5f local). The test is also a placeholder, so it is not landable.
 * - The same helper testing D_001B23A0 keeps that load, which retail does not have.
 * - Single-armed `r = ...; if (c) r += adjust;` (constant, or a local holding 0), and copy arms: deleted
 *   by jump1, so no boundary reaches flow. `py + 0.0f` never folds and leaves its branch.
 * - -fno-schedule-insns: fixes the f20-f22 save set but gives the wrong order (f14-f16 first).
 * Next: a test that cse follows around (single-use label) whose arm survives to flow and is then
 * empty, or evidence of the original helper. Retail's s6/s7/fp saves are not explained; they may belong
 * to whatever that construct leaves behind. The copies s0=s2, s2=s0 around the first func_0028FC48
 * look like gcse copies from the same boundaries.
 */
#include "include_asm.h"
typedef struct { char pad[0x1CC]; unsigned char *entries; int count; int timer; } MenuEntryState;
extern MenuEntryState D_001F2840;
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];
extern unsigned int D_001A7AF0[] __attribute__((sda));
extern int D_001ABA74 __attribute__((sda));
extern int D_001A7340[] __attribute__((sda)), D_001A7344[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
typedef struct { unsigned char bytes[16]; } MenuCorners;
extern MenuCorners D_001ABA78;
extern char D_001AB998[];
extern int func_002A9588(int, int, int, int, int);
extern int func_00336D50(char *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, MenuCorners *);
extern void func_0028E868(int, int, int, int, int, int);
extern char *func_00288FB8(int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);
extern int func_0027FAA8(int, int, unsigned long long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_002D3D88(int, int);
extern void func_002FC620(int, int, int, int);
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_002A0300(char *, int), func_002A0220(void), func_002A0380(void);
extern void func_002ECB70(char *);
extern void func_0027C540(int), func_0027C660(void);
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001B23A0;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
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
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;
    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
int func_002D3FA0(void)
{
    MenuCorners corners = D_001ABA78;
    char text[32];
    int color = func_002A9588(0x60241700, 0x55F0C070, 30, 0, 0);
    int x, index, i;
    char *first, *second;
    int t, r, e;
    int y1, y2, y3;
    int on2 = 1, on3 = 1;
    int one = 1;
    int one2 = 1;
    int one3 = 1;
    int ya, yb;
    unsigned long cB;
    unsigned long cC;
    float px, py;
    func_0027C540(0);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD0), 0x60442D00, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD1), 0x60241700, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD2), 0x55F0C070, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD3), 0x55F0C070, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    ya = hud_coord(326.0f, D_001B23A4[0], 0.5f, one);
    yb = hud_coord(387.0f, D_001B23A4[0], 0.5f, one);
    cB = color;
    cC = cB;
    func_0028FC48(228, ya, 230, yb, cB, 0);
    func_0028FC48(286, hud_coord(326.0f, D_001B23A4[0], 0.5f, one), 288, hud_coord(387.0f, D_001B23A4[0], 0.5f, one), cC, 0);
    func_0028FC48(228, hud_coord(325.0f, D_001B23A4[0], 0.5f, one), 288, hud_coord(327.0f, D_001B23A4[0], 0.5f, one), cC, 0);
    func_0028FC48(228, hud_coord(386.0f, D_001B23A4[0], 0.5f, one2), 288, hud_coord(388.0f, D_001B23A4[0], 0.5f, one2), cB, 0);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 16, label_y((void *)t, 36.0f, D_001B23A4[0], 0.5f, one2), 192, label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 400, label_y((void *)t, 36.0f, D_001B23A4[0], 0.5f, one2), -192, label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 16, label_y((void *)t, 228.0f, D_001B23A4[0], 0.5f, one2), 192, -label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 0); func_0028EA58(t, 400, label_y((void *)t, 228.0f, D_001B23A4[0], 0.5f, one2), -192, -label_y((void *)t, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    t = func_0028E588(0xEAA8, 1); func_0028E868(t, 402, label_y((void *)t, 50.0f, D_001B23A4[0], 0.5f, one2), 89, label_y((void *)t, 115.0f, D_001B23A4[0], 0.5f, one2), 64);
    y1 = hud_coord(116.0f, D_001B23A4[0], 0.5f, one2);
    e = func_0027FB40(445, y1, 0x80F0F0F0ULL, func_00288FB8(0x3212), -1);
    y2 = hud_coord(134.0f, D_001B23A4[0], 0.5f, one2);
    e = func_0027FB40(445, y2, 0x80F0F0F0ULL, func_00288FB8(0x3213), -1);
    e = func_00115DA8(text, D_001AB998, func_00288FB8(0x3213), func_00288FB8(0x2D55));
    e = func_0027FAA8(159, hud_coord(18.0f, D_001B23A4[0], 0.5f, on3), 0x80F0F0F0ULL, text, -1);
    do {
    y3 = label_y((void *)e, 187.0f, D_001B23A4[0], 0.5f, on3);
    } while (0);
    r = func_0027FAA8(445, y3, 0x80F0F0F0ULL, func_00288FB8(0x2D4F), -1);
    x = 235;
    for (i = 0; i < 12; i++) {
        index = D_001ABA74 - i;
        if (index >= 0 && index < 12) {
            while (index >= 0) {
                if ((D_001A7AF0[0] & D_0026CFD0[index].selectionMask) == D_0026CFD0[index].requiredBits)
                    break;
                index--;
                i++;
            }
            if (index < 0)
                continue;
            func_002D3D88(index, x);
        }
        x -= 56;
    }
    x = 291;
    for (i = 1; i < 12; i++) {
        index = D_001ABA74 + i;
        if (index >= 0 && index < 12) {
            while (index < 12) {
                if ((D_001A7AF0[0] & D_0026CFD0[index].selectionMask) == D_0026CFD0[index].requiredBits)
                    break;
                index++;
                i++;
            }
            if (index >= 12)
                continue;
            func_002D3D88(index, x);
        }
        x += 56;
    }
    func_0027C660();
    func_002FC620(30, 385, label_y2((void *)r, 50.0f, D_001B23A4[0], 0.5f, on2), label_y((void *)i, 213.0f, D_001B23A4[0], 0.5f, on3));
    func_002A0250();
    func_002A01C8();
    func_002A01F0();
    func_002A0300(D_001F2840.entries, D_001F2840.count);
    func_002A0220();
    func_002A0380();
    func_0027C540(0);
    func_002ECB70(D_001F2840.entries);
    func_0027C660();
    func_002FC620(0, D_001A7340[0] - 1, 0, D_001A7344[0] - 1);
    return 0;
}
