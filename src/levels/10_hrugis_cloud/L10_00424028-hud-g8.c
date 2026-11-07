#include "common.h"

/* func_L10_00424CD0 (DrawFadingHudIconPairs): two sprite pairs, the timed pair (faded in and out
   over its first and last ten frames, otherwise drawn in full with its icon and count), and two
   more pairs.

   Every sprite and text label y goes through label_y, the HUD label idiom (see its comment), and the
   icon y through screen_coord. label_y's tests have no effect on the result and leave no
   instruction, but retail shows them: after each y conversion retail ends a block (the x and y
   conversions are made before it, the remaining draw arguments after it), the display-mode compare
   holds a 1 in a saved register, and its last use leaves the unused saved $s2. */

typedef struct { u8 bytes[16]; } Block;

extern u8 *D_L10_001B13F0 __attribute__((sda));
extern int D_L10_001B3548 __attribute__((sda));
extern int D_L10_001B3544 __attribute__((sda));
/* The count shown beside the icon is the fourth word of this block. Read as an element, it stays a
   two-word load, which keeps it out of the timer test's delay slot as in retail. */
extern int D_001A79F0[] __attribute__((sda));
extern u8 *D_L10_001A904C;
extern int D_L10_001B14A8 __attribute__((sda)), D_L10_001B14B0 __attribute__((sda));
extern int D_L10_001B14B8 __attribute__((sda)), D_L10_001B14C0 __attribute__((sda));
extern int D_L10_001B14AC, D_L10_001B14B4, D_L10_001B14BC, D_L10_001B14C4;
extern float D_L10_001B2D84;
extern int D_L10_001B2D80;
extern Block D_L10_001B1520;
extern char D_L10_001B1530[] MACRO_ADDR;
extern void *func_00336D50(void *, s32);
/* (sprite, color, x, y, scale, alpha, angle) */
extern void func_00300A00(void *, u32, f32, f32, f32, f32, f32);
extern s32 func_00282948(void *);
extern f32 func_00283CE0(s32);
extern void *func_0028E588(s32, s32);
extern void func_0028EA58(void *, s32, s32, s32, s32, Block *);
extern s32 func_00115DA8(char *, const char *, ...);
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

/* One sprite of a pair at (x, y): its y scaled for the display. */
#define HUD_SPRITE(id, color, x, y, scale, alpha, angle)                                       \
    {                                                                                          \
        sprite = func_00336D50(D_L10_001A904C + 0x8710, id);                                   \
        func_00300A00(sprite, color, (f32)(x),                                                 \
                      (f32)label_y(sprite, (f32)(y), D_L10_001B2D84, 0.5f, 1), scale, alpha, angle); \
    }

void func_L10_00424CD0(s32 first, s32 second, s32 third, s32 fourth)
{
    u8 *state = *(u8 **)(D_L10_001B13F0 + 0x68);
    f32 fade;
    void *sprite;
    char text[128];
    Block color;

    if (D_L10_001B3548 == 0) {
        D_L10_001B3544 = D_001A79F0[3];
        D_L10_001B3548 = 1;
    }
    if (D_L10_001A904C == 0)
        return;
    if (first) {
        HUD_SPRITE(0xBD, 0x60442D00, D_L10_001B14A8, D_L10_001B14AC, -1.0f, 1.0f, 0.0f);
        HUD_SPRITE(0xBE, 0x55F0C070, D_L10_001B14A8, D_L10_001B14AC, -1.0f, 1.0f, 0.0f);
    }
    if (second && D_L10_001B3544 < D_001A79F0[3]) {
        if (func_00282948(state + 0x4C) == 0) {
            if (*(s32 *)(state + 0x4C) >= 291) {
                fade = func_00283CE0(300 - *(s32 *)(state + 0x4C)) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
                HUD_SPRITE(0xBF, 0x60442D00, D_L10_001B14B0, D_L10_001B14B4, fade, fade, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, D_L10_001B14B0, D_L10_001B14B4, fade, fade, 0.0f);
            } else if (*(s32 *)(state + 0x4C) < 10) {
                fade = func_00283CE0(*(s32 *)(state + 0x4C)) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
                HUD_SPRITE(0xBF, 0x60442D00, D_L10_001B14B0, D_L10_001B14B4, fade, fade, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, D_L10_001B14B0, D_L10_001B14B4, fade, fade, 0.0f);
            } else {
                s32 textX;

                HUD_SPRITE(0xBF, 0x60442D00, D_L10_001B14B0, D_L10_001B14B4, 1.0f, 1.0f, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, D_L10_001B14B0, D_L10_001B14B4, 1.0f, 1.0f, 0.0f);
                color = D_L10_001B1520;
                func_0028EA58(func_0028E588(0xEAA2, 3), D_L10_001B14B0 - 51,
                              screen_coord(D_L10_001B2D80, (f32)(D_L10_001B14B4 - 13), 1.0f), 28, 28, &color);
                func_00115DA8(text, D_L10_001B1530, D_001A79F0[3]);
                textX = D_L10_001B14B0 + 5;
                func_0027F5B8(textX, label_y((void *)textX, (f32)(D_L10_001B14B4 + 2), D_L10_001B2D84, 0.5f, 1),
                              0x80808080, text, 128);
            }
        } else {
            D_L10_001B3544 = D_001A79F0[3];
            *(s32 *)(state + 0x4C) = 300;
        }
    }
    if (third) {
        HUD_SPRITE(0xC1, 0x60442D00, D_L10_001B14B8, D_L10_001B14BC, 1.35f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, D_L10_001B14B8, D_L10_001B14BC, 1.35f, 1.0f, 0.0f);
    }
    if (fourth) {
        HUD_SPRITE(0xC1, 0x60442D00, D_L10_001B14C0, D_L10_001B14C4, 1.35f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, D_L10_001B14C0, D_L10_001B14C4, 1.35f, 1.0f, 0.0f);
    }
}
