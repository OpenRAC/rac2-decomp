/* func_PAL_L15_004334B0, the PAL copy of func_L15_0042E1B0: the same C, where rename func_L15_00431590 becomes func_PAL_L15_004371B0; rename func_002ED578 becomes func_PAL_002EE490; rename func_L05_003263F8 becomes func_PAL_L05_00328198; rename func_L00_0030CF60 becomes func_PAL_0029C7F0. */
#include "common.h"

/* func_PAL_L15_004334B0 (DrawGornStageHud): the Gorn stage HUD, ported from func_L10_00421790
   (L10_00421790-g8.c). The mission text for the current stage, the ship's health and ammo bars,
   the weapon icons and the three corner sprites.

   Every text and sprite label y goes through label_y, the HUD label idiom (see its comment). Its tests
   have no effect on the result and leave no instruction, but retail shows them: after each y
   conversion retail ends a block (the x and y conversions are made before it, the remaining draw
   arguments after it), and the display-mode compare holds the 1 that is set up at entry. */

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
    s32 count;
    u8 pad14[0x14];
    s32 health;
} HudMissionState;

/* The HUD object's variables: the health bar blinks while health is low. */
typedef struct {
    u8 pad00[0x34];
    s32 blinkTimer;
    s32 blinkOn;
} HudBlinkVars;

extern u8 *D_L15_001B1580 __attribute__((sda));
extern s32 D_L15_001B1530 __attribute__((sda));
extern s32 D_L15_001B1638 __attribute__((sda));
extern s32 D_L15_001B1620 __attribute__((sda));
extern s32 D_L15_001B15B0 __attribute__((sda));
extern s32 D_L15_001B15A4 __attribute__((sda));
extern void *D_L15_001B1560 __attribute__((sda));
extern void *D_L15_001B1564 __attribute__((sda));
extern void *D_L15_001B1568 __attribute__((sda));
extern void *D_L15_001B156C __attribute__((sda));
extern void *D_L15_001B1570 __attribute__((sda));
extern void *D_L15_001B1574 __attribute__((sda));
extern u8 *D_L15_001A904C MACRO_ADDR;
extern s32 D_L15_001B163C MACRO_ADDR;
extern s32 D_L15_001B1624 MACRO_ADDR;
extern f32 D_L15_001B2E84;
extern s32 D_L15_001B2E80 MACRO_ADDR;
extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_L15_001B3698 MACRO_ADDR;
extern HudMissionState D_L15_00221E10;
extern f32 D_L15_001AC560, D_L15_001AC564;
extern char D_L15_001B1640[], D_L15_001B1648[], D_L15_001B1690[];
extern Block D_L15_001B1660, D_L15_001B1670, D_L15_001B1680;
extern HudWeapon D_L15_0029FD80[];

extern void func_PAL_L15_004371B0(s32, s32, s32, s32);
extern void *func_L05_00379ED0(s32);
extern s32 func_L10_0037D200(void *);
extern s32 func_L15_00381CF0(void *);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
extern s32 func_00282948(s32 *);
extern void func_PAL_002EE490(s32, s32 *, s32 *, s32 *);
extern void *func_00336D50(void *, s32);
extern f32 func_00283CE0(s32);
/* (sprite, x, y, color, scale, angle): the EE passes the integer and float arguments in their own
   register banks. */
extern void func_00300968(void *, f32, f32, s32, f32, f32);
extern s32 func_002ED8A0(s32);
extern s32 func_00283D38(u32, u32, f32);
extern void func_0027EAE8(s32, s32, s32, s32, s32, u32 *);
extern void *func_0028E588(s32, s32);
extern void func_0028EA58(void *, s32, s32, s32, s32, Block *);
extern void func_0027F538(s32, s32, u64, char *, s32);
extern void func_PAL_L05_00328198(s32);
extern s32 func_L05_00324DB8(void);
extern void func_PAL_0029C7F0(void), func_L05_0037A5F8(void);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L15_001B2E84 + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

/* label_y, the HUD label idiom for text and sprite label y coordinates (accepted 7 November 2026; one
   shared definition, `active` the literal 1 at every call). Its tests do not change the result: flow
   deletes their stores and jump2 their jumps, but only after allocation and both scheduling passes,
   which see the block they end. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L15_001B2E80;
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

s32 func_PAL_L15_004334B0(void) {
    char text[128];
    char *label;
    u32 colors[2], colors2[2];
    Block b0, b1, b2;
    s32 a, b, c, idx, newidx, color, textX;
    HudBlinkVars *data = *(HudBlinkVars **)(D_L15_001B1580 + 0x68);
    f32 x, y, ratio, tmp, base, end, fill, tweenColor;
    void *sprite0, *sprite2;

    switch (D_L15_001B1530) {
    case 0: {
        s32 textX2;

        func_PAL_L15_004371B0(0, 1, 0, 1);
        label = func_00288FB8(0x10e9);
        func_00115DA8(text, D_L15_001B1640, label, func_L10_0037D200(func_L05_00379ED0(0x1211)));
        textX2 = D_L15_001B1638 - 60;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L15_001B163C - 8, D_L15_001B2E84, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 1: {
        s32 textX2;

        func_PAL_L15_004371B0(0, 1, 0, 1);
        label = func_00288FB8(0x10e9);
        func_00115DA8(text, D_L15_001B1640, label, D_L15_00221E10.count);
        textX2 = D_L15_001B1638 - 60;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L15_001B163C - 8, D_L15_001B2E84, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 2: {
        s32 textX2;

        func_PAL_L15_004371B0(0, 1, 0, 1);
        label = func_00288FB8(0x10e9);
        func_00115DA8(text, D_L15_001B1640, label, func_L15_00381CF0(func_L05_00379ED0(0x1211)));
        textX2 = D_L15_001B1638 - 60;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L15_001B163C - 8, D_L15_001B2E84, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 3: {
        f32 half = 0.5f;
        s32 textX2;

        func_PAL_L15_004371B0(1, 1, 0, 1);
        label = func_00288FB8(0x10ef);
        func_00115DA8(text, D_L15_001B1640, label, D_L15_001B15A4);
        textX = D_L15_001B1638 - 60;
        func_0027F5B8(textX, label_y((void *)textX, D_L15_001B163C - 8, D_L15_001B2E84, half, 1), 0x80808080, text, 128);
        func_PAL_002EE490(D_L15_001B3698, &a, &b, &c);
        label = func_00288FB8(0xea8);
        func_00115DA8(text, D_L15_001B1648, label, a, b, c);
        textX2 = D_L15_001B1620 - 80;
        func_0027F5B8(textX2, label_y((void *)textX2, D_L15_001B1624 - 8, D_L15_001B2E84, half, 1), 0x80808080, text, 128);
        break;
    }
    }

    if (D_L15_001A904C) {
        D_L15_001B1560 = func_00336D50(D_L15_001A904C + 0x8710, 128);
        D_L15_001B1564 = func_00336D50(D_L15_001A904C + 0x8710, 129);
        D_L15_001B1568 = func_00336D50(D_L15_001A904C + 0x8710, 130);
        D_L15_001B156C = func_00336D50(D_L15_001A904C + 0x8710, 131);
        D_L15_001B1570 = func_00336D50(D_L15_001A904C + 0x8710, 132);
        D_L15_001B1574 = func_00336D50(D_L15_001A904C + 0x8710, 133);
        x = func_00283CE0(D_001A7340) * 0.5f;
        y = screen_coord(D_L15_001B2E80, 200.0f, 4.0f);
        func_00300968(D_L15_001B1560, x, y, 0x60442d00, 1.0f, 0.0f);
        func_00300968(D_L15_001B1564, x, y, 0x55f0c070, 1.0f, 0.0f);

        /* The weapon's level gauge, red to green in one, two or three segments. */
        idx = func_002ED8A0(6);
        ratio = func_00283CE0(D_L15_0029FD80[idx].value) / func_00283CE0(D_L15_0029FD80[idx].maxLevel);
        switch (idx) {
        case 6:
            if (ratio > 0.0f) {
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio);
                func_00300968(D_L15_001B156C, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 12:
            if (ratio > 0.5f) {
                ratio -= 0.5f;
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio + ratio);
                func_00300968(D_L15_001B1570, x, y, (s32)tweenColor, 1.0f, 0.0f);
                func_00300968(D_L15_001B156C, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio + ratio);
                func_00300968(D_L15_001B156C, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 14:
            if (ratio > 0.6666667f) {
                ratio -= 0.6666667f;
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio * 3.0f);
                func_00300968(D_L15_001B1574, x, y, (s32)tweenColor, 1.0f, 0.0f);
                func_00300968(D_L15_001B1570, x, y, 0x8000ff00, 1.0f, 0.0f);
                func_00300968(D_L15_001B156C, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.33333334f) {
                ratio -= 0.33333334f;
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio * 3.0f);
                func_00300968(D_L15_001B1570, x, y, (s32)tweenColor, 1.0f, 0.0f);
                func_00300968(D_L15_001B156C, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = func_00283D38(0x800000ff, 0x8000ff00, ratio * 3.0f);
                func_00300968(D_L15_001B156C, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        }

        /* Health bar: blinks below 30%. */
        fill = D_L15_00221E10.health * 0.01f;
        if (fill > 0.3f) {
            data->blinkOn = 1;
        } else if (func_00282948(&data->blinkTimer)) {
            data->blinkTimer = 4;
            data->blinkOn ^= 1;
        }
        colors[1] = func_00283D38(0x800000ff, 0x8000ff00, fill);
        colors[0] = 0x800000ff;
        tmp = fill * 200.0f + 156.0f;
        if (data->blinkOn)
            func_0027EAE8(156, 14, (s32)tmp, 27, 1, colors);

        /* Ammo bar. */
        idx = func_002ED8A0(7);
        ratio = func_00283CE0(D_L15_0029FD80[idx].value);
        fill = ratio / func_00283CE0(D_L15_0029FD80[idx].maxAmmo);
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

        /* Weapon icons and the fill count. */
        b0 = D_L15_001B1660;
        b1 = D_L15_001B1670;
        b2 = D_L15_001B1680;
        func_0028EA58(func_0028E588(0xea97, 1), 21, 7, 30, 30, &b1);
        func_0028EA58(func_0028E588(0xea97, 0), 21, 7, 30, 30, &b0);
        func_0028EA58(func_0028E588(0xea97, D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].icon), 21, 7, 30, 30, &b2);
        func_0028EA58(func_0028E588(0xea97, 1), 462, 9, 30, 30, &b1);
        func_0028EA58(func_0028E588(0xea97, D_L15_0029FD80[func_002ED8A0(7)].icon), 462, 9, 30, 30, &b2);
        func_00115DA8(text, D_L15_001B1690, D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].value,
                      D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].maxAmmo);
        func_0027F538(67, 5, 0x80808080, text, 128);

        /* Weapon switch. */
        func_PAL_L05_00328198(2);
        newidx = func_L05_00324DB8();
        if (newidx >= 0) {
            D_L15_0029FD80[func_002ED8A0(D_L15_001B15B0)].active = 0;
            D_L15_001B15B0 = newidx;
            D_L15_0029FD80[func_002ED8A0(newidx)].active = 1;
        }
        func_00300968(D_L15_001B1568, x, y, 0x80f0f0f0, 1.0f, 0.0f);
    }

    func_PAL_0029C7F0();
    sprite0 = func_00336D50(D_L15_001A904C + 0x8710, 186);
    /* data, done with, holds the second sprite. */
    data = func_00336D50(D_L15_001A904C + 0x8710, 187);
    sprite2 = func_00336D50(D_L15_001A904C + 0x8710, 188);
    func_00300968(sprite0, D_L15_001AC560 + 4.0f, label_y(sprite0, D_L15_001AC564 + 4.0f, D_L15_001B2E84, 0.5f, 1), 0x60442d00, 0.8f, 0.0f);
    func_00300968(data, D_L15_001AC560 + 4.0f, label_y(data, D_L15_001AC564 + 4.0f, D_L15_001B2E84, 0.5f, 1), 0x60241700, 0.8f, 0.0f);
    func_00300968(sprite2, D_L15_001AC560 + 4.0f, label_y(sprite2, D_L15_001AC564 + 4.0f, D_L15_001B2E84, 0.5f, 1), 0x55f0c070, 0.8f, 0.0f);
    func_L05_0037A5F8();
    return 1;
}
