/* 7 November 2026, USA v1.01; retained, not linked.
 * Profile: own -g8 unit (e.g. src/levels/10_hrugis_cloud/L10_003170D0-menu-g8.c) with
 * `-O2 -G8 -ffunction-sections -ffast-math` in config/cflags.txt.
 * tools/check.py: 3440/3420 bytes, 0/1. Relocation-masked alignment: 795 of retail's 855
 * instructions (the 4 November 3260-byte source scores 602 on the same script).
 * The same body is func_L05_0041EF00 and func_L15_0042EFE0.
 *
 * Lawful causes found (no volatile, no dead store, no barrier):
 * - D_L10_001B1390..139C are one per-race array. Retail reads [0] through $gp and [1]..[3]
 *   as unsplit sym+offset macro loads (lui/lw with empty branch slots), which is what the
 *   earlier volatile scalars imitated. [0] uses a D_L10_001B1390_gp SDATA view, as
 *   D_L22_001B0A20_gp does. D_L10_001B1448/1454/1460/146C are rows of one [4][3] reward table.
 * - func_L05_00303000 forwards its colour and text to the matched func_L05_00302CE8
 *   (u64 color, u8 *text); retail builds 0x80F0F0F0 as a 64-bit constant
 *   (ori/dsll/ori), so the caller's prototype has u64 color, as the other text helpers.
 * - Every row goes through one MenuY(y, adjustment) helper; rows with no adjustment pass
 *   0.0f. Under -ffast-math `scaled + 0.0f` folds, the two arms become equal and the
 *   test vanishes after the register allocators, giving retail's $f20-$f24, $s1 for
 *   0x8710, $s3 = 1 and row registers without a dead body. The ternary and an if/else
 *   assigning one row compile the same; `if (...) return ...; return ...;` loses 120 words.
 *
 * Still different: sched2 order. Retail keeps a block boundary after each vanished
 * test, so the 200.0f rows load 1.0f/0.0f and the arguments after cvt.s.w, and the
 * text calls keep the order a3, a1, a0, a2, t0. Here the arguments interleave with the
 * row, which breaks the cross-jump of the three "locked" 0x2F73 tails (20 bytes over).
 * The index register is $v0 here and $v1 in retail. No effect from -fno-sched-interblock,
 * -fno-sched-spec, -malign-loops=2, -frac2-keep-block-order, -frac2-gcse-unsplit-edges,
 * -fno-gcse (782), clamp spellings, or passing func_001157AC(text) as the argument.
 * Worse: a do { } while (0) statement macro (non-empty) on any subset of rows (545-742),
 * a comma-expression macro (fold drops the test at tree level: 616), and a float-returning
 * helper for the image rows (746-760).
 */
#include "common.h"

extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern s32 func_00283D38(s32, s32, f32);
extern s32 func_00336D50(u8 *, s32);
extern void func_00300968(char *, s32, f32, f32, f32, f32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 func_0027FBD8(s32, s32, u64, char *, s32);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern s32 func_0027FAA8(s32, s32, u64, char *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
/* Forwards to func_L05_00302CE8 (u64 color, u8 *text); retail builds the colour as a 64-bit
   constant (ori/dsll/ori), as for the other text helpers. */
extern void func_L05_00303000(s32, s32, s32, s32, u64, u8 *, s32);
extern s32 D_001A7340;
typedef struct { u8 pad[0x1A0]; s32 buttons; } MenuInput;
extern MenuInput D_00138180;
extern u8 D_001A7A0A;
extern s32 D_L10_001A8F00;
extern u8 *D_L10_001A904C;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80;
extern s32 D_L10_001B2048;
extern s32 D_L10_001B1F64 __attribute__((sda));
extern s32 D_L10_001B143C __attribute__((sda));
/* One record per race: [0] is read through $gp (its SDATA view), [1]..[3] at offsets, which
   cc1 leaves as unsplit macro loads (lui/lw, empty branch slots), as retail. */
extern s32 D_L10_001B1390[] __attribute__((sda));
extern s32 D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
/* Reward table, three tiers per race (rows 0x1448, 0x1454, 0x1460, 0x146C). */
extern s32 D_L10_001B1448[][3] __attribute__((sda));
extern s32 D_L10_001B1448_gp[][3] SDATA(D_L10_001B1448);

static __inline__ s32 MenuY(f32 y, f32 adjustment) {
f32 scaled = y * D_L10_001B2D84 + 0.5f; return D_L10_001B2D80 == 1 ? (s32)(scaled + adjustment) : (s32)scaled;
}

s32 func_L10_004227A0(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 r, remainder, color, blink, x, headerX, reward;
    char *text;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_L10_001A8F00 || !D_L10_001A904C) return 1;
    D_L10_001B1F64 = 0;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x45);
    { s32 row; row = MenuY(200.0f, 0.0f); imageY = (f32)row; }
    func_00300968((char *)r, 0x60442D00, center, imageY, 1.0f, 0.0f);
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x44);
    { s32 row; row = MenuY(200.0f, 0.0f); imageY = (f32)row; }
    func_00300968((char *)r, 0x55F0C070, center, imageY, 1.0f, 0.0f);
    remainder = D_L10_001B2048 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = func_00283D38(0x80FFDE8D, 0x60442D00, pulse);
    color = (D_00138180.buttons & 0x2000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuY(291.0f, 2.0f);
    func_00300A00((char *)r, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (D_00138180.buttons & 0x8000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L10_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuY(291.0f, 2.0f);
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
            s32 len;
            s32 row = MenuY(101.0f, -2.0f);
            len = func_001157AC(text);
            func_0027FB40(x, row, 0x80F0F0F0ULL, text, len);
        }
        text = func_00288FB8(0x2FE7);
        {
            s32 len;
            s32 row;
            row = MenuY(131.0f, 0.0f);
            len = func_001157AC(text);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L10_001B1390_gp[0];
            if (index >= 3) index = 2;
            reward = D_L10_001B1448_gp[0][index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
        {
            s32 len;
            s32 row;
            row = MenuY(242.0f, 0.0f);
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
                s32 len;
                s32 row = MenuY(101.0f, -2.0f);
                len = func_001157AC(text);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, len);
            }
            text = func_00288FB8(0x2FE8);
            {
                s32 len;
                s32 row;
                row = MenuY(131.0f, 0.0f);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L10_001B1390[1];
                if (index >= 3) index = 2;
                reward = D_L10_001B1448[1][index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = MenuY(242.0f, 0.0f);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = MenuY(170.0f, 0.0f);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L10_001B1390_gp[0] && D_L10_001B1390[1]) {
            text = func_00288FB8(0x2FE5);
            {
                s32 len;
                s32 row = MenuY(101.0f, -2.0f);
                len = func_001157AC(text);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, len);
            }
            text = func_00288FB8(0x2FE9);
            {
                s32 len;
                s32 row;
                row = MenuY(131.0f, 0.0f);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L10_001B1390[2];
                if (index >= 3) index = 2;
                reward = D_L10_001B1448[2][index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = MenuY(242.0f, 0.0f);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = MenuY(170.0f, 0.0f);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L10_001B1390_gp[0] && D_L10_001B1390[1] && D_L10_001B1390[2]) {
            text = func_00288FB8(0x2FE6);
            {
                s32 len;
                s32 row = MenuY(101.0f, -2.0f);
                len = func_001157AC(text);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, len);
            }
            text = func_00288FB8(0x2FEB);
            {
                s32 len;
                s32 row;
                row = MenuY(131.0f, 0.0f);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L10_001B1390[3];
                if (index >= 3) index = 2;
                reward = D_L10_001B1448[3][index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = MenuY(242.0f, 0.0f);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = MenuY(170.0f, 0.0f);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    }
    func_0027F5B8(119, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F40), -1);
    func_0027F5B8(356, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F41), -1);
    func_0027F5B8(279, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F42), -1);
    return 1;
}
