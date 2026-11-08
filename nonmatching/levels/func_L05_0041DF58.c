/* 8 November 2026, Sonnet round (o12, lesson 48 sweep): scripted local-cc1 sweep of every simple statement (incl. label_y's) moved up/down 1..6 lines, also across do-group edges (540+216 variants), plus 964 pairs of neutral moves: none below 2 rows. */
/* 8 November 2026, Sonnet round (o10): still 2 rows. sched2 -dR deps at the 0041E20C tie (after lw a3): a0=sp has 4 forward deps (call, textX2's a0 output, LOOP_END barrier via its sp use, next call), a1 lo_sum 3, a2 3; ranks tie on priority/class, so dep count picks a0. Retail needs count(a1) >= count(a0) > count(a2). Group ending before label_y or before textX2 (3 forms) or no group: 883 bytes; textX2 after label_y: 8 rows; label inline / &text[0]: no gain. 25-minute permuter (-j2): nothing below base. */
/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_002ED578 is declared void but src/game/002ED578.c returns int: corrected, 5 -> 9 rows (worse). func_00300968 is declared (void *, f32, f32, s32, f32, f32) but src/game/00300618.c:305 is (char *, int flags, f32 x4): calls reordered to (object, colour, x, y, 1.0f, 0.0f) give 2 -> 18 rows (argument set-up order changes). The matched sibling L05_00420360-g8.c carries the same extern spelling as this note. */
/*
 * 8 November 2026 (Sonnet round): best now 3516/3516 bytes, 2 swapped insns (0041E20C/10: retail
 * addiu a1,0x1448 before daddu a0,sp at case 2's func_00115DA8 call); needs cflags line
 * "-O2 -G8 -ffunction-sections -malign-loops=2" (else a .p2align nop). Case 2 below: body in a
 * do { } while (0) group, label_y result in a local y, handle `text` (tests fold in jump1, so no old
 * label; the LOOP_END note is the sched2 barrier and jump2 makes a new label, so case 1 no longer
 * merges into case 0). Why: flow2 deletes label_y's mode test and second handle test but keeps the
 * first (its fall block still holds the second), so label 447 survives to jump2. Tried: do-group
 * starting at each statement (2-14 rows), two groups, handle colors (same), &global/fmt (not folded),
 * handle (void *)textX2 in the group (3496), half local (3440); permuter 25 min from this C: no gain.
 * 8 November 2026 (re-measure): still 3496/3516, 0/1 places, same single 5-insn cross-jump.
 * From the jump2/sched2/greg dumps: jump2 sends case 0's and case 1's second-draw calls into
 * case 2's call (label before `ori a2`), then merges case 1's tail [mul.s, add.s, fix, a0=v0]
 * into case 0's (4 insns >= the minimum 2). All seven label_y blocks except case 2 get mode in
 * a0 (local-alloc's fake lifetime: mode's load sits right after the float that frees v1) and
 * fix scratch v1 (reload takes the first free call-used reg); case 2 gets mode v1, scratch v0.
 * So a different scratch would need mode in v1, but then x's copy preference gives it a0
 * (visible `addiu a0`, as in case 2). Tried, no change: a `y2` local for the case 1 label_y
 * result; case 0's second draw with its own block-local x; handle passed as the expression
 * (void *)(D_L05_001B1428 - 80). Handle `text`: tests fold away (3544). `active` 2: 3520 (fix
 * result goes to v1 plus a move to a1). Open: which RTL difference kept retail's two tails apart.
 * 8 November 2026 (round 2): the L10 donor's switch is a different shape (score/object calls),
 * so it gives no evidence for these tails. Cause found in the EE gcc jump.c: cross-jumping only
 * walks jump_chain for a label whose uid is < max_uid (a label that existed before jump2).
 * Here case 0's call merges into case 2's call at case 2's handle-test label (code_label 447, right
 * before `ori a2`). That label existed before jump2, so case 1 then finds case 0's jump on its
 * chain and merges. In retail the label before case 2's `ori a2` must have been new (made by
 * jump2), so no chain search happened; the C has to stop that label from directly preceding
 * a2. Tried with no change: case 2 with no scope block, or with a function-level x; case 0 in its
 * own block with its own x. Case 2 handle 0 or `text` folds the tests: no merges, 3528, 858 rows.
 *
 * 7 November 2026 (donor port): best check.py, USA v1.01 (level 05): 3496/3516 bytes, 0/1 places.
 * Ported from matched func_L10_00421790 (src/levels/10_hrugis_cloud/L10_00421790-g8.c, same
 * routine, label_y idiom, default -g8 flags). Build as its own unit
 * src/levels/05_feltzin_system/L05_0041DF58-g8.c (no cflags line) and replace the INCLUDE_ASM in
 * L05_00314E28.c with a pointer comment.
 * Aligned diff (mnemonic+registers, relocations masked): 874 of 879 retail rows line up; the only
 * difference is 0041E1C8..0041E1E0, the tail of case 1's second draw. Retail keeps
 * `addiu v0,v0,-0x50; mul.s; add.s; cvt.w.s; mfc1 a1; b .L0041E25C; daddu a0,v0`; this C
 * cross-jumps those five insns into case 0's identical tail (`b` back 0x44 insns).
 * Why (from the compiler source, jump.c): after sched2 the cross-jump pass sends case 0's and case 1's
 * final calls into case 2's call at the old label_y label before `ori a2`, so both jumps share that
 * label's jump_chain and case 1 then merges with case 0. Retail does not, so their patterns differed
 * at that point. The only invisible field is fix_truncsfsi2's SI scratch (v1 in both here, because
 * mode sits in a0 and x in v0); mode in v1 for one draw would give scratch a0 and stop the merge.
 * A diagnostic `active` 2 in case 1's second draw stops the merge (not landable).
 * Tried with no change (still 6 rows): `half` local or literal in cases 0/1, textX vs textX2 in
 * either draw, an inline x expression, a `fmt` local in case 0/1, a `row` local for the y value,
 * label_y with mode read after result. Plain y (no label_y) in case 2: 33 rows.
 * Needed and kept: case 2 uses its own textX2 (x straight into a0); cases 1 and 3 use `half` and
 * textX2 for the second draw (fixes the a3/a0 order at 0041E14C and 0041E2EC).
 * Older drafts (task v1866, 31 October 2026: 3520/3516, 667/880 masked rows) are superseded.
 */
#include "common.h"

typedef struct { u8 bytes[16]; } Block;

typedef struct {
    s32 active;
    u8 pad04[8];
    s32 maxLevel;
    s32 maxAmmo;
    s32 value;
    u8 pad18[4];
    s16 icon;
    u8 pad1E[10];
} HudWeapon;

typedef struct {
    u8 pad00[0x10];
    s32 objectives;
    s32 wave;
    u8 pad18[0x10];
    s32 health;
} HudMissionState;

typedef struct {
    u8 pad00[0x34];
    s32 blinkTimer;
    s32 blinkOn;
    u8 pad3C[8];
    s32 time;
} HudBlinkVars;

extern u8 *D_L05_001B13B0 __attribute__((sda));
extern s32 D_L05_001B1360 __attribute__((sda));
extern s32 D_L05_001B1438 __attribute__((sda));
extern s32 D_L05_001B1440 __attribute__((sda));
extern s32 D_L05_001B1428 __attribute__((sda));
extern s32 D_L05_001B13DC __attribute__((sda));
extern s32 D_L05_001B13D0 __attribute__((sda));
extern void *D_L05_001B1390 __attribute__((sda));
extern void *D_L05_001B1394 __attribute__((sda));
extern void *D_L05_001B1398 __attribute__((sda));
extern void *D_L05_001B139C __attribute__((sda));
extern void *D_L05_001B13A0 __attribute__((sda));
extern void *D_L05_001B13A4 __attribute__((sda));
extern u8 *D_L05_001A904C MACRO_ADDR;
extern s32 D_L05_001B143C MACRO_ADDR;
extern s32 D_L05_001B1444 MACRO_ADDR;
extern s32 D_L05_001B142C MACRO_ADDR;
extern f32 D_L05_001B2D84;
extern s32 D_L05_001B2D80 MACRO_ADDR;
extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_L05_001B3550 MACRO_ADDR;
extern HudMissionState D_L05_00221D10;
extern f32 D_L05_001AC4E0, D_L05_001AC4E4;
extern char D_L05_001B1448[], D_L05_001B1450[], D_L05_001B1498[];
extern Block D_L05_001B1468, D_L05_001B1478, D_L05_001B1488;
extern HudWeapon D_L05_002A1800[];

extern void func_L05_00421B98(s32, s32, s32, s32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
extern s32 func_00282948(s32 *);
extern void func_002ED578(s32, s32 *, s32 *, s32 *);
extern void *func_00336D50(void *, s32);
extern f32 func_00283CE0(s32);
extern void func_00300968(void *, f32, f32, s32, f32, f32);
extern s32 func_002ED8A0(s32);
extern s32 func_00283D38(u32, u32, f32);
extern void func_0027EAE8(s32, s32, s32, s32, s32, u32 *);
extern void *func_0028E588(s32, s32);
extern void func_0028EA58(void *, s32, s32, s32, s32, Block *);
extern void func_0027F538(s32, s32, u64, char *, s32);
extern void func_L05_003263F8(s32);
extern s32 func_L05_00324DB8(void);
extern void func_L00_0030CF60(void), func_L05_0037A5F8(void);

static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L05_001B2D84 + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

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

s32 func_L05_0041DF58(void) {
    char text[128];
    char *label;
    u32 colors[2], colors2[2];
    Block b0, b1, b2;
    s32 a, b, c, idx, newidx, color, textX;
    HudBlinkVars *data = *(HudBlinkVars **)(D_L05_001B13B0 + 0x68);
    f32 x, y, ratio, tmp, base, end, fill, tweenColor;
    void *sprite0, *sprite2;

    switch (D_L05_001B1360) {
    case 0:
        func_L05_00421B98(0, 1, 1, 1);
        label = func_00288FB8(0x31d1);
        func_00115DA8(text, D_L05_001B1448, label, D_L05_00221D10.objectives);
        textX = D_L05_001B1438 - 60;
        func_0027F5B8(textX, label_y((void *)textX, D_L05_001B143C - 8, D_L05_001B2D84, 0.5f, 1), 0x80808080, text, 128);
        label = func_00288FB8(0x31d2);
        func_00115DA8(text, D_L05_001B1448, label, D_L05_00221D10.wave + 1);
        textX = D_L05_001B1440 - 60;
        func_0027F5B8(textX, label_y((void *)textX, D_L05_001B1444 - 8, D_L05_001B2D84, 0.5f, 1), 0x80808080, text, 128);
        break;
    case 1: {
        f32 half = 0.5f;
        s32 textX2;

        func_L05_00421B98(1, 1, 0, 1);
        label = func_00288FB8(0x31d4);
        func_00115DA8(text, D_L05_001B1448, label, D_L05_00221D10.objectives);
        textX = D_L05_001B1440 - 60;
        func_0027F5B8(textX, label_y((void *)textX, D_L05_001B1444 - 8, D_L05_001B2D84, half, 1), 0x80808080, text, 128);
        func_002ED578(data->time, &a, &b, &c);
        label = func_00288FB8(0x2f83);
        func_00115DA8(text, D_L05_001B1450, label, a, b, c);
        textX2 = D_L05_001B1428 - 80;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L05_001B142C - 8, D_L05_001B2D84, half, 1), 0x80808080, text, 128);
        break;
    }
    case 2: {
        s32 textX2, y;

        do {
            func_L05_00421B98(0, 1, 0, 1);
            label = func_00288FB8(0x31d1);
            func_00115DA8(text, D_L05_001B1448, label, D_L05_00221D10.objectives);
            textX2 = D_L05_001B1440 - 60;
            y = label_y(text, D_L05_001B1444 - 8, D_L05_001B2D84, 0.5f, 1);
        } while (0);
        func_0027F5B8(textX2, y, 0x80808080, text, 128);
        break;
    }
    case 3: {
        f32 half = 0.5f;
        s32 textX2;

        func_L05_00421B98(1, 1, 0, 1);
        label = func_00288FB8(0x31d7);
        func_00115DA8(text, D_L05_001B1448, label, D_L05_001B13D0);
        textX = D_L05_001B1440 - 60;
        func_0027F5B8(textX, label_y((void *)textX, D_L05_001B1444 - 8, D_L05_001B2D84, half, 1), 0x80808080, text, 128);
        func_002ED578(D_L05_001B3550, &a, &b, &c);
        label = func_00288FB8(0x2f83);
        func_00115DA8(text, D_L05_001B1450, label, a, b, c);
        textX2 = D_L05_001B1428 - 80;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L05_001B142C - 8, D_L05_001B2D84, half, 1), 0x80808080, text, 128);
        break;
    }
    }

    if (D_L05_001A904C) {
        D_L05_001B1390 = func_00336D50(D_L05_001A904C + 0x8710, 128);
        D_L05_001B1394 = func_00336D50(D_L05_001A904C + 0x8710, 129);
        D_L05_001B1398 = func_00336D50(D_L05_001A904C + 0x8710, 130);
        D_L05_001B139C = func_00336D50(D_L05_001A904C + 0x8710, 131);
        D_L05_001B13A0 = func_00336D50(D_L05_001A904C + 0x8710, 132);
        D_L05_001B13A4 = func_00336D50(D_L05_001A904C + 0x8710, 133);
        x = func_00283CE0(D_001A7340) * 0.5f;
        y = screen_coord(D_L05_001B2D80, 200.0f, 4.0f);
        func_00300968(D_L05_001B1390, x, y, 0x60442d00, 1.0f, 0.0f);
        func_00300968(D_L05_001B1394, x, y, 0x55f0c070, 1.0f, 0.0f);

        idx = func_002ED8A0(6);
        ratio = func_00283CE0(D_L05_002A1800[idx].value) / func_00283CE0(D_L05_002A1800[idx].maxLevel);
        switch (idx) {
        case 6:
            if (ratio > 0.0f) {
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio);
                func_00300968(D_L05_001B139C, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 12:
            if (ratio > 0.5f) {
                ratio -= 0.5f;
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio + ratio);
                func_00300968(D_L05_001B13A0, x, y, (s32)tweenColor, 1.0f, 0.0f);
                func_00300968(D_L05_001B139C, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio + ratio);
                func_00300968(D_L05_001B139C, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 14:
            if (ratio > 0.6666667f) {
                ratio -= 0.6666667f;
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio * 3.0f);
                func_00300968(D_L05_001B13A4, x, y, (s32)tweenColor, 1.0f, 0.0f);
                func_00300968(D_L05_001B13A0, x, y, 0x8000ff00, 1.0f, 0.0f);
                func_00300968(D_L05_001B139C, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.33333334f) {
                ratio -= 0.33333334f;
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio * 3.0f);
                func_00300968(D_L05_001B13A0, x, y, (s32)tweenColor, 1.0f, 0.0f);
                func_00300968(D_L05_001B139C, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio * 3.0f);
                func_00300968(D_L05_001B139C, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        }

        fill = D_L05_00221D10.health * 0.01f;
        if (fill > 0.3f) {
            data->blinkOn = 1;
        } else if (func_00282948(&data->blinkTimer)) {
            data->blinkTimer = 5;
            data->blinkOn ^= 1;
        }
        colors[1] = func_00283D38(0x800000ff, 0x8000ff00, fill);
        colors[0] = 0x800000ff;
        tmp = fill * 200.0f + 156.0f;
        if (data->blinkOn)
            func_0027EAE8(156, 14, (s32)tmp, 27, 1, colors);

        idx = func_002ED8A0(7);
        ratio = func_00283CE0(D_L05_002A1800[idx].value);
        fill = ratio / func_00283CE0(D_L05_002A1800[idx].maxAmmo);
        color = func_00283D38(0x800000ff, 0x8000ff00, fill);
        base = func_00283CE0(450);
        end = func_00283CE0(386);
        end -= func_00283CE0(450);
        colors2[0] = 0x800000ff;
        colors2[1] = color;
        end = end * fill;
        tmp = base + end;
        if (fill > 0.0f)
            func_0027EAE8(450, 8, (s32)tmp, 19, 1, colors2);

        b0 = D_L05_001B1468;
        b1 = D_L05_001B1478;
        b2 = D_L05_001B1488;
        func_0028EA58(func_0028E588(0xea97, 1), 21, 7, 30, 30, &b1);
        func_0028EA58(func_0028E588(0xea97, 0), 21, 7, 30, 30, &b0);
        func_0028EA58(func_0028E588(0xea97, D_L05_002A1800[func_002ED8A0(D_L05_001B13DC)].icon), 21, 7, 30, 30, &b2);
        func_0028EA58(func_0028E588(0xea97, 1), 462, 9, 30, 30, &b1);
        func_0028EA58(func_0028E588(0xea97, D_L05_002A1800[func_002ED8A0(7)].icon), 462, 9, 30, 30, &b2);
        func_00115DA8(text, D_L05_001B1498, D_L05_002A1800[func_002ED8A0(D_L05_001B13DC)].value,
                      D_L05_002A1800[func_002ED8A0(D_L05_001B13DC)].maxAmmo);
        func_0027F538(67, 5, 0x80808080, text, 128);

        func_L05_003263F8(2);
        newidx = func_L05_00324DB8();
        if (newidx >= 0) {
            D_L05_002A1800[func_002ED8A0(D_L05_001B13DC)].active = 0;
            D_L05_001B13DC = newidx;
            D_L05_002A1800[func_002ED8A0(newidx)].active = 1;
        }
        func_00300968(D_L05_001B1398, x, y, 0x80f0f0f0, 1.0f, 0.0f);
    }

    func_L00_0030CF60();
    sprite0 = func_00336D50(D_L05_001A904C + 0x8710, 186);
    data = func_00336D50(D_L05_001A904C + 0x8710, 187);
    sprite2 = func_00336D50(D_L05_001A904C + 0x8710, 188);
    func_00300968(sprite0, D_L05_001AC4E0 + 4.0f, label_y(sprite0, D_L05_001AC4E4 + 4.0f, D_L05_001B2D84, 0.5f, 1), 0x60442d00, 0.8f, 0.0f);
    func_00300968(data, D_L05_001AC4E0 + 4.0f, label_y(data, D_L05_001AC4E4 + 4.0f, D_L05_001B2D84, 0.5f, 1), 0x60241700, 0.8f, 0.0f);
    func_00300968(sprite2, D_L05_001AC4E0 + 4.0f, label_y(sprite2, D_L05_001AC4E4 + 4.0f, D_L05_001B2D84, 0.5f, 1), 0x55f0c070, 0.8f, 0.0f);
    func_L05_0037A5F8();
    return 1;
}
