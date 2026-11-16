#include "common.h"

/* func_PAL_L05_004273C8: Feltzin HUD sprite drawing, ported from func_L05_00421B98 with PAL 50Hz timing (250-frame timer). */

typedef struct { u8 bytes[16]; } Block;

/* The HUD object's variables: the timed sprite pair's frame countdown. */
typedef struct {
    u8 pad00[0x50];
    s32 timer;
} HudTimerVars;

extern u8 *g_feltzin_controller_moby __attribute__((sda));
extern s32 g_feltzin_hud_shown __attribute__((sda));
extern s32 g_feltzin_last_time __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 *g_feltzin_mission_data;
extern s32 g_feltzin_hud_icon_x __attribute__((sda)), g_feltzin_hud_badge_x __attribute__((sda));
extern s32 g_feltzin_hud_label_x __attribute__((sda)), g_feltzin_hud_label_alt_x __attribute__((sda));
extern s32 g_feltzin_hud_icon_y, g_feltzin_hud_badge_y, g_feltzin_hud_label_y, g_feltzin_hud_label_alt_y;
extern f32 g_screen_l05_scale;
extern s32 g_label_mode;
extern Block g_feltzin_hud_color;
extern char g_str_feltzin_map_label[] MACRO_ADDR;

extern void *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object_two_axes(void *, s32, f32, f32, f32, f32, f32);
extern s32 math_fast_float_d(s32 *);
extern f32 IntToFloat(s32);
extern s32 GetIconFrame(s32, s32);
extern void hud_draw_sprite_gradient(s32, s32, s32, s32, s32, Block *);
extern s32 sprintf(char *, char *, ...);
extern void text_draw_medium(s32, s32, u64, char *, s32);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l05_scale + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

/* label_y, the HUD label idiom for text and sprite label y coordinates. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_label_mode;
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

void hud_draw_feltzin_mission_sprites_pal(s32 first, s32 timed, s32 third, s32 fourth)
{
    HudTimerVars *vars = *(HudTimerVars **)(g_feltzin_controller_moby + 0x68);
    f32 fade;
    void *sprite;
    char text[128];
    Block color;

    if (!g_feltzin_hud_shown) {
        g_feltzin_last_time = g_current_map_index[3];
        g_feltzin_hud_shown = 1;
    }
    if (!g_feltzin_mission_data)
        return;
    if (first) {
        HUD_SPRITE(0xBD, 0x60442D00, g_feltzin_hud_icon_x, g_feltzin_hud_icon_y, -1.0f, 1.0f, 0.0f);
        HUD_SPRITE(0xBE, 0x55F0C070, g_feltzin_hud_icon_x, g_feltzin_hud_icon_y, -1.0f, 1.0f, 0.0f);
    }
    if (timed && g_feltzin_last_time < g_current_map_index[3]) {
        if (!math_fast_float_d(&vars->timer)) {
            if (vars->timer >= 291) {
                fade = IntToFloat(250 - vars->timer) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
            } else if (vars->timer < 10) {
                fade = IntToFloat(vars->timer) * 0.1f;
                if (fade > 1.0f)
                    fade = 1.0f;
                else if (fade < 0.0f)
                    fade = 0.0f;
            } else
                goto full;
            HUD_SPRITE(0xBF, 0x60442D00, g_feltzin_hud_badge_x, g_feltzin_hud_badge_y, fade, fade, 0.0f);
            HUD_SPRITE(0xC0, 0x55F0C070, g_feltzin_hud_badge_x, g_feltzin_hud_badge_y, fade, fade, 0.0f);
            goto timed_done;
        full:
            HUD_SPRITE(0xBF, 0x60442D00, g_feltzin_hud_badge_x, g_feltzin_hud_badge_y, 1.0f, 1.0f, 0.0f);
            HUD_SPRITE(0xC0, 0x55F0C070, g_feltzin_hud_badge_x, g_feltzin_hud_badge_y, 1.0f, 1.0f, 0.0f);
            color = g_feltzin_hud_color;
            {
                s32 icon = GetIconFrame(0xEAA2, 3);
                s32 x = g_feltzin_hud_badge_x - 51;
                s32 y = screen_coord(g_label_mode, (f32)(g_feltzin_hud_badge_y - 13), 1.0f);

                hud_draw_sprite_gradient(icon, x, y, 28, 28, &color);
            }
            sprintf(text, g_str_feltzin_map_label, g_current_map_index[3]);
            {
                s32 textX = g_feltzin_hud_badge_x + 5;

                text_draw_medium(textX, label_y((void *)textX, (f32)(g_feltzin_hud_badge_y + 2), g_screen_l05_scale, 0.5f, 1),
                              0x80808080, text, 128);
            }
        timed_done:;
        } else {
            s32 reset = 250;

            g_feltzin_last_time = g_current_map_index[3];
            vars->timer = reset;
        }
    }
    if (third) {
        HUD_SPRITE(0xC1, 0x60442D00, g_feltzin_hud_label_x, g_feltzin_hud_label_y, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, g_feltzin_hud_label_x, g_feltzin_hud_label_y, 1.1f, 1.0f, 0.0f);
    }
    if (fourth) {
        HUD_SPRITE(0xC1, 0x60442D00, g_feltzin_hud_label_alt_x, g_feltzin_hud_label_alt_y, 1.1f, 1.0f, 0.0f);
        HUD_SPRITE(0xC2, 0x55F0C070, g_feltzin_hud_label_alt_x, g_feltzin_hud_label_alt_y, 1.1f, 1.0f, 0.0f);
    }
}
