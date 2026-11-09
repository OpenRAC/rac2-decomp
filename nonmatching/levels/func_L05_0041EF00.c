/* 9 November 2026 (round o63, label_y3 per owner ruling, L05 measured, ~230 local compiles): still 5 rows; C below unchanged. label_y3 (label_y with the mode test after both handle tests, mode read at top) at the 242 sites with case 0 kept: (void *)n in cases 1-3 gives 14 rows (sprintf a0/a1 swap returns AND the 242 row $f0/$f1 swap stays); best handle mix buf/buf 10 (f swap only); all 27 dead-assignment RHS mixes (scale/half/value) unchanged; mode read after the multiply, between the handle tests, or inline at the test: 10-22 rows (read between the tests with buf fixes the f rows but adds sprintf + 3 strlen-call rows). So the f0/f1 rows are right only when the mode test comes first (label_y/label_y2), and sprintf only when no mode load is early; label_y3 does not join the two. */
/* 9 November 2026 (round o62, L05 measured, ~700 local compiles): still 5 rows; C below unchanged. Found the mechanisms: (1) sprintf a0/a1/a2 order is a sched2 tie on dependent counts: without a block end after the 242 row, a0=sp gets extra dependents (the strlen a0 set, the two calls, the block-end branch) and goes first; (2) final.c gives the first CODE_LABEL after any NOTE_INSN_LOOP_BEG 8-byte alignment, so a do-while starting at the sprintf (which does fix the sprintf rows in every case: label_y2(n) + `do { n = sprintf(...); row = label_y2(n, 242...); } while (0);` leaves only nops) pads before case 1 else label (retail row 469, odd) and case 3 MenuY tail (row 701, odd); groups starting earlier (index block / reward*=10 test, so the even join label 432/666 is inside) keep size but move the lbu/index rows and do not fix sprintf (the loop note must sit at the 432/666 block start). So retail had no loop there. Also measured: 242 handles r, headerX, blink, color, remainder (size changes), the 101/131 call results and lens (extra move), the 131 row (3 rows per case: 131 a1/t1 order), D_L05_001A904C (same as n); a two-handle-test helper without mode test fixes sprintf and 101 in cases 1-3 but swaps the 242 row f0/f1 (local-alloc: the mode load between the scale load and mul is what gives retail regs; 13 helper/expression variants unchanged), 10 rows. */
/* 9 November 2026 (round o61, label_y2 sweep, L05 measured): 8 -> 5 masked rows, 3420 bytes, C below (this level's text ids 0x2FD6..0x2FDF). Mechanism: the 101 rows' a0/t0 order is a sched1 reg-weight tie, right only when x dies at the 101 call, so no later label may use x as handle; the sprintf args and the 242 row are right only when a sched2 block boundary sits after the 242 row (the x handle's surviving dead jump gives it). Case 0 matched: `do { sprintf(buf, ...); row = label_y(buf, 242, ...); } while (0);` (buf folds the tests; the loop notes end the block). Cases 1-2 (tail-merged): label_y2((void *)n) with n = sprintf result: 101 rows right, sprintf a0/a1/a2 order left (3 rows; flow2 deletes both jumps). Case 3: kept label_y((void *)x) (2 rows: 101 a0/t0). Scripted all per-site helper x handle combos (label_y/label_y2; x, n, reward, buf, text, r, the 131 row value, fmt, a one=1 local; MenuSpriteY on the 101 rows; 1300+ compiles): the 131 row value as handle fixes 101+sprintf but breaks the 131 row (same weight tie); label_y(n) adds `move $3,$2` (mode load takes v0); reward conflicts with the 242 row in s0; one/buf/reward-in-case-0 fold. The case-0 do-while in cases 1-3 adds a .p2align nop each and, with buf, puts 0.5f in f21. No -frac2-* switch changes the rows. */
/* 8 November 2026 (Sonnet round o19, L05 measured): still 8 rows. New: case 0 with a 242 handle helper that has no mode test before the handle tests (`if (h) s = scale; copy = h; if (copy) s = half;` then the mode test last) and sprintf's result `n` as the handle fixes that case's 101 rows and leaves no `move $3,$2` and no sprintf a0/a1 swap; only the 242 row's $f0/$f1 swap is left (value/scale, local-alloc: no mode load between scale and mul): net 2 rows fixed, 5 added in that case. A one-test or no-copy helper keeps the sprintf swap (the jump to the next label is deleted before sched2, so the row joins the sprintf block); buf/global handles fold or add a load. Not changed by: len/x/row locals, if/else MenuY expansion, two-step adds, do-while(0), scale/value/half/one locals, all mode-test orders, scale*value. Permuter (25 min, case 0 region, seeded from this): no improvement (base 150, only ties). */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_00300968 is declared (void *, f32, f32, s32, f32, f32) but src/game/00300618.c:305 is (char *, int flags, f32 x4): real-order calls (object, colour, x, y, ...) give 22 -> 26 masked rows (worse). Same result as func_L05_0041DF58. */
/* 8 November 2026 (round 12, unit placement): no match, still the same 8 rows (the four 101 a0/t0
 * pairs). Retail places each trio member right after a matched HUD sibling and the 488-byte menu
 * func_L05_0041ED18 (L15: E1B0, EDF8, EFE0; L05: DF58, ED18, EF00). Measured in L15 by appending
 * this draft to L15_0042E1B0-g8.c (its label_y, externs, -O2 -G8; func_L15_0042E1B0 still matched):
 * externs after the body or with the unit's externs, with and without func_L05_0041ED18's body
 * between, MenuY written through the unit's screen_coord: 8 rows each. So cse symbol hashing and
 * unit order do not cause the rows. Also tried: `text` as the 242 rows' label_y handle (85 rows).
 * The L05 port was not tried (the L15 one changed nothing).
 */
/* func_L05_0041EF00: near miss, 3420/3420 bytes, 0 of 1 place (USA v1.01, 7 November 2026).
 *
 * Same body as func_L10_004227A0. This is that note's round-three draft, with this level's data
 * names (the addresses come from this level's relocations): 847/855 aligned, the same 8 rows,
 * which are the four 101 rows' a0/t0 order. The L10 note has the analysis. Unit: its own -g8.c,
 * -O2 -G8 -ffunction-sections. MenuSpriteY's dead tests are allowed by owner ruling (7 November 2026).
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
extern s32 D_L05_001A8F00;
extern u8 *D_L05_001A904C;
extern f32 D_L05_001B2D84;
extern s32 D_L05_001B2D80;
extern s32 D_L05_001B2048;
extern s32 D_L05_001B1404[] __attribute__((sda)), D_L05_001B1410[] __attribute__((sda)), D_L05_001B141C[] __attribute__((sda));
extern s32 D_L05_001B1F64 __attribute__((sda));
extern s32 D_L05_001B13EC __attribute__((sda));
extern s32 D_L05_001B1350[] __attribute__((sda));
extern s32 D_L05_001B1350_gp[] SDATA(D_L05_001B1350);
extern s32 D_L05_001B13F8[] SDATA(D_L05_001B13F8);

/* MenuY with label_y's two dead handle tests, for the two sprite rows (allowed by owner ruling,
   7 November 2026, as the dead-test helper). The tests do not change the result; they end blocks
   that allocation and both scheduling passes see. */
static __inline__ s32 MenuSpriteY(void *handle, f32 y, f32 adjustment) {
    f32 scaled = y * D_L05_001B2D84 + 0.5f;
    s32 result;
    void *copy;
    if (D_L05_001B2D80 == 1)
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
    f32 scaled = y * D_L05_001B2D84 + 0.5f;
    if (D_L05_001B2D80 == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

/* label_y: the accepted HUD label helper (src/levels/10_hrugis_cloud/L10_00421790-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
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

/* label_y2: label_y with only one of its two dead handle tests (allowed by owner ruling,
   9 November 2026; definition as in nonmatching/game/func_002D3FA0.c). */
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}

s32 func_L05_0041EF00(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 n;
    s32 r, remainder, color, blink, x, headerX, reward;
    char *text;

    center = func_00283CE0(D_001A7340) * 0.5f;
    if (D_L05_001A8F00) return 1;
    if (D_L05_001A904C) {
    D_L05_001B1F64 = 0;
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x45);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L05_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x44);
    func_00300968((void *)r, center, (f32)label_y((void *)r, 200.0f, D_L05_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
    remainder = D_L05_001B2048 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = func_00283D38(0x80FFDE8D, 0x60442D00, pulse);
    color = (D_00138180.buttons & 0x2000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (D_00138180.buttons & 0x8000) ? 0x80007FFF : blink;
    r = func_00336D50(D_L05_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuSpriteY((void *)r, 291.0f, 2.0f);
    func_00300A00((char *)r, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    func_00115DA8(buf, func_00288FB8(0x2F72), D_L05_001B13EC + 1);
    headerX = func_00283CF0(center);
    { s32 len;
    len = func_001157AC(buf);
    func_0027FBD8(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = func_00283CF0(center);
    switch (D_L05_001B13EC) {
    case 0:
        text = func_00288FB8(0x2FD6);
        {
            s32 row = MenuY(101.0f, -2.0f);
            func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
        }
        text = func_00288FB8(0x2FDB);
        {
            s32 len;
            s32 row;
            row = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
            len = func_001157AC(text);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L05_001B1350_gp[0];
            if (index >= 3) index = 2;
            reward = D_L05_001B13F8[index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        {
            s32 len;
            s32 row;
            do {
                func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
                row = label_y(buf, 242.0f, D_L05_001B2D84, 0.5f, 1);
            } while (0);
            len = func_001157AC(buf);
            func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
        }
        }
        func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        break;
    case 1:
        if (D_L05_001B1350_gp[0]) {
            text = func_00288FB8(0x2FD8);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FAA8(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FDD);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L05_001B1350[1];
                if (index >= 3) index = 2;
                reward = D_L05_001B1404[index];
            }
            if (D_001A7A0A) reward *= 10;
            n = func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y2((void *)n, 242.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L05_001B1350_gp[0] && D_L05_001B1350[1]) {
            text = func_00288FB8(0x2FD7);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FDC);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L05_001B1350[2];
                if (index >= 3) index = 2;
                reward = D_L05_001B1410[index];
            }
            if (D_001A7A0A) reward *= 10;
            n = func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y2((void *)n, 242.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_0027FBD8(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L05_001B1350_gp[0] && D_L05_001B1350[1] && D_L05_001B1350[2]) {
            text = func_00288FB8(0x2FDA);
            {
                s32 row = MenuY(101.0f, -2.0f);
                func_0027FB40(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = func_00288FB8(0x2FDF);
            {
                s32 len;
                s32 row;
                row = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
            }
            {
                s32 index = D_L05_001B1350[3];
                if (index >= 3) index = 2;
                reward = D_L05_001B141C[index];
            }
            if (D_001A7A0A) reward *= 10;
            func_00115DA8(buf, func_00288FB8(0x2FE0), reward);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 242.0f, D_L05_001B2D84, 0.5f, 1);
                len = func_001157AC(buf);
                func_L05_00303000(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            func_0027F5B8(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, func_00288FB8(0x2F3F), -1);
        } else {
            text = func_00288FB8(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, D_L05_001B2D84, 0.5f, 1);
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
