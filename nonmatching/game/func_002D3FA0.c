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
extern int func_0028EA58(int, int, int, int, int, MenuCorners *);
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
    int x, x2, index, i;
    char *first, *second;
    int t;
    int y1, y2, y3;
    int on2 = 1, on3 = 1;
    int one = 1;
    float px, py;
    func_0027C540(0);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD0), 0x60442D00, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD1), 0x60241700, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD2), 0x55F0C070, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0XD3), 0x55F0C070, (float)(D_001A7340[0] / 2), (float)hud_coord((float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    func_0028FC48(228, label_y((void *)color, 326.0f, D_001B23A4[0], 0.5f, one), 230, label_y((void *)color, 387.0f, D_001B23A4[0], 0.5f, one), color, 0);
    func_0028FC48(286, label_y((void *)color, 326.0f, D_001B23A4[0], 0.5f, one), 288, label_y((void *)color, 387.0f, D_001B23A4[0], 0.5f, one), color, 0);
    func_0028FC48(228, label_y((void *)color, 325.0f, D_001B23A4[0], 0.5f, one), 288, label_y((void *)color, 327.0f, D_001B23A4[0], 0.5f, one), color, 0);
    func_0028FC48(228, label_y((void *)color, 386.0f, D_001B23A4[0], 0.5f, one), 288, label_y((void *)color, 388.0f, D_001B23A4[0], 0.5f, one), color, 0);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, label_y((void *)color, 36.0f, D_001B23A4[0], 0.5f, one), 192, label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, one), &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, label_y((void *)color, 36.0f, D_001B23A4[0], 0.5f, one), -192, label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, one), &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, label_y((void *)color, 228.0f, D_001B23A4[0], 0.5f, one), 192, -label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, one), &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, label_y((void *)color, 228.0f, D_001B23A4[0], 0.5f, one), -192, -label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, one), &corners);
    func_0028E868(func_0028E588(0xEAA8, 1), 402, label_y((void *)color, 50.0f, D_001B23A4[0], 0.5f, one), 89, label_y((void *)color, 115.0f, D_001B23A4[0], 0.5f, one), 64);
    y1 = label_y((void *)color, 116.0f, D_001B23A4[0], 0.5f, one);
    func_0027FB40(445, y1, 0x80F0F0F0ULL, func_00288FB8(0x3212), -1);
    y2 = label_y((void *)color, 134.0f, D_001B23A4[0], 0.5f, one);
    func_0027FB40(445, y2, 0x80F0F0F0ULL, func_00288FB8(0x3213), -1);
    func_00115DA8(text, D_001AB998, func_00288FB8(0x3213), func_00288FB8(0x2D55));
    func_0027FAA8(159, label_y((void *)color, 18.0f, D_001B23A4[0], 0.5f, one), 0x80F0F0F0ULL, text, -1);
    y3 = label_y((void *)color, 187.0f, D_001B23A4[0], 0.5f, one);
    func_0027FAA8(445, y3, 0x80F0F0F0ULL, func_00288FB8(0x2D4F), -1);
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
    x2 = 291;
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
            func_002D3D88(index, x2);
        }
        x2 += 56;
    }
    func_0027C660();
    func_002FC620(30, 385, label_y((void *)0, 50.0f, D_001B23A4[0], 0.5f, on2), label_y((void *)0, 213.0f, D_001B23A4[0], 0.5f, on3));
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
