#include "common.h"

/* func_PAL_L08_003DF82C (levels 8 and 19), the PAL copy of func_L08_003DB518
   (src/levels/shared/L08_003DB518-g8.c): the same C, where the fade step is scaled by 1.2f (50 Hz).

   Fades a meter in, draws the two centred labels when the text table is loaded, then the
   meter icon and its counter at the bottom of the screen. Built with -malign-loops=2
   (config/cflags.txt): the one-pass group starts at the join, and retail does not pad the
   label after it. */

typedef struct __attribute__((packed)) { s64 word[2]; } Style;
typedef struct { s32 count; f32 fade; } Meter;

extern u8 *D_L08_001B0488 __attribute__((sda));
extern u8 *D_L08_001A904C MACRO_ADDR;
extern f32 D_L08_001B046C __attribute__((sda));
extern f32 D_L08_001B0468 __attribute__((sda));
extern f32 D_L08_001B0460 __attribute__((sda));
extern s32 D_L08_001B0484 __attribute__((sda));
extern s32 D_L08_001B047C __attribute__((sda));
extern s32 D_L08_001B0480 __attribute__((sda));
extern f32 D_L08_001B3244 MACRO_ADDR;
extern s32 D_L08_001B3240 MACRO_ADDR;
extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_001A7344 MACRO_ADDR;
extern Style D_L08_001B0490;
extern char D_L08_001B04A0[];

extern void func_L00_0037B750(void), func_L08_00300090(void), func_L08_00300100(void);
extern void func_L08_003000C0(void);
extern s32 func_00336D50(void *, s32);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern s32 func_L08_003DB4E8(void), func_0028E588(s32, s32), func_00283CF0(f32);
extern int func_0028EA58(s32, s32, s32, s32, s32, void *);
extern s32 func_00115DA8(char *, char *, ...);
extern u32 func_001157AC(char *);
extern s32 func_0027FAA8(s32, s32, u64, void *, s32);

/* A screen y scaled for the display and rounded, four pixels lower in display mode 1. */
static __inline__ s32 screen_y(f32 v, f32 scale, f32 half, s32 active)
{
    f32 scaled = v * scale + half;
    if (D_L08_001B3240 == active) return (s32)(scaled + 4.0f);
    return (s32)scaled;
}

/* A size scaled for the display and rounded. The display-mode test has no effect on the
   result, but it is real: it goes at flow2, after allocation (as func_L11_004456A0). */
static __inline__ s32 hud_round(f32 value, f32 scale, f32 half, s32 active)
{
    f32 scaled = value * scale + half;
    s32 result = (s32)scaled;
    if (result != 0 && D_L08_001B3240 == active) scaled = 1.0f;
    return result;
}

s32 func_PAL_L08_003DF82C(void)
{
    Style style;
    char text[16];
    Meter *state = *(Meter **)(D_L08_001B0488 + 0x68);
    f32 t, fade, bottom, size, z, half, half2;
    s32 r, texture, x, y, x2, y2, width, height, one, one2, entry;
    char *label;

    func_L00_0037B750();
    fade = 1.0f;
    size = 32.0f;
    state->fade += D_L08_001B046C * 1.2f;
    if (state->fade > fade) state->fade = fade;
    if (D_L08_001A904C) {
        entry = 0x8710;
        func_L08_00300090();
        func_L08_00300100();
        z = 0.0f;
        label = (char *)func_00336D50(D_L08_001A904C + entry, 0xAC);
        func_00300A00(label, 0x60442D00, (f32)(D_001A7340 / 2), (f32)(D_001A7344 / 2), fade, fade, z);
        label = (char *)func_00336D50(D_L08_001A904C + entry, 0xAD);
        func_00300A00(label, 0x55F0C070, (f32)(D_001A7340 / 2), (f32)(D_001A7344 / 2), fade, fade, z);
        func_L08_003000C0();
    }
    do {
        half = 0.5f;
        t = (fade - state->fade) * size;
        fade = t * half;
        r = (s32)(D_L08_001B0468 * D_L08_001B3244 + half);
    } while (0);
    one = 1;
    style = D_L08_001B0490;
    bottom = (f32)(D_001A7344 - r);
    texture = func_0028E588(0xEAA2, func_L08_003DB4E8());
    x = func_00283CF0(D_L08_001B0460 + fade);
    t = D_L08_001B3244;
    y = func_00283CF0(bottom + (f32)screen_y(fade - (f32)D_L08_001B0484, t, half, one));
    half2 = 0.5f;
    one2 = 1;
    width = func_00283CF0(size * state->fade);
    height = hud_round((f32)func_00283CF0(size * state->fade), D_L08_001B3244, half2, one2);
    func_0028EA58(texture, x, y, width, height, &style);
    func_00115DA8(text, D_L08_001B04A0, state->count);
    x2 = func_00283CF0(D_L08_001B0460 + (f32)D_L08_001B047C);
    y2 = func_00283CF0(bottom) + screen_y((f32)D_L08_001B0480, D_L08_001B3244, half2, one2);
    func_0027FAA8(x2, y2, 0x80F0F0F0UL, text, func_001157AC(text));
    return 0;
}
