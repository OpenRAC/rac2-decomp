#include "common.h"

/* func_US2_L05_00421F7C: the Feltzin System copy of the v2.00 HUD panel routine that
   func_US2_L15_00431C88 (src/us2/levels/15_gorn/L15_00431C88-g8.c) and func_US2_L10_004254C8 draw for
   their levels: the same C, with this level's data and 0x11F5 as the zero-count text id. See
   func_US2_L15_00431C88 for the label_y idiom.

   Level 05's names are its USA v1.01 addresses. D_L05_001A904C, D_L05_001B2D80/2D84 and D_L05_001B1350
   are read at the same places by carried level 05 code in both releases. D_L05_001B13EC, D_L05_001B13F8
   and D_L05_001B3578 (v2.00 0x001B138C, 0x001B1398, 0x001B34F8) have no carried use; their names
   follow the shift of their neighbours in level 05 (+0x60 around 0x001B1390, +0x80 around 0x001B34F0). */

extern s32 D_001A7340 MACRO_ADDR;
extern u8 D_001A7A0A MACRO_ADDR;
extern u8 D_001A7BB4 MACRO_ADDR;
extern u8 *D_L05_001A904C MACRO_ADDR;
extern f32 D_L05_001B2D84;
extern s32 D_L05_001B2D80 MACRO_ADDR;
extern s32 D_L05_001B3578 MACRO_ADDR;
extern s32 D_L05_001B13EC __attribute__((sda));
extern s32 D_L05_001B1350[] SDATA(D_L05_001B1350);
extern s32 D_L05_001B13F8[][3] SDATA(D_L05_001B13F8);

extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern void *func_00336D50(void *, s32);
extern void func_00300968(void *, f32, f32, s32, f32, f32);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 func_0027FB40(s32, s32, u64, char *, s32);
extern s32 func_L05_00303000(s32, s32, s32, s32, u64, u8 *, s32);
extern void func_0027F5B8(s32, s32, u64, char *, s32);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L05_001B2D84 + 0.5f;

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

s32 func_US2_L05_00421F7C(void) {
    char buf[128];
    f32 center = func_00283CE0(D_001A7340) * 0.5f;
    void *sprite;
    char *text;
    s32 x, y, count, index;

    if (D_L05_001A904C != 0) {
        sprite = func_00336D50(D_L05_001A904C + 0x8710, 0x45);
        func_00300968(sprite, center, (f32)label_y(sprite, 200.0f, D_L05_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
        sprite = func_00336D50(D_L05_001A904C + 0x8710, 0x44);
        func_00300968(sprite, center, (f32)label_y(sprite, 200.0f, D_L05_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
        func_00115DA8(buf, func_00288FB8(0x2e08), D_L05_001B13EC + 1);
        text = func_00288FB8(0x2e29);
        x = func_00283CF0(center);
        y = screen_coord(D_L05_001B2D80, 46.0f, -2.0f);
        func_0027FB40(x, y, 0x80F0F0F0, text, func_001157AC(text));
        text = func_00288FB8(0x3061);
        {
            s32 ty = label_y(text, 131.0f, D_L05_001B2D84, 0.5f, 1);
            func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        index = D_L05_001B1350[D_L05_001B3578] - 1;
        if (index >= 3)
            index = 2;
        count = D_L05_001B13F8[D_L05_001B3578][index];
        if (D_001A7A0A != 0)
            count *= 10;
        text = buf;
        if (count == 0)
            func_00115DA8(buf, func_00288FB8(0x11F5));
        else
            func_00115DA8(buf, func_00288FB8(0x2e5c), count);
        {
            s32 ty = label_y(text, 210.0f, D_L05_001B2D84, 0.5f, 1);
            func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        y = screen_coord(D_L05_001B2D80, 294.0f, 3.0f);
        func_0027F5B8(117, y, 0x80F0F0F0, func_00288FB8(0x3062), -1);
        if (D_001A7BB4 == 5) {
            y = screen_coord(D_L05_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(260, y, 0x80F0F0F0, func_00288FB8(0x3063), -1);
        } else if (D_001A7BB4 == 4) {
            y = screen_coord(D_L05_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(268, y, 0x80F0F0F0, func_00288FB8(0x3063), -1);
        } else if (D_001A7BB4 == 2) {
            y = screen_coord(D_L05_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(256, y, 0x80F0F0F0, func_00288FB8(0x3063), -1);
        } else {
            y = screen_coord(D_L05_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(274, y, 0x80F0F0F0, func_00288FB8(0x3063), -1);
        }
    }
    return 1;
}
