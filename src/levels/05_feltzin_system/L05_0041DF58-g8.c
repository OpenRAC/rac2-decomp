#include "common.h"

/* func_L05_0041DF58 (DrawFeltzinMissionHud): the Feltzin System mission HUD. The mission text for
   the current stage, the ship's health and ammo bars, the weapon icons and the three corner sprites.
   Ported from the matched func_L10_00421790 (L10_00421790-g8.c), the same routine for Hrugis Cloud.

   Every text and sprite label y goes through label_y, the HUD label idiom (dead-test helper, allowed
   by owner ruling). Case 1's second label passes the stage global, which is 1 in that case, as
   `active` (a value holding 1, as allowed by owner ruling): with the literal 1, both of case 0's and
   case 1's identical second-draw tails reach jump2 with equal RTL and are cross-jumped into one;
   retail keeps them apart. */

typedef struct { u8 bytes[16]; } Block;

typedef struct {
    s32 active;
    u8 pad04[8];
    s32 maxLevel;
    s32 maxAmmo;
    s32 value;
    u8 pad18[4];
    s16 icon;
    u8 pad1E[10];
} HudWeapon;

typedef struct {
    u8 pad00[0x10];
    s32 objectives;
    s32 wave;
    u8 pad18[0x10];
    s32 health;
} HudMissionState;

typedef struct {
    u8 pad00[0x34];
    s32 blinkTimer;
    s32 blinkOn;
    u8 pad3C[8];
    s32 time;
} HudBlinkVars;

extern u8 *g_feltzin_controller_moby __attribute__((sda));
extern s32 g_feltzin_menu_mode __attribute__((sda));
extern s32 g_feltzin_hud_label_x __attribute__((sda));
extern s32 g_feltzin_hud_label_alt_x __attribute__((sda));
extern s32 g_feltzin_hud_icon_x __attribute__((sda));
extern s32 g_feltzin_active_slot_index __attribute__((sda));
extern s32 g_feltzin_countdown_timer __attribute__((sda));
extern void *g_feltzin_hud_sprite_a __attribute__((sda));
extern void *g_feltzin_hud_sprite_b __attribute__((sda));
extern void *g_feltzin_hud_sprite_c __attribute__((sda));
extern void *g_feltzin_hud_sprite_d __attribute__((sda));
extern void *g_feltzin_hud_sprite_e __attribute__((sda));
extern void *g_feltzin_hud_sprite_f __attribute__((sda));
extern u8 *g_feltzin_mission_data MACRO_ADDR;
extern s32 g_feltzin_hud_label_y MACRO_ADDR;
extern s32 g_feltzin_hud_label_alt_y MACRO_ADDR;
extern s32 g_feltzin_hud_icon_y MACRO_ADDR;
extern f32 g_screen_l05_scale;
extern s32 g_label_mode MACRO_ADDR;
extern s32 g_screen_width MACRO_ADDR;
extern s32 g_feltzin_timer MACRO_ADDR;
extern HudMissionState g_feltzin_challenge_state;
extern f32 g_hud_marker_x, g_hud_marker_y;
extern char g_str_feltzin_label_count[], g_str_feltzin_label_time[], g_str_feltzin_slot_value[];
extern Block g_feltzin_color_block_a, g_feltzin_color_block_b, g_feltzin_color_block_c;
extern HudWeapon g_spawn_entry_table[];

extern void hud_draw_feltzin_mission_sprites(s32, s32, s32, s32);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern void text_draw_medium(s32, s32, u64, char *, s32);
extern s32 math_fast_float_d(s32 *);
extern void math_split_time_into_parts(s32, s32 *, s32 *, s32 *);
extern void *table_find_by_id(void *, s32);
extern f32 IntToFloat(s32);
extern void gfx_draw_scaled_object(void *, f32, f32, s32, f32, f32);
extern s32 table_find_last_used_entry(s32);
extern s32 FastTweenColor(u32, u32, f32);
extern void gfx_draw_screen_rectangle(s32, s32, s32, s32, s32, u32 *);
extern int GetIconFrame(s32, s32);
extern void hud_draw_sprite_gradient(void *, s32, s32, s32, s32, Block *);
extern void text_draw_small(s32, s32, u64, char *, s32);
extern void level_set_counter_plus_one(s32);
extern s32 level_lookup_step_table(void);
extern void module_l00_call_handler_2(void), hud_draw_object_markers(void);

static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l05_scale + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

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

/* Draws the Feltzin combat HUD: wave and objective text, the timer, the health and ammo bars, the weapon icons and the corner sprites. */
s32 DrawFeltzinCombatHud(void) {
    char text[128];
    char *label;
    u32 colors[2], colors2[2];
    Block b0, b1, b2;
    s32 minutes, seconds, hundredths, idx, newidx, color, textX;
    HudBlinkVars *data = *(HudBlinkVars **)(g_feltzin_controller_moby + 0x68);
    f32 x, y, ratio, tmp, base, end, fill, tweenColor;
    void *sprite0, *sprite2;

    switch (g_feltzin_menu_mode) {
    case 0:
        hud_draw_feltzin_mission_sprites(0, 1, 1, 1);
        label = GetLocalizedString(0x31d1);
        sprintf(text, g_str_feltzin_label_count, label, g_feltzin_challenge_state.objectives);
        textX = g_feltzin_hud_label_x - 60;
        text_draw_medium(textX, label_y((void *)textX, g_feltzin_hud_label_y - 8, g_screen_l05_scale, 0.5f, 1), 0x80808080, text, 128);
        label = GetLocalizedString(0x31d2);
        sprintf(text, g_str_feltzin_label_count, label, g_feltzin_challenge_state.wave + 1);
        textX = g_feltzin_hud_label_alt_x - 60;
        text_draw_medium(textX, label_y((void *)textX, g_feltzin_hud_label_alt_y - 8, g_screen_l05_scale, 0.5f, 1), 0x80808080, text, 128);
        break;
    case 1: {
        f32 half = 0.5f;
        s32 textX2;

        hud_draw_feltzin_mission_sprites(1, 1, 0, 1);
        label = GetLocalizedString(0x31d4);
        sprintf(text, g_str_feltzin_label_count, label, g_feltzin_challenge_state.objectives);
        textX = g_feltzin_hud_label_alt_x - 60;
        text_draw_medium(textX, label_y((void *)textX, g_feltzin_hud_label_alt_y - 8, g_screen_l05_scale, half, 1), 0x80808080, text, 128);
        math_split_time_into_parts(data->time, &minutes, &seconds, &hundredths);
        label = GetLocalizedString(0x2f83);
        sprintf(text, g_str_feltzin_label_time, label, minutes, seconds, hundredths);
        textX2 = g_feltzin_hud_icon_x - 80;
        /* active is the switch value, 1 in this case (allowed by owner ruling, 2026-11-09). */
        text_draw_medium(textX2, label_y((void *)textX2, g_feltzin_hud_icon_y - 8, g_screen_l05_scale, half, g_feltzin_menu_mode), 0x80808080, text, 128);
        break;
    }
    case 2: {
        s32 textX2;

        hud_draw_feltzin_mission_sprites(0, 1, 0, 1);
        label = GetLocalizedString(0x31d1);
        sprintf(text, g_str_feltzin_label_count, label, g_feltzin_challenge_state.objectives);
        textX2 = g_feltzin_hud_label_alt_x - 60;
        text_draw_medium(textX2, label_y((void *)textX2, g_feltzin_hud_label_alt_y - 8, g_screen_l05_scale, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 3: {
        f32 half = 0.5f;
        s32 textX2;

        hud_draw_feltzin_mission_sprites(1, 1, 0, 1);
        label = GetLocalizedString(0x31d7);
        sprintf(text, g_str_feltzin_label_count, label, g_feltzin_countdown_timer);
        textX = g_feltzin_hud_label_alt_x - 60;
        text_draw_medium(textX, label_y((void *)textX, g_feltzin_hud_label_alt_y - 8, g_screen_l05_scale, half, 1), 0x80808080, text, 128);
        math_split_time_into_parts(g_feltzin_timer, &minutes, &seconds, &hundredths);
        label = GetLocalizedString(0x2f83);
        sprintf(text, g_str_feltzin_label_time, label, minutes, seconds, hundredths);
        textX2 = g_feltzin_hud_icon_x - 80;
        text_draw_medium(textX2, label_y((void *)textX2, g_feltzin_hud_icon_y - 8, g_screen_l05_scale, half, 1), 0x80808080, text, 128);
        break;
    }
    }

    if (g_feltzin_mission_data) {
        g_feltzin_hud_sprite_a = table_find_by_id(g_feltzin_mission_data + 0x8710, 128);
        g_feltzin_hud_sprite_b = table_find_by_id(g_feltzin_mission_data + 0x8710, 129);
        g_feltzin_hud_sprite_c = table_find_by_id(g_feltzin_mission_data + 0x8710, 130);
        g_feltzin_hud_sprite_d = table_find_by_id(g_feltzin_mission_data + 0x8710, 131);
        g_feltzin_hud_sprite_e = table_find_by_id(g_feltzin_mission_data + 0x8710, 132);
        g_feltzin_hud_sprite_f = table_find_by_id(g_feltzin_mission_data + 0x8710, 133);
        x = IntToFloat(g_screen_width) * 0.5f;
        y = screen_coord(g_label_mode, 200.0f, 4.0f);
        gfx_draw_scaled_object(g_feltzin_hud_sprite_a, x, y, 0x60442d00, 1.0f, 0.0f);
        gfx_draw_scaled_object(g_feltzin_hud_sprite_b, x, y, 0x55f0c070, 1.0f, 0.0f);

        idx = table_find_last_used_entry(6);
        ratio = IntToFloat(g_spawn_entry_table[idx].value) / IntToFloat(g_spawn_entry_table[idx].maxLevel);
        switch (idx) {
        case 6:
            if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_d, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 12:
            if (ratio > 0.5f) {
                ratio -= 0.5f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_e, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_d, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_d, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 14:
            if (ratio > 0.6666667f) {
                ratio -= 0.6666667f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_f, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_e, x, y, 0x8000ff00, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_d, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.33333334f) {
                ratio -= 0.33333334f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_e, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_d, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_feltzin_hud_sprite_d, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        }

        fill = g_feltzin_challenge_state.health * 0.01f;
        if (fill > 0.3f) {
            data->blinkOn = 1;
        } else if (math_fast_float_d(&data->blinkTimer)) {
            data->blinkTimer = 5;
            data->blinkOn ^= 1;
        }
        colors[1] = FastTweenColor(0x800000ff, 0x8000ff00, fill);
        colors[0] = 0x800000ff;
        tmp = fill * 200.0f + 156.0f;
        if (data->blinkOn)
            gfx_draw_screen_rectangle(156, 14, (s32)tmp, 27, 1, colors);

        idx = table_find_last_used_entry(7);
        ratio = IntToFloat(g_spawn_entry_table[idx].value);
        fill = ratio / IntToFloat(g_spawn_entry_table[idx].maxAmmo);
        color = FastTweenColor(0x800000ff, 0x8000ff00, fill);
        base = IntToFloat(450);
        end = IntToFloat(386);
        end -= IntToFloat(450);
        colors2[0] = 0x800000ff;
        colors2[1] = color;
        end = end * fill;
        tmp = base + end;
        if (fill > 0.0f)
            gfx_draw_screen_rectangle(450, 8, (s32)tmp, 19, 1, colors2);

        b0 = g_feltzin_color_block_a;
        b1 = g_feltzin_color_block_b;
        b2 = g_feltzin_color_block_c;
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 1), 21, 7, 30, 30, &b1);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 0), 21, 7, 30, 30, &b0);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, g_spawn_entry_table[table_find_last_used_entry(g_feltzin_active_slot_index)].icon), 21, 7, 30, 30, &b2);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 1), 462, 9, 30, 30, &b1);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, g_spawn_entry_table[table_find_last_used_entry(7)].icon), 462, 9, 30, 30, &b2);
        sprintf(text, g_str_feltzin_slot_value, g_spawn_entry_table[table_find_last_used_entry(g_feltzin_active_slot_index)].value,
                      g_spawn_entry_table[table_find_last_used_entry(g_feltzin_active_slot_index)].maxAmmo);
        text_draw_small(67, 5, 0x80808080, text, 128);

        level_set_counter_plus_one(2);
        newidx = level_lookup_step_table();
        if (newidx >= 0) {
            g_spawn_entry_table[table_find_last_used_entry(g_feltzin_active_slot_index)].active = 0;
            g_feltzin_active_slot_index = newidx;
            g_spawn_entry_table[table_find_last_used_entry(newidx)].active = 1;
        }
        gfx_draw_scaled_object(g_feltzin_hud_sprite_c, x, y, 0x80f0f0f0, 1.0f, 0.0f);
    }

    module_l00_call_handler_2();
    sprite0 = table_find_by_id(g_feltzin_mission_data + 0x8710, 186);
    data = table_find_by_id(g_feltzin_mission_data + 0x8710, 187);
    sprite2 = table_find_by_id(g_feltzin_mission_data + 0x8710, 188);
    gfx_draw_scaled_object(sprite0, g_hud_marker_x + 4.0f, label_y(sprite0, g_hud_marker_y + 4.0f, g_screen_l05_scale, 0.5f, 1), 0x60442d00, 0.8f, 0.0f);
    gfx_draw_scaled_object(data, g_hud_marker_x + 4.0f, label_y(data, g_hud_marker_y + 4.0f, g_screen_l05_scale, 0.5f, 1), 0x60241700, 0.8f, 0.0f);
    gfx_draw_scaled_object(sprite2, g_hud_marker_x + 4.0f, label_y(sprite2, g_hud_marker_y + 4.0f, g_screen_l05_scale, 0.5f, 1), 0x55f0c070, 0.8f, 0.0f);
    hud_draw_object_markers();
    return 1;
}
