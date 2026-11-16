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

extern u8 *g_hud_blink_moby __attribute__((sda));
extern int g_hud_first_draw_done __attribute__((sda));
extern int g_hud_last_map_value __attribute__((sda));
/* The count shown beside the icon is the fourth word of this block. Read as an element, it stays a
   two-word load, which keeps it out of the timer test's delay slot as in retail. */
extern int g_current_map_index[] __attribute__((sda));
extern u8 *g_hud_sprite_table_base;
extern int g_hud_panel_first_x __attribute__((sda)), g_hud_icon_x __attribute__((sda));
extern int g_hud_panel_second_x __attribute__((sda)), g_hud_panel_third_x __attribute__((sda));
extern int g_hud_panel_first_y, g_hud_icon_y, g_hud_panel_second_y, g_hud_panel_third_y;
extern float g_screen_l10_scale;
extern int g_screen_layout_mode;
extern Block g_hud_color_block_active;
extern char g_str_hud_map_format[] MACRO_ADDR;
extern void *table_find_by_id(void *, s32);
/* (sprite, color, x, y, scale, alpha, angle) */
extern void gfx_draw_scaled_object_two_axes(void *, u32, f32, f32, f32, f32, f32);
extern s32 math_fast_float_d(void *);
extern f32 IntToFloat(s32);
extern int GetIconFrame(s32, s32);
extern void hud_draw_sprite_gradient(void *, s32, s32, s32, s32, Block *);
extern s32 sprintf(char *, const char *, ...);
extern void text_draw_medium(s32, s32, u64, char *, s32);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l10_scale + 0.5f;

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
    int mode = g_screen_layout_mode;
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

/* Draws the HUD icon pairs (and the fading counter) used by the mission screens. */
void DrawFadingHudIconPairs(s32 first, s32 second, s32 third, s32 fourth)
{
    u8 *state = *(u8 **)(g_hud_blink_moby + 0x68);
    f32 fade;
    void *sprite;
    char text[128];
    Block color;

    if (g_hud_first_draw_done == 0) {
        g_hud_last_map_value = g_current_map_index[3];
        g_hud_first_draw_done = 1;
    }
    if (g_hud_sprite_table_base == 0)
        return;
    if (first) {
        HUD_SPRITE(0xBD, 0x60442D00, g_hud_panel_first_x, g_hud_panel_first_y, -1.0f, 1.0f, 0.0f);
        HUD_SPRITE(0xBE, 0x55F0C070, g_hud_panel_first_x, g_hud_panel_first_y, -1.0f, 1.0f, 0.0f);
    }
    if (second && g_hud_last_map_value < g_current_map_index[3]) {
        if (math_fast_float_d(state + 0x4C) == 0) {
            if (*(s32 *)(state + 0x4C) >= 291) {
                fade = IntToFloat(300 - *(s32 *)(state + 0x4C)) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
                HUD_SPRITE(0xBF, 0x60442D00, g_hud_icon_x, g_hud_icon_y, fade, fade, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, g_hud_icon_x, g_hud_icon_y, fade, fade, 0.0f);
            } else if (*(s32 *)(state + 0x4C) < 10) {
                fade = IntToFloat(*(s32 *)(state + 0x4C)) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
                HUD_SPRITE(0xBF, 0x60442D00, g_hud_icon_x, g_hud_icon_y, fade, fade, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, g_hud_icon_x, g_hud_icon_y, fade, fade, 0.0f);
            } else {
                s32 textX;

                HUD_SPRITE(0xBF, 0x60442D00, g_hud_icon_x, g_hud_icon_y, 1.0f, 1.0f, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, g_hud_icon_x, g_hud_icon_y, 1.0f, 1.0f, 0.0f);
                color = g_hud_color_block_active;
                hud_draw_sprite_gradient(GetIconFrame(0xEAA2, 3), g_hud_icon_x - 51,
                              screen_coord(g_screen_layout_mode, (f32)(g_hud_icon_y - 13), 1.0f), 28, 28, &color);
                sprintf(text, g_str_hud_map_format, g_current_map_index[3]);
                textX = g_hud_icon_x + 5;
                text_draw_medium(textX, label_y((void *)textX, (f32)(g_hud_icon_y + 2), g_screen_l10_scale, 0.5f, 1),
                              0x80808080, text, 128);
            }
        } else {
            g_hud_last_map_value = g_current_map_index[3];
            *(s32 *)(state + 0x4C) = 300;
        }
    }
    if (third) {
        HUD_SPRITE(0xC1, 0x60442D00, g_hud_panel_second_x, g_hud_panel_second_y, 1.35f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, g_hud_panel_second_x, g_hud_panel_second_y, 1.35f, 1.0f, 0.0f);
    }
    if (fourth) {
        HUD_SPRITE(0xC1, 0x60442D00, g_hud_panel_third_x, g_hud_panel_third_y, 1.35f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, g_hud_panel_third_x, g_hud_panel_third_y, 1.35f, 1.0f, 0.0f);
    }
}
