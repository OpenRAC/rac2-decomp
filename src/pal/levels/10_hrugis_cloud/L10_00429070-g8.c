#include "common.h"

/* func_PAL_L10_00429070, the PAL copy of func_L10_004239A0: the same C with PAL's string ids, where the
   last option label's x depends on the language byte D_PAL_001A7C3C (260 for 5, 268 for 4, 256 for 2,
   274 otherwise), each arm drawing the label as USA does. It draws a Hrugis Cloud HUD panel: two
   sprites, the counter line, a wrapped text box, the count line (its own text when the count is zero)
   and two option labels.

   Every sprite and box label y goes through label_y, the HUD label idiom (see its comment). Its
   tests have no effect on the result and leave no instruction, but retail shows them: after each y
   conversion retail ends a block, and the display-mode compare holds the 1 that the next real
   screen_coord mode test reads. The box text goes to func_L05_00303000, which returns the height
   used. */

extern s32 D_001A7340 MACRO_ADDR;
extern u8 D_001A7A0A MACRO_ADDR;
extern u8 *D_L10_001A904C MACRO_ADDR;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80 MACRO_ADDR;
extern s32 D_L10_001B355C MACRO_ADDR;
extern u8 D_PAL_001A7C3C MACRO_ADDR;
extern s32 D_L10_001B143C __attribute__((sda));
extern s32 D_L10_001B1390[] SDATA(D_L10_001B1390);
extern s32 D_L10_001B1448[][3] SDATA(D_L10_001B1448);

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

s32 func_PAL_L10_00429070(void) {
    char buf[128];
    f32 center = func_00283CE0(D_001A7340) * 0.5f;
    void *sprite;
    char *text;
    s32 x, y, count, index;

    if (D_L10_001A904C != 0) {
        sprite = func_00336D50(D_L10_001A904C + 0x8710, 0x45);
        func_00300968(sprite, center, (f32)label_y(sprite, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
        sprite = func_00336D50(D_L10_001A904C + 0x8710, 0x44);
        func_00300968(sprite, center, (f32)label_y(sprite, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
        func_00115DA8(buf, func_00288FB8(0xe97), D_L10_001B143C + 1);
        text = func_00288FB8(0xeb8);
        x = func_00283CF0(center);
        y = screen_coord(D_L10_001B2D80, 46.0f, -2.0f);
        func_0027FB40(x, y, 0x80F0F0F0, text, func_001157AC(text));
        text = func_00288FB8(0x10e3);
        {
            s32 ty = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
            func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        index = D_L10_001B1390[D_L10_001B355C] - 1;
        if (index >= 3)
            index = 2;
        count = D_L10_001B1448[D_L10_001B355C][index];
        if (D_001A7A0A != 0)
            count *= 10;
        text = buf;
        if (count == 0)
            func_00115DA8(buf, func_00288FB8(0x11FB));
        else
            func_00115DA8(buf, func_00288FB8(0xeeb), count);
        {
            s32 ty = label_y(text, 210.0f, D_L10_001B2D84, 0.5f, 1);
            func_L05_00303000(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        y = screen_coord(D_L10_001B2D80, 294.0f, 3.0f);
        func_0027F5B8(117, y, 0x80F0F0F0, func_00288FB8(0x10e4), -1);
        if (D_PAL_001A7C3C == 5) {
            y = screen_coord(D_L10_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(260, y, 0x80F0F0F0, func_00288FB8(0x10e5), -1);
        } else if (D_PAL_001A7C3C == 4) {
            y = screen_coord(D_L10_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(268, y, 0x80F0F0F0, func_00288FB8(0x10e5), -1);
        } else if (D_PAL_001A7C3C == 2) {
            y = screen_coord(D_L10_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(256, y, 0x80F0F0F0, func_00288FB8(0x10e5), -1);
        } else {
            y = screen_coord(D_L10_001B2D80, 294.0f, 3.0f);
            func_0027F5B8(274, y, 0x80F0F0F0, func_00288FB8(0x10e5), -1);
        }
    }
    return 1;
}
