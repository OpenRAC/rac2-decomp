#include "common.h"

/* func_L05_0041DF58 (DrawFeltzinMissionHud): the Feltzin System mission HUD. The mission text for
   the current stage, the ship's health and ammo bars, the weapon icons and the three corner sprites.
   Ported from the matched func_L10_00421790 (L10_00421790-g8.c), the same routine for Hrugis Cloud.

   Every text and sprite label y goes through label_y, the HUD label idiom (dead-test helper, allowed
   by owner ruling). Case 1's second label passes the stage global, which is 1 in that case, as
   `active` (a value holding 1, as allowed by owner ruling): with the literal 1, both of case 0's and
   case 1's identical second-draw tails reach jump2 with equal RTL and are cross-jumped into one;
   retail keeps them apart. */

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
        /* active is the switch value, 1 in this case (allowed by owner ruling, 2026-11-09). */
        func_0027F5B8(textX2, label_y((void *)textX2, D_L05_001B142C - 8, D_L05_001B2D84, half, D_L05_001B1360), 0x80808080, text, 128);
        break;
    }
    case 2: {
        s32 textX2;

        func_L05_00421B98(0, 1, 0, 1);
        label = func_00288FB8(0x31d1);
        func_00115DA8(text, D_L05_001B1448, label, D_L05_00221D10.objectives);
        textX2 = D_L05_001B1440 - 60;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L05_001B1444 - 8, D_L05_001B2D84, 0.5f, 1), 0x80808080, text, 128);
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
