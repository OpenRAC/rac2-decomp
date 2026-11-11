#include "common.h"

/* func_PAL_L05_004273C8: Feltzin HUD sprite drawing, ported from func_L05_00421B98 with PAL 50Hz timing (250-frame timer). */

typedef struct { u8 bytes[16]; } Block;

/* The HUD object's variables: the timed sprite pair's frame countdown. */
typedef struct {
    u8 pad00[0x50];
    s32 timer;
} HudTimerVars;

extern u8 *D_L05_001B13B0 __attribute__((sda));
extern s32 D_L05_001B354C __attribute__((sda));
extern s32 D_L05_001B3548 __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 *D_L05_001A904C;
extern s32 D_L05_001B1428 __attribute__((sda)), D_L05_001B1430 __attribute__((sda));
extern s32 D_L05_001B1438 __attribute__((sda)), D_L05_001B1440 __attribute__((sda));
extern s32 D_L05_001B142C, D_L05_001B1434, D_L05_001B143C, D_L05_001B1444;
extern f32 D_L05_001B2D84;
extern s32 D_L05_001B2D80;
extern Block D_L05_001B14A0;
extern char D_L05_001B14B0[] MACRO_ADDR;

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
    f32 scaled = value * D_L05_001B2D84 + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

/* label_y, the HUD label idiom for text and sprite label y coordinates. */
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

/* Draws HUD sprite `id` at (X, Y) in screen units. */
#define HUD_SPRITE(id, color, X, Y, a, b, c)                                                        \
    {                                                                                               \
        f32 x;                                                                                      \
        sprite = func_00336D50(D_L05_001A904C + 0x8710, id);                                       \
        x = (f32)(X);                                                                               \
        func_00300A00(sprite, color, x, (f32)label_y(sprite, (f32)(Y), D_L05_001B2D84, 0.5f, 1), a, \
                      b, c);                                                                        \
    }

void func_PAL_L05_004273C8(s32 first, s32 timed, s32 third, s32 fourth)
{
    HudTimerVars *vars = *(HudTimerVars **)(D_L05_001B13B0 + 0x68);
    f32 fade;
    void *sprite;
    char text[128];
    Block color;

    if (!D_L05_001B354C) {
        D_L05_001B3548 = D_001A79F0[3];
        D_L05_001B354C = 1;
    }
    if (!D_L05_001A904C)
        return;
    if (first) {
        HUD_SPRITE(0xBD, 0x60442D00, D_L05_001B1428, D_L05_001B142C, -1.0f, 1.0f, 0.0f);
        HUD_SPRITE(0xBE, 0x55F0C070, D_L05_001B1428, D_L05_001B142C, -1.0f, 1.0f, 0.0f);
    }
    if (timed && D_L05_001B3548 < D_001A79F0[3]) {
        if (!func_00282948(&vars->timer)) {
            if (vars->timer >= 291) {
                fade = func_00283CE0(250 - vars->timer) * 0.1f;
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
            HUD_SPRITE(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, fade, fade, 0.0f);
            HUD_SPRITE(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, fade, fade, 0.0f);
            goto timed_done;
        full:
            HUD_SPRITE(0xBF, 0x60442D00, D_L05_001B1430, D_L05_001B1434, 1.0f, 1.0f, 0.0f);
            HUD_SPRITE(0xC0, 0x55F0C070, D_L05_001B1430, D_L05_001B1434, 1.0f, 1.0f, 0.0f);
            color = D_L05_001B14A0;
            {
                s32 icon = func_0028E588(0xEAA2, 3);
                s32 x = D_L05_001B1430 - 51;
                s32 y = screen_coord(D_L05_001B2D80, (f32)(D_L05_001B1434 - 13), 1.0f);

                func_0028EA58(icon, x, y, 28, 28, &color);
            }
            func_00115DA8(text, D_L05_001B14B0, D_001A79F0[3]);
            {
                s32 textX = D_L05_001B1430 + 5;

                func_0027F5B8(textX, label_y((void *)textX, (f32)(D_L05_001B1434 + 2), D_L05_001B2D84, 0.5f, 1),
                              0x80808080, text, 128);
            }
        timed_done:;
        } else {
            s32 reset = 250;

            D_L05_001B3548 = D_001A79F0[3];
            vars->timer = reset;
        }
    }
    if (third) {
        HUD_SPRITE(0xC1, 0x60442D00, D_L05_001B1438, D_L05_001B143C, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, D_L05_001B1438, D_L05_001B143C, 1.1f, 1.0f, 0.0f);
    }
    if (fourth) {
        HUD_SPRITE(0xC1, 0x60442D00, D_L05_001B1440, D_L05_001B1444, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, D_L05_001B1440, D_L05_001B1444, 1.1f, 1.0f, 0.0f);
    }
}
