#include "common.h"

/* func_L10_00421790 (DrawHrugisMissionHud): the Hrugis Cloud mission HUD. The mission text for the
   current stage, the ship's health and ammo bars, the weapon icons and the three corner sprites.

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
    u8 pad00[0x28];
    s32 health;
} HudMissionState;

/* The HUD object's variables: the health bar blinks while health is low. */
typedef struct {
    u8 pad00[0x34];
    s32 blinkTimer;
    s32 blinkOn;
} HudBlinkVars;

extern u8 *D_L10_001B13F0 __attribute__((sda));
extern s32 D_L10_001B13A0 __attribute__((sda));
extern s32 D_L10_001B13F4 __attribute__((sda));
extern s32 D_L10_001B13F8 __attribute__((sda));
extern s32 D_L10_001B13FC __attribute__((sda));
extern s32 D_L10_001B14C0 __attribute__((sda));
extern s32 D_L10_001B14B8 __attribute__((sda));
extern s32 D_L10_001B14A8 __attribute__((sda));
extern s32 D_L10_001B1428 __attribute__((sda));
extern s32 D_L10_001B141C __attribute__((sda));
extern void *D_L10_001B13D0 __attribute__((sda));
extern void *D_L10_001B13D4 __attribute__((sda));
extern void *D_L10_001B13D8 __attribute__((sda));
extern void *D_L10_001B13DC __attribute__((sda));
extern void *D_L10_001B13E0 __attribute__((sda));
extern void *D_L10_001B13E4 __attribute__((sda));
extern u8 *D_L10_001A904C MACRO_ADDR;
extern s32 D_L10_001B14C4 MACRO_ADDR;
extern s32 D_L10_001B14BC MACRO_ADDR;
extern s32 D_L10_001B14AC MACRO_ADDR;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80 MACRO_ADDR;
extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_L10_001B3550 MACRO_ADDR;
extern HudMissionState D_L10_00221CD0;
extern f32 D_L10_001AC5E0, D_L10_001AC5E4;
extern char D_L10_001B14C8[], D_L10_001B14D0[], D_L10_001B1518[];
extern Block D_L10_001B14E8, D_L10_001B14F8, D_L10_001B1508;
extern HudWeapon D_L10_002A3C70[];

extern void func_L10_00424CD0(s32, s32, s32, s32);
extern void *func_L05_00379ED0(s32);
extern s32 func_L10_0037D200(void *);
extern s32 func_L05_0037B3A0(void *);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(s32, s32, u64, char *, s32);
extern s32 func_L10_004176A0(void), func_L10_004176B0(void);
extern void func_L00_0030DD70(char *, s32);
extern s32 func_00282948(s32 *);
extern void func_002ED578(s32, s32 *, s32 *, s32 *);
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
extern void func_L05_003263F8(s32);
extern s32 func_L05_00324DB8(void);
extern void func_L00_0030CF60(void), func_L05_0037A5F8(void);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L10_001B2D84 + 0.5f;

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
    int mode = D_L10_001B2D80;
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

/* Draws the mission HUD each frame: the mission text, the health and ammo bars, the weapon icons
   and the corner sprites. */
s32 func_L10_00421790(void) {
    char text[128];
    char *label;
    u32 colors[2], colors2[2];
    Block b0, b1, b2;
    s32 timePart0, timePart1, timePart2, score, idx, newidx, color, textX;
    void *object;
    HudBlinkVars *data = *(HudBlinkVars **)(D_L10_001B13F0 + 0x68);
    f32 x, y, ratio, barRight, base, end, fill, tweenColor;
    void *sprite0, *sprite2;

    switch (D_L10_001B13A0) {
    case 0:
        DrawFadingHudIconPairs(0, 1, 0, 1);
        object = FindLevelObjectByClassId(0xf85 /* moby class 3973 */);
        if (object)
            score = CountAliveGroupMobys(object);
        else
            score = 0;
        label = GetLocalizedString(0x31d8);
        Sprintf(text, D_L10_001B14C8, label, score);
        textX = D_L10_001B14C0 - 65;
        DrawTextMediumFont(textX, label_y((void *)textX, D_L10_001B14C4 - 8, D_L10_001B2D84, 0.5f, 1), 0x80808080, text, 128);
        if (TakeBossFlagA() && D_L10_001B13F4) {
            D_L10_001B13F4 = 0;
            D_L10_001B13F8 = 180;
        }
        if (TakeBossFlagB()) {
            D_L10_001B13F4 = 1;
            D_L10_001B13FC = 180;
        }
        if (D_L10_001B13F8)
            CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x31d9), -1);
        if (D_L10_001B13FC)
            CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x31da), -1);
        FastFloatHelperD(&D_L10_001B13F8);
        FastFloatHelperD(&D_L10_001B13FC);
        break;
    case 1: {
        f32 half = 0.5f;
        char *fmt;

        DrawFadingHudIconPairs(0, 1, 1, 1);
        label = GetLocalizedString(0x31db);
        fmt = D_L10_001B14C8;
        Sprintf(text, fmt, label, CountReadyListObjects(FindLevelObjectByClassId(0xf93 /* moby class 3987 */)));
        textX = D_L10_001B14B8 - 65;
        DrawTextMediumFont(textX, label_y((void *)textX, D_L10_001B14BC - 8, D_L10_001B2D84, half, 1), 0x80808080, text, 128);
        label = GetLocalizedString(0x31dc);
        Sprintf(text, fmt, label, CountReadyListObjects(FindLevelObjectByClassId(0xcbe /* moby class 3262 */)));
        textX = D_L10_001B14C0 - 65;
        DrawTextMediumFont(textX, label_y((void *)textX, D_L10_001B14C4 - 8, D_L10_001B2D84, half, 1), 0x80808080, text, 128);
        break;
    }
    case 2: {
        char *fmt;
        s32 textX2;

        DrawFadingHudIconPairs(0, 1, 0, 1);
        label = GetLocalizedString(0x31dd);
        fmt = D_L10_001B14C8;
        Sprintf(text, fmt, label, CountReadyListObjects(FindLevelObjectByClassId(0xf8e /* moby class 3982 */)));
        textX2 = D_L10_001B14C0 - 70;
        DrawTextMediumFont(textX2, label_y((void *)textX2, D_L10_001B14C4 - 8, D_L10_001B2D84, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 3: {
        f32 half = 0.5f;
        s32 textX2;

        DrawFadingHudIconPairs(1, 1, 0, 1);
        label = GetLocalizedString(0x31d7);
        Sprintf(text, D_L10_001B14C8, label, D_L10_001B141C);
        textX = D_L10_001B14C0 - 65;
        DrawTextMediumFont(textX, label_y((void *)textX, D_L10_001B14C4 - 8, D_L10_001B2D84, half, 1), 0x80808080, text, 128);
        SplitTimeIntoParts(D_L10_001B3550, &timePart0, &timePart1, &timePart2);
        label = GetLocalizedString(0x2f83);
        Sprintf(text, D_L10_001B14D0, label, timePart0, timePart1, timePart2);
        textX2 = D_L10_001B14A8 - 80;
        DrawTextMediumFont(textX2, label_y((void *)textX2, D_L10_001B14AC - 8, D_L10_001B2D84, half, 1), 0x80808080, text, 128);
        break;
    }
    }

    if (D_L10_001A904C) {
        D_L10_001B13D0 = FindTableEntryById(D_L10_001A904C + 0x8710, 128);
        D_L10_001B13D4 = FindTableEntryById(D_L10_001A904C + 0x8710, 129);
        D_L10_001B13D8 = FindTableEntryById(D_L10_001A904C + 0x8710, 130);
        D_L10_001B13DC = FindTableEntryById(D_L10_001A904C + 0x8710, 131);
        D_L10_001B13E0 = FindTableEntryById(D_L10_001A904C + 0x8710, 132);
        D_L10_001B13E4 = FindTableEntryById(D_L10_001A904C + 0x8710, 133);
        x = IntToFloat(gScreenWidth) * 0.5f;
        y = screen_coord(D_L10_001B2D80, 200.0f, 4.0f);
        DrawScaledObjectUniform(D_L10_001B13D0, x, y, 0x60442d00, 1.0f, 0.0f);
        DrawScaledObjectUniform(D_L10_001B13D4, x, y, 0x55f0c070, 1.0f, 0.0f);

        /* The weapon's level gauge, red to green in one, two or three segments. */
        idx = FindLastUsedChainEntry(6);
        ratio = IntToFloat(D_L10_002A3C70[idx].value) / IntToFloat(D_L10_002A3C70[idx].maxLevel);
        switch (idx) {
        case 6:
            if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio);
                DrawScaledObjectUniform(D_L10_001B13DC, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 12:
            if (ratio > 0.5f) {
                ratio -= 0.5f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                DrawScaledObjectUniform(D_L10_001B13E0, x, y, (s32)tweenColor, 1.0f, 0.0f);
                DrawScaledObjectUniform(D_L10_001B13DC, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                DrawScaledObjectUniform(D_L10_001B13DC, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 14:
            if (ratio > 0.6666667f) {
                ratio -= 0.6666667f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                DrawScaledObjectUniform(D_L10_001B13E4, x, y, (s32)tweenColor, 1.0f, 0.0f);
                DrawScaledObjectUniform(D_L10_001B13E0, x, y, 0x8000ff00, 1.0f, 0.0f);
                DrawScaledObjectUniform(D_L10_001B13DC, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.33333334f) {
                ratio -= 0.33333334f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                DrawScaledObjectUniform(D_L10_001B13E0, x, y, (s32)tweenColor, 1.0f, 0.0f);
                DrawScaledObjectUniform(D_L10_001B13DC, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                DrawScaledObjectUniform(D_L10_001B13DC, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        }

        /* Health bar: blinks below 30%. */
        fill = D_L10_00221CD0.health * 0.01f;
        if (fill > 0.3f) {
            data->blinkOn = 1;
        } else if (FastFloatHelperD(&data->blinkTimer)) {
            data->blinkTimer = 5;
            data->blinkOn ^= 1;
        }
        colors[1] = FastTweenColor(0x800000ff, 0x8000ff00, fill);
        colors[0] = 0x800000ff;
        barRight = fill * 200.0f + 156.0f;
        if (data->blinkOn)
            DrawScreenRectangle(156, 14, (s32)barRight, 27, 1, colors);

        /* Ammo bar. */
        idx = FindLastUsedChainEntry(7);
        ratio = IntToFloat(D_L10_002A3C70[idx].value);
        fill = ratio / IntToFloat(D_L10_002A3C70[idx].maxAmmo);
        color = FastTweenColor(0x800000ff, 0x8000ff00, fill);
        base = IntToFloat(450);
        end = IntToFloat(386);
        end -= IntToFloat(450);
        colors2[0] = 0x800000ff;
        colors2[1] = color;
        end = end * fill;
        barRight = base + end;
        if (fill > 0.0f)
            DrawScreenRectangle(450, 8, (s32)barRight, 19, 1, colors2);

        /* Weapon icons and the fill count. */
        b0 = D_L10_001B14E8;
        b1 = D_L10_001B14F8;
        b2 = D_L10_001B1508;
        DrawHudSpriteGradient(GetIconFrame(0xea97, 1), 21, 7, 30, 30, &b1);
        DrawHudSpriteGradient(GetIconFrame(0xea97, 0), 21, 7, 30, 30, &b0);
        DrawHudSpriteGradient(GetIconFrame(0xea97, D_L10_002A3C70[FindLastUsedChainEntry(D_L10_001B1428)].icon), 21, 7, 30, 30, &b2);
        DrawHudSpriteGradient(GetIconFrame(0xea97, 1), 462, 9, 30, 30, &b1);
        DrawHudSpriteGradient(GetIconFrame(0xea97, D_L10_002A3C70[FindLastUsedChainEntry(7)].icon), 462, 9, 30, 30, &b2);
        Sprintf(text, D_L10_001B1518, D_L10_002A3C70[FindLastUsedChainEntry(D_L10_001B1428)].value,
                      D_L10_002A3C70[FindLastUsedChainEntry(D_L10_001B1428)].maxAmmo);
        DrawTextSmallFont(67, 5, 0x80808080, text, 128);

        /* Weapon switch. */
        SetCounterPlusOne(2);
        newidx = LookUpStepTable();
        if (newidx >= 0) {
            D_L10_002A3C70[FindLastUsedChainEntry(D_L10_001B1428)].active = 0;
            D_L10_001B1428 = newidx;
            D_L10_002A3C70[FindLastUsedChainEntry(newidx)].active = 1;
        }
        DrawScaledObjectUniform(D_L10_001B13D8, x, y, 0x80f0f0f0, 1.0f, 0.0f);
    }

    CallLoadedModuleHandler_L00443E18();
    sprite0 = FindTableEntryById(D_L10_001A904C + 0x8710, 186);
    /* data, done with, holds the second sprite. */
    data = FindTableEntryById(D_L10_001A904C + 0x8710, 187);
    sprite2 = FindTableEntryById(D_L10_001A904C + 0x8710, 188);
    DrawScaledObjectUniform(sprite0, D_L10_001AC5E0 + 4.0f, label_y(sprite0, D_L10_001AC5E4 + 4.0f, D_L10_001B2D84, 0.5f, 1), 0x60442d00, 0.8f, 0.0f);
    DrawScaledObjectUniform(data, D_L10_001AC5E0 + 4.0f, label_y(data, D_L10_001AC5E4 + 4.0f, D_L10_001B2D84, 0.5f, 1), 0x60241700, 0.8f, 0.0f);
    DrawScaledObjectUniform(sprite2, D_L10_001AC5E0 + 4.0f, label_y(sprite2, D_L10_001AC5E4 + 4.0f, D_L10_001B2D84, 0.5f, 1), 0x55f0c070, 0.8f, 0.0f);
    DrawObjectHudMarkers();
    return 1;
}
