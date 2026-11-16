#include "names.h"
/* func_PAL_L25_00412938, the PAL copy of func_L25_0040DE40: the same C. */
#include "common.h"

/* func_PAL_L25_00412938, this level's copy of func_L10_00424CD0 (DrawFadingHudIconPairs, in
   src/levels/10_hrugis_cloud/L10_00424028-hud-g8.c): the same C, with this level's data, the timer
   at +0x30 and 1.1f for the last two pairs' scale. Two sprite pairs, the timed pair (faded in and
   out over its first and last ten frames, otherwise drawn in full with its icon and count), and two
   more pairs.

   Every sprite and text label y goes through label_y, the HUD label idiom (see its comment), and the
   icon y through screen_coord. label_y's tests have no effect on the result and leave no
   instruction, but retail shows them: after each y conversion retail ends a block (the x and y
   conversions are made before it, the remaining draw arguments after it), the display-mode compare
   holds a 1 in a saved register, and its last use leaves the unused saved $s2. */

typedef struct { u8 bytes[16]; } Block;

extern u8 *g_mission_moby __attribute__((sda));
extern int g_hud_icon_pairs_initialized __attribute__((sda));
extern int g_mission_last_map_index __attribute__((sda));
/* The count shown beside the icon is the fourth word of this block. Read as an element, it stays a
   two-word load, which keeps it out of the timer test's delay slot as in retail. */
extern int g_current_map_index[] __attribute__((sda));
extern u8 *g_hud_l25_resource_base;
extern int g_hud_icon_pair_x __attribute__((sda)), g_hud_icon_pair_x_second __attribute__((sda));
extern int g_hud_text_x_left __attribute__((sda)), g_hud_text_x_right __attribute__((sda));
extern int g_hud_icon_pair_y, g_hud_icon_pair_y_second, g_hud_text_y_left, g_hud_text_y_right;
extern float g_hud_screen_scale;
extern int g_hud_l25_layout_mode;
extern Block g_hud_sprite_color;
extern char g_str_hud_map_index_format[] MACRO_ADDR;
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
    f32 scaled = value * g_hud_screen_scale + 0.5f;

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
    int mode = g_hud_l25_layout_mode;
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
        sprite = func_00336D50(D_L25_001A904C + 0x8710, id);                                   \
        func_00300A00(sprite, color, (f32)(x),                                                 \
                      (f32)label_y(sprite, (f32)(y), D_L25_001B2904, 0.5f, 1), scale, alpha, angle); \
    }

/* Draws the HUD icon pairs: the first, the timed pair (faded in and out over its first and last ten frames), and two more. */
void hud_draw_fading_icon_pairs_pal(s32 show_first, s32 show_second, s32 show_third, s32 show_fourth)
{
    u8 *vars = *(u8 **)(g_mission_moby + 0x68);
    f32 fade;
    void *sprite;
    char text[128];
    Block color;

    if (g_hud_icon_pairs_initialized == 0) {
        g_mission_last_map_index = g_current_map_index[3];
        g_hud_icon_pairs_initialized = 1;
    }
    if (g_hud_l25_resource_base == 0)
        return;
    if (show_first) {
        HUD_SPRITE(0xBD, 0x60442D00, g_hud_icon_pair_x, g_hud_icon_pair_y, -1.0f, 1.0f, 0.0f);
        HUD_SPRITE(0xBE, 0x55F0C070, g_hud_icon_pair_x, g_hud_icon_pair_y, -1.0f, 1.0f, 0.0f);
    }
    if (show_second && g_mission_last_map_index < g_current_map_index[3]) {
        if (math_fast_float_d(vars + 0x30) == 0) {
            if (*(s32 *)(vars + 0x30) >= 291) {
                fade = IntToFloat(250 - *(s32 *)(vars + 0x30)) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
                HUD_SPRITE(0xBF, 0x60442D00, g_hud_icon_pair_x_second, g_hud_icon_pair_y_second, fade, fade, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, g_hud_icon_pair_x_second, g_hud_icon_pair_y_second, fade, fade, 0.0f);
            } else if (*(s32 *)(vars + 0x30) < 10) {
                fade = IntToFloat(*(s32 *)(vars + 0x30)) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
                HUD_SPRITE(0xBF, 0x60442D00, g_hud_icon_pair_x_second, g_hud_icon_pair_y_second, fade, fade, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, g_hud_icon_pair_x_second, g_hud_icon_pair_y_second, fade, fade, 0.0f);
            } else {
                s32 text_x;

                HUD_SPRITE(0xBF, 0x60442D00, g_hud_icon_pair_x_second, g_hud_icon_pair_y_second, 1.0f, 1.0f, 0.0f);
                HUD_SPRITE(0xC0, 0x55F0C070, g_hud_icon_pair_x_second, g_hud_icon_pair_y_second, 1.0f, 1.0f, 0.0f);
                color = g_hud_sprite_color;
                hud_draw_sprite_gradient(GetIconFrame(0xEAA2, 3), g_hud_icon_pair_x_second - 51,
                              screen_coord(g_hud_l25_layout_mode, (f32)(g_hud_icon_pair_y_second - 13), 1.0f), 28, 28, &color);
                sprintf(text, g_str_hud_map_index_format, g_current_map_index[3]);
                text_x = g_hud_icon_pair_x_second + 5;
                text_draw_medium(text_x, label_y((void *)text_x, (f32)(g_hud_icon_pair_y_second + 2), g_hud_screen_scale, 0.5f, 1),
                              0x80808080, text, 128);
            }
        } else {
            g_mission_last_map_index = g_current_map_index[3];
            *(s32 *)(vars + 0x30) = 250;
        }
    }
    if (show_third) {
        HUD_SPRITE(0xC1, 0x60442D00, g_hud_text_x_left, g_hud_text_y_left, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, g_hud_text_x_left, g_hud_text_y_left, 1.1f, 1.0f, 0.0f);
    }
    if (show_fourth) {
        HUD_SPRITE(0xC1, 0x60442D00, g_hud_text_x_right, g_hud_text_y_right, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, g_hud_text_x_right, g_hud_text_y_right, 1.1f, 1.0f, 0.0f);
    }
}
