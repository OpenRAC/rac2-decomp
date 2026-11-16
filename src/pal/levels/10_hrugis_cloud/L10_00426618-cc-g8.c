/* func_PAL_L10_00426618, the PAL copy of func_L10_00421790: the same C, where rename func_L10_00424CD0 becomes func_PAL_L10_0042A5C8; rename func_L00_0030DD70 becomes func_PAL_L00_0030FBC0; rename func_002ED578 becomes func_PAL_002EE490; rename func_L05_003263F8 becomes func_PAL_L05_00328198; rename func_L00_0030CF60 becomes func_PAL_0029C7F0. */
#include "common.h"

/* func_PAL_L10_00426618 (DrawHrugisMissionHud): the Hrugis Cloud mission HUD. The mission text for the
   current stage, the ship's health and ammo bars, the weapon icons and the three corner sprites.

   Every text and sprite label y goes through label_y, the HUD label idiom (see its comment). Its tests
   have no effect on the result and leave no instruction, but retail shows them: after each y
   conversion retail ends a block (the x and y conversions are made before it, the remaining draw
   arguments after it), and the display-mode compare holds the 1 that is set up at entry. */

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
    u8 pad00[0x28];
    s32 health;
} HudMissionState;

/* The HUD object's variables: the health bar blinks while health is low. */
typedef struct {
    u8 pad00[0x34];
    s32 blinkTimer;
    s32 blinkOn;
} HudBlinkVars;

extern u8 *g_hud_blink_moby __attribute__((sda));
extern s32 g_selected_mission_kind __attribute__((sda));
extern s32 g_hud_boss_flag_latched __attribute__((sda));
extern s32 g_hud_blink_timer_first __attribute__((sda));
extern s32 g_hud_blink_timer_second __attribute__((sda));
extern s32 g_hud_panel_third_x __attribute__((sda));
extern s32 g_hud_panel_second_x __attribute__((sda));
extern s32 g_hud_panel_first_x __attribute__((sda));
extern s32 g_mission_record_index __attribute__((sda));
extern s32 g_gate_frame_counter __attribute__((sda));
extern void *g_hud_label_sprite_first __attribute__((sda));
extern void *g_hud_label_sprite_second __attribute__((sda));
extern void *g_hud_label_sprite_third __attribute__((sda));
extern void *g_hud_blink_sprite_first __attribute__((sda));
extern void *g_hud_blink_sprite_second __attribute__((sda));
extern void *g_hud_blink_sprite_third __attribute__((sda));
extern u8 *g_hud_sprite_table_base MACRO_ADDR;
extern s32 g_hud_panel_third_y MACRO_ADDR;
extern s32 g_hud_panel_second_y MACRO_ADDR;
extern s32 g_hud_panel_first_y MACRO_ADDR;
extern f32 g_screen_l10_scale;
extern s32 g_screen_layout_mode MACRO_ADDR;
extern s32 g_screen_width MACRO_ADDR;
extern s32 g_mission_time_value MACRO_ADDR;
extern HudMissionState g_mission_state;
extern f32 g_hud_label_offset_x, g_hud_label_offset_y;
extern char g_str_hud_score_format[], g_str_hud_time_format[], g_str_hud_value_format[];
extern Block g_hud_color_block_first, g_hud_color_block_second, g_hud_color_block_third;
extern HudWeapon g_reward_slot_table[];

extern void func_PAL_L10_0042A5C8(s32, s32, s32, s32);
extern void *level_find_object_by_class_id(s32);
extern s32 group_count_alive(void *);
extern s32 list_count_ready_objects(void *);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern void text_draw_medium(s32, s32, u64, char *, s32);
extern s32 hrugis_take_boss_flag_a(void), hrugis_take_boss_flag_b(void);
extern int level_l00_call_module_handler_with_arg_9_pal(char *, s32);
extern s32 math_fast_float_d(s32 *);
extern void func_PAL_002EE490(s32, s32 *, s32 *, s32 *);
extern void *table_find_by_id(void *, s32);
extern f32 IntToFloat(s32);
/* (sprite, x, y, color, scale, angle): the EE passes the integer and float arguments in their own
   register banks. */
extern void gfx_draw_scaled_object(void *, f32, f32, s32, f32, f32);
extern s32 table_find_last_used_entry(s32);
extern s32 FastTweenColor(u32, u32, f32);
extern void gfx_draw_screen_rectangle(s32, s32, s32, s32, s32, u32 *);
extern int GetIconFrame(s32, s32);
extern void hud_draw_sprite_gradient(void *, s32, s32, s32, s32, Block *);
extern void text_draw_small(s32, s32, u64, char *, s32);
extern void func_PAL_L05_00328198(s32);
extern s32 level_lookup_step_table(void);
extern void func_PAL_0029C7F0(void), hud_draw_object_markers(void);

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

s32 func_PAL_L10_00426618(void) {
    char text[128];
    char *label;
    u32 colors[2], colors2[2];
    Block b0, b1, b2;
    s32 a, b, c, score, idx, newidx, color, textX;
    void *object;
    HudBlinkVars *data = *(HudBlinkVars **)(g_hud_blink_moby + 0x68);
    f32 x, y, ratio, tmp, base, end, fill, tweenColor;
    void *sprite0, *sprite2;

    switch (g_selected_mission_kind) {
    case 0:
        func_PAL_L10_0042A5C8(0, 1, 0, 1);
        object = level_find_object_by_class_id(0xf85);
        if (object)
            score = group_count_alive(object);
        else
            score = 0;
        label = GetLocalizedString(0x10f0);
        sprintf(text, g_str_hud_score_format, label, score);
        textX = g_hud_panel_third_x - 65;
        text_draw_medium(textX, label_y((void *)textX, g_hud_panel_third_y - 8, g_screen_l10_scale, 0.5f, 1), 0x80808080, text, 128);
        if (hrugis_take_boss_flag_a() && g_hud_boss_flag_latched) {
            g_hud_boss_flag_latched = 0;
            g_hud_blink_timer_first = 150;
        }
        if (hrugis_take_boss_flag_b()) {
            g_hud_boss_flag_latched = 1;
            g_hud_blink_timer_second = 150;
        }
        if (g_hud_blink_timer_first)
            level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x10f1), -1);
        if (g_hud_blink_timer_second)
            level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x10f2), -1);
        math_fast_float_d(&g_hud_blink_timer_first);
        math_fast_float_d(&g_hud_blink_timer_second);
        break;
    case 1: {
        f32 half = 0.5f;
        char *fmt;

        func_PAL_L10_0042A5C8(0, 1, 1, 1);
        label = GetLocalizedString(0x10f3);
        fmt = g_str_hud_score_format;
        sprintf(text, fmt, label, list_count_ready_objects(level_find_object_by_class_id(0xf93)));
        textX = g_hud_panel_second_x - 65;
        text_draw_medium(textX, label_y((void *)textX, g_hud_panel_second_y - 8, g_screen_l10_scale, half, 1), 0x80808080, text, 128);
        label = GetLocalizedString(0x10f4);
        sprintf(text, fmt, label, list_count_ready_objects(level_find_object_by_class_id(0xcbe)));
        textX = g_hud_panel_third_x - 65;
        text_draw_medium(textX, label_y((void *)textX, g_hud_panel_third_y - 8, g_screen_l10_scale, half, 1), 0x80808080, text, 128);
        break;
    }
    case 2: {
        char *fmt;
        s32 textX2;

        func_PAL_L10_0042A5C8(0, 1, 0, 1);
        label = GetLocalizedString(0x10f5);
        fmt = g_str_hud_score_format;
        sprintf(text, fmt, label, list_count_ready_objects(level_find_object_by_class_id(0xf8e)));
        textX2 = g_hud_panel_third_x - 70;
        text_draw_medium(textX2, label_y((void *)textX2, g_hud_panel_third_y - 8, g_screen_l10_scale, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 3: {
        f32 half = 0.5f;
        s32 textX2;

        func_PAL_L10_0042A5C8(1, 1, 0, 1);
        label = GetLocalizedString(0x10ef);
        sprintf(text, g_str_hud_score_format, label, g_gate_frame_counter);
        textX = g_hud_panel_third_x - 65;
        text_draw_medium(textX, label_y((void *)textX, g_hud_panel_third_y - 8, g_screen_l10_scale, half, 1), 0x80808080, text, 128);
        func_PAL_002EE490(g_mission_time_value, &a, &b, &c);
        label = GetLocalizedString(0xea8);
        sprintf(text, g_str_hud_time_format, label, a, b, c);
        textX2 = g_hud_panel_first_x - 80;
        text_draw_medium(textX2, label_y((void *)textX2, g_hud_panel_first_y - 8, g_screen_l10_scale, half, 1), 0x80808080, text, 128);
        break;
    }
    }

    if (g_hud_sprite_table_base) {
        g_hud_label_sprite_first = table_find_by_id(g_hud_sprite_table_base + 0x8710, 128);
        g_hud_label_sprite_second = table_find_by_id(g_hud_sprite_table_base + 0x8710, 129);
        g_hud_label_sprite_third = table_find_by_id(g_hud_sprite_table_base + 0x8710, 130);
        g_hud_blink_sprite_first = table_find_by_id(g_hud_sprite_table_base + 0x8710, 131);
        g_hud_blink_sprite_second = table_find_by_id(g_hud_sprite_table_base + 0x8710, 132);
        g_hud_blink_sprite_third = table_find_by_id(g_hud_sprite_table_base + 0x8710, 133);
        x = IntToFloat(g_screen_width) * 0.5f;
        y = screen_coord(g_screen_layout_mode, 200.0f, 4.0f);
        gfx_draw_scaled_object(g_hud_label_sprite_first, x, y, 0x60442d00, 1.0f, 0.0f);
        gfx_draw_scaled_object(g_hud_label_sprite_second, x, y, 0x55f0c070, 1.0f, 0.0f);

        /* The weapon's level gauge, red to green in one, two or three segments. */
        idx = table_find_last_used_entry(6);
        ratio = IntToFloat(g_reward_slot_table[idx].value) / IntToFloat(g_reward_slot_table[idx].maxLevel);
        switch (idx) {
        case 6:
            if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio);
                gfx_draw_scaled_object(g_hud_blink_sprite_first, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 12:
            if (ratio > 0.5f) {
                ratio -= 0.5f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                gfx_draw_scaled_object(g_hud_blink_sprite_second, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_first, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                gfx_draw_scaled_object(g_hud_blink_sprite_first, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 14:
            if (ratio > 0.6666667f) {
                ratio -= 0.6666667f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_third, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_second, x, y, 0x8000ff00, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_first, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.33333334f) {
                ratio -= 0.33333334f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_second, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_first, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_hud_blink_sprite_first, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        }

        /* Health bar: blinks below 30%. */
        fill = g_mission_state.health * 0.01f;
        if (fill > 0.3f) {
            data->blinkOn = 1;
        } else if (math_fast_float_d(&data->blinkTimer)) {
            data->blinkTimer = 4;
            data->blinkOn ^= 1;
        }
        colors[1] = FastTweenColor(0x800000ff, 0x8000ff00, fill);
        colors[0] = 0x800000ff;
        tmp = fill * 200.0f + 156.0f;
        if (data->blinkOn)
            gfx_draw_screen_rectangle(156, 14, (s32)tmp, 27, 1, colors);

        /* Ammo bar. */
        idx = table_find_last_used_entry(7);
        ratio = IntToFloat(g_reward_slot_table[idx].value);
        fill = ratio / IntToFloat(g_reward_slot_table[idx].maxAmmo);
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

        /* Weapon icons and the fill count. */
        b0 = g_hud_color_block_first;
        b1 = g_hud_color_block_second;
        b2 = g_hud_color_block_third;
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 1), 21, 7, 30, 30, &b1);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 0), 21, 7, 30, 30, &b0);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, g_reward_slot_table[table_find_last_used_entry(g_mission_record_index)].icon), 21, 7, 30, 30, &b2);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 1), 462, 9, 30, 30, &b1);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, g_reward_slot_table[table_find_last_used_entry(7)].icon), 462, 9, 30, 30, &b2);
        sprintf(text, g_str_hud_value_format, g_reward_slot_table[table_find_last_used_entry(g_mission_record_index)].value,
                      g_reward_slot_table[table_find_last_used_entry(g_mission_record_index)].maxAmmo);
        text_draw_small(67, 5, 0x80808080, text, 128);

        /* Weapon switch. */
        func_PAL_L05_00328198(2);
        newidx = level_lookup_step_table();
        if (newidx >= 0) {
            g_reward_slot_table[table_find_last_used_entry(g_mission_record_index)].active = 0;
            g_mission_record_index = newidx;
            g_reward_slot_table[table_find_last_used_entry(newidx)].active = 1;
        }
        gfx_draw_scaled_object(g_hud_label_sprite_third, x, y, 0x80f0f0f0, 1.0f, 0.0f);
    }

    func_PAL_0029C7F0();
    sprite0 = table_find_by_id(g_hud_sprite_table_base + 0x8710, 186);
    /* data, done with, holds the second sprite. */
    data = table_find_by_id(g_hud_sprite_table_base + 0x8710, 187);
    sprite2 = table_find_by_id(g_hud_sprite_table_base + 0x8710, 188);
    gfx_draw_scaled_object(sprite0, g_hud_label_offset_x + 4.0f, label_y(sprite0, g_hud_label_offset_y + 4.0f, g_screen_l10_scale, 0.5f, 1), 0x60442d00, 0.8f, 0.0f);
    gfx_draw_scaled_object(data, g_hud_label_offset_x + 4.0f, label_y(data, g_hud_label_offset_y + 4.0f, g_screen_l10_scale, 0.5f, 1), 0x60241700, 0.8f, 0.0f);
    gfx_draw_scaled_object(sprite2, g_hud_label_offset_x + 4.0f, label_y(sprite2, g_hud_label_offset_y + 4.0f, g_screen_l10_scale, 0.5f, 1), 0x55f0c070, 0.8f, 0.0f);
    hud_draw_object_markers();
    return 1;
}
