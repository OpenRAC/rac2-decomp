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
extern s32 g_screen_width MACRO_ADDR;
extern s32 g_screen_height MACRO_ADDR;
extern Style D_L08_001B0490;
extern char D_L08_001B04A0[];

extern void gfx_append_draw_list_packet_b(void), hero_set_saved_float_and_update(void);
extern s32 hero_begin_saved_float_hold(void);
extern s32 hero_end_saved_float_hold(void);
extern void *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object_two_axes(char *, s32, f32, f32, f32, f32, f32);
extern s32 mode_get_selector(void), GetIconFrame(s32, s32), FloatToInt(f32);
extern void hud_draw_sprite_gradient(s32, s32, s32, s32, s32, void *);
extern s32 sprintf(char *, char *, ...);
extern u32 func_001157AC(char *);
extern s32 text_draw_centered_small(s32, s32, u64, void *, s32);

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

    gfx_append_draw_list_packet_b();
    fade = 1.0f;
    size = 32.0f;
    state->fade += D_L08_001B046C * 1.2f;
    if (state->fade > fade) state->fade = fade;
    if (D_L08_001A904C) {
        entry = 0x8710;
        hero_begin_saved_float_hold();
        hero_set_saved_float_and_update();
        z = 0.0f;
        label = (char *)table_find_by_id(D_L08_001A904C + entry, 0xAC);
        gfx_draw_scaled_object_two_axes(label, 0x60442D00, (f32)(g_screen_width / 2), (f32)(g_screen_height / 2), fade, fade, z);
        label = (char *)table_find_by_id(D_L08_001A904C + entry, 0xAD);
        gfx_draw_scaled_object_two_axes(label, 0x55F0C070, (f32)(g_screen_width / 2), (f32)(g_screen_height / 2), fade, fade, z);
        hero_end_saved_float_hold();
    }
    do {
        half = 0.5f;
        t = (fade - state->fade) * size;
        fade = t * half;
        r = (s32)(D_L08_001B0468 * D_L08_001B3244 + half);
    } while (0);
    one = 1;
    style = D_L08_001B0490;
    bottom = (f32)(g_screen_height - r);
    texture = GetIconFrame(0xEAA2, mode_get_selector());
    x = FloatToInt(D_L08_001B0460 + fade);
    t = D_L08_001B3244;
    y = FloatToInt(bottom + (f32)screen_y(fade - (f32)D_L08_001B0484, t, half, one));
    half2 = 0.5f;
    one2 = 1;
    width = FloatToInt(size * state->fade);
    height = hud_round((f32)FloatToInt(size * state->fade), D_L08_001B3244, half2, one2);
    hud_draw_sprite_gradient(texture, x, y, width, height, &style);
    sprintf(text, D_L08_001B04A0, state->count);
    x2 = FloatToInt(D_L08_001B0460 + (f32)D_L08_001B047C);
    y2 = FloatToInt(bottom) + screen_y((f32)D_L08_001B0480, D_L08_001B3244, half2, one2);
    text_draw_centered_small(x2, y2, 0x80F0F0F0UL, text, func_001157AC(text));
    return 0;
}
