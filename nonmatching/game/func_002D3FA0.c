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

int func_002D3FA0(void)
{
    MenuCorners corners = D_001ABA78;
    char text[32];
    int color = func_002A9588(0x60241700, 0x55F0C070, 30, 0, 0);
    int x, index, i;
    char *first, *second;
    int t;
    float px, py;
    func_0027C540(0);
    t = func_00336D50(D_001A8CFC[0] + 0x8710, 0XD0);
    px = (float)(D_001A7340[0] / 2);
    py = (float)label_y((void *)t, (float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, 1);
    func_00300A00(t, 0x60442D00, px, py, 1.0f, 1.0f, 0.0f);
    t = func_00336D50(D_001A8CFC[0] + 0x8710, 0XD1);
    px = (float)(D_001A7340[0] / 2);
    py = (float)label_y((void *)t, (float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, 1);
    func_00300A00(t, 0x60241700, px, py, 1.0f, 1.0f, 0.0f);
    t = func_00336D50(D_001A8CFC[0] + 0x8710, 0XD2);
    px = (float)(D_001A7340[0] / 2);
    py = (float)label_y((void *)t, (float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, 1);
    func_00300A00(t, 0x55F0C070, px, py, 1.0f, 1.0f, 0.0f);
    t = func_00336D50(D_001A8CFC[0] + 0x8710, 0XD3);
    px = (float)(D_001A7340[0] / 2);
    py = (float)label_y((void *)t, (float)(D_001A7344[0] / 2), D_001B23A4[0], 0.5f, 1);
    func_00300A00(t, 0x55F0C070, px, py, 1.0f, 1.0f, 0.0f);
    func_0028FC48(228, label_y((void *)color, 326.0f, D_001B23A4[0], 0.5f, 1), 230, label_y((void *)color, 387.0f, D_001B23A4[0], 0.5f, 1), color, 0);
    func_0028FC48(286, label_y((void *)color, 326.0f, D_001B23A4[0], 0.5f, 1), 288, label_y((void *)color, 387.0f, D_001B23A4[0], 0.5f, 1), color, 0);
    func_0028FC48(228, label_y((void *)color, 325.0f, D_001B23A4[0], 0.5f, 1), 288, label_y((void *)color, 327.0f, D_001B23A4[0], 0.5f, 1), color, 0);
    func_0028FC48(228, label_y((void *)color, 386.0f, D_001B23A4[0], 0.5f, 1), 288, label_y((void *)color, 388.0f, D_001B23A4[0], 0.5f, 1), color, 0);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, label_y((void *)color, 36.0f, D_001B23A4[0], 0.5f, 1), 192, label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, 1), &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, label_y((void *)color, 36.0f, D_001B23A4[0], 0.5f, 1), -192, label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, 1), &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 16, label_y((void *)color, 228.0f, D_001B23A4[0], 0.5f, 1), 192, -label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, 1), &corners);
    func_0028EA58(func_0028E588(0xEAA8, 0), 400, label_y((void *)color, 228.0f, D_001B23A4[0], 0.5f, 1), -192, -label_y((void *)color, 96.0f, D_001B23A4[0], 0.5f, 1), &corners);
    func_0028E868(func_0028E588(0xEAA8, 1), 402, label_y((void *)color, 50.0f, D_001B23A4[0], 0.5f, 1), 89, label_y((void *)color, 115.0f, D_001B23A4[0], 0.5f, 1), 64);
    x = label_y((void *)color, 116.0f, D_001B23A4[0], 0.5f, 1);
    func_0027FB40(445, x, 0x80F0F0F0ULL, func_00288FB8(0x3212), -1);
    x = label_y((void *)color, 134.0f, D_001B23A4[0], 0.5f, 1);
    func_0027FB40(445, x, 0x80F0F0F0ULL, func_00288FB8(0x3213), -1);
    first = func_00288FB8(0x3213);
    second = func_00288FB8(0x2D55);
    func_00115DA8(text, D_001AB998, first, second);
    func_0027FAA8(159, label_y((void *)color, 18.0f, D_001B23A4[0], 0.5f, 1), 0x80F0F0F0ULL, text, -1);
    x = label_y((void *)color, 187.0f, D_001B23A4[0], 0.5f, 1);
    func_0027FAA8(445, x, 0x80F0F0F0ULL, func_00288FB8(0x2D4F), -1);
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
    func_002FC620(30, 385, label_y((void *)color, 50.0f, D_001B23A4[0], 0.5f, 1), label_y((void *)color, 213.0f, D_001B23A4[0], 0.5f, 1));
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
