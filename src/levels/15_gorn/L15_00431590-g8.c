#include "common.h"

/* func_L15_00431590: draws the Gorn HUD's two sprite pairs, the timed sprite pair (fading in for its
   first frames and out for its last ones, drawn in full with the countdown icon and the frame count
   in between) and two more sprite pairs. The same code as func_L05_00421B98, func_L10_00424CD0 and
   func_L25_0040DE40, with this level's data.

   Every sprite and text label y goes through label_y, the HUD label idiom (see its comment). Its
   tests have no effect on the result and leave no instruction, but retail shows them: after each y
   conversion retail ends a block (the x and y conversions are made before it, the remaining draw
   arguments after it), and the display-mode compare holds the 1 that the icon's real mode test
   reads. The icon's y is screen_coord, the shape of scaled_screen_coord in src/game/002D3390.c.
   The "%d" format string lies in the small-data area and is addressed with one unsplit `la`, which
   is why retail loads the frame count before it. */

typedef struct { u8 bytes[16]; } Block;

/* The HUD object's variables: the timed sprite pair's frame countdown. */
typedef struct {
    u8 pad00[0x60];
    s32 timer;
} HudTimerVars;

extern u8 *D_L15_001B1580 __attribute__((sda));
extern s32 D_L15_001B3694 __attribute__((sda));
extern s32 D_L15_001B3690 __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 *D_L15_001A904C;
extern s32 D_L15_001B1620 __attribute__((sda)), D_L15_001B1628 __attribute__((sda));
extern s32 D_L15_001B1630 __attribute__((sda)), D_L15_001B1638 __attribute__((sda));
extern s32 D_L15_001B1624, D_L15_001B162C, D_L15_001B1634, D_L15_001B163C;
extern f32 D_L15_001B2E84;
extern s32 D_L15_001B2E80;
extern Block D_L15_001B1698;
extern char D_L15_001B16A8[] MACRO_ADDR;

extern void *func_00336D50(void *, s32);
extern void func_00300A00(void *, s32, f32, f32, f32, f32, f32);
extern s32 func_00282948(s32 *);
extern f32 func_00283CE0(s32);
extern s32 func_0028E588(s32, s32);
extern void func_0028EA58(s32, s32, s32, s32, s32, Block *);
extern s32 func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(s32, s32, u64, char *, s32);

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

/* Draws HUD sprite `id` at (X, Y) in screen units. */
#define HUD_SPRITE(id, color, X, Y, a, b, c)                                                        \
    {                                                                                               \
        f32 x;                                                                                      \
        sprite = func_00336D50(D_L15_001A904C + 0x8710, id);                                       \
        x = (f32)(X);                                                                               \
        func_00300A00(sprite, color, x, (f32)label_y(sprite, (f32)(Y), D_L15_001B2E84, 0.5f, 1), a, \
                      b, c);                                                                        \
    }

void func_L15_00431590(s32 first, s32 timed, s32 third, s32 fourth)
{
    HudTimerVars *vars = *(HudTimerVars **)(D_L15_001B1580 + 0x68);
    f32 fade;
    void *sprite;
    char text[128];
    Block color;

    if (!D_L15_001B3694) {
        D_L15_001B3690 = D_001A79F0[3];
        D_L15_001B3694 = 1;
    }
    if (!D_L15_001A904C)
        return;
    if (first) {
        HUD_SPRITE(0xBD, 0x60442D00, D_L15_001B1620, D_L15_001B1624, -1.0f, 1.0f, 0.0f);
        HUD_SPRITE(0xBE, 0x55F0C070, D_L15_001B1620, D_L15_001B1624, -1.0f, 1.0f, 0.0f);
    }
    if (timed && D_L15_001B3690 < D_001A79F0[3]) {
        if (!func_00282948(&vars->timer)) {
            if (vars->timer >= 291) {
                fade = func_00283CE0(300 - vars->timer) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
            } else if (vars->timer < 10) {
                fade = func_00283CE0(vars->timer) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
            } else
                goto full;
            HUD_SPRITE(0xBF, 0x60442D00, D_L15_001B1628, D_L15_001B162C, fade, fade, 0.0f);
            HUD_SPRITE(0xC0, 0x55F0C070, D_L15_001B1628, D_L15_001B162C, fade, fade, 0.0f);
            goto timed_done;
        full:
            HUD_SPRITE(0xBF, 0x60442D00, D_L15_001B1628, D_L15_001B162C, 1.0f, 1.0f, 0.0f);
            HUD_SPRITE(0xC0, 0x55F0C070, D_L15_001B1628, D_L15_001B162C, 1.0f, 1.0f, 0.0f);
            color = D_L15_001B1698;
            {
                s32 icon = func_0028E588(0xEAA2, 3);
                s32 x = D_L15_001B1628 - 51;
                s32 y = screen_coord(D_L15_001B2E80, (f32)(D_L15_001B162C - 13), 1.0f);

                func_0028EA58(icon, x, y, 28, 28, &color);
            }
            func_00115DA8(text, D_L15_001B16A8, D_001A79F0[3]);
            {
                s32 textX = D_L15_001B1628 + 5;

                func_0027F5B8(textX, label_y((void *)textX, (f32)(D_L15_001B162C + 2), D_L15_001B2E84, 0.5f, 1),
                              0x80808080, text, 128);
            }
        timed_done:;
        } else {
            s32 reset = 300;

            D_L15_001B3690 = D_001A79F0[3];
            vars->timer = reset;
        }
    }
    if (third) {
        HUD_SPRITE(0xC1, 0x60442D00, D_L15_001B1630, D_L15_001B1634, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, D_L15_001B1630, D_L15_001B1634, 1.1f, 1.0f, 0.0f);
    }
    if (fourth) {
        HUD_SPRITE(0xC1, 0x60442D00, D_L15_001B1638, D_L15_001B163C, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, D_L15_001B1638, D_L15_001B163C, 1.1f, 1.0f, 0.0f);
    }
}
