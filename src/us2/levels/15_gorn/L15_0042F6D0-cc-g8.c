/* func_US2_L15_0042F6D0, the USA v2.00 copy of func_L15_0042E1B0: the same C, where rename func_L05_003263F8 becomes func_US2_L05_00327640; rename func_L00_0030CF60 becomes func_US2_0029CC48. */
#include "common.h"

/* func_US2_L15_0042F6D0 (DrawGornStageHud): the Gorn stage HUD, ported from func_L10_00421790
   (L10_00421790-g8.c). The mission text for the current stage, the ship's health and ammo bars,
   the weapon icons and the three corner sprites.

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
    u8 pad00[0x10];
    s32 count;
    u8 pad14[0x14];
    s32 health;
} HudMissionState;

/* The HUD object's variables: the health bar blinks while health is low. */
typedef struct {
    u8 pad00[0x34];
    s32 blinkTimer;
    s32 blinkOn;
} HudBlinkVars;

extern u8 *g_gorn_hud_moby __attribute__((sda));
extern s32 g_challenge_menu_choice __attribute__((sda));
extern s32 g_gorn_hud_text_x __attribute__((sda));
extern s32 g_gorn_hud_icon_x __attribute__((sda));
extern s32 g_gorn_weapon_slot_index __attribute__((sda));
extern s32 g_gorn_course_miss_count __attribute__((sda));
extern void *g_label_sprite_a __attribute__((sda));
extern void *g_label_sprite_b __attribute__((sda));
extern void *g_label_sprite_c __attribute__((sda));
extern void *g_label_sprite_d __attribute__((sda));
extern void *g_label_sprite_e __attribute__((sda));
extern void *g_label_sprite_f __attribute__((sda));
extern u8 *g_challenge_menu_data MACRO_ADDR;
extern s32 g_gorn_hud_text_y MACRO_ADDR;
extern s32 g_gorn_hud_icon_y MACRO_ADDR;
extern f32 g_screen_l15_scale;
extern s32 g_screen_l15_mode MACRO_ADDR;
extern s32 g_screen_width MACRO_ADDR;
extern s32 g_gorn_course_timer MACRO_ADDR;
extern HudMissionState g_gorn_challenge_vars;
extern f32 g_label_offset_x, g_label_offset_y;
extern char g_str_gorn_label_count[], g_str_gorn_label_time[], g_str_gorn_label_value[];
extern Block g_gorn_hud_color_a, g_gorn_hud_color_b, g_gorn_hud_color_c;
extern HudWeapon g_weapon_l15_table[];

extern void gorn_hud_draw_sprites(s32, s32, s32, s32);
extern void *level_find_object_by_class_id(s32);
extern s32 group_count_alive(void *);
extern s32 CountActiveLinkedListObjects(void *);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern void text_draw_medium(s32, s32, u64, char *, s32);
extern s32 math_fast_float_d(s32 *);
extern void math_split_time_into_parts(s32, s32 *, s32 *, s32 *);
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
extern void func_US2_L05_00327640(s32);
extern s32 level_lookup_step_table(void);
extern void func_US2_0029CC48(void), hud_draw_object_markers(void);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l15_scale + 0.5f;

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
    int mode = g_screen_l15_mode;
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

s32 func_US2_L15_0042F6D0(void) {
    char text[128];
    char *label;
    u32 colors[2], colors2[2];
    Block b0, b1, b2;
    s32 a, b, c, idx, newidx, color, textX;
    HudBlinkVars *data = *(HudBlinkVars **)(g_gorn_hud_moby + 0x68);
    f32 x, y, ratio, tmp, base, end, fill, tweenColor;
    void *sprite0, *sprite2;

    switch (g_challenge_menu_choice) {
    case 0: {
        s32 textX2;

        gorn_hud_draw_sprites(0, 1, 0, 1);
        label = GetLocalizedString(0x3067);
        sprintf(text, g_str_gorn_label_count, label, group_count_alive(level_find_object_by_class_id(0x1211)));
        textX2 = g_gorn_hud_text_x - 60;
        text_draw_medium(textX2, label_y((void *)textX2, g_gorn_hud_text_y - 8, g_screen_l15_scale, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 1: {
        s32 textX2;

        gorn_hud_draw_sprites(0, 1, 0, 1);
        label = GetLocalizedString(0x3067);
        sprintf(text, g_str_gorn_label_count, label, g_gorn_challenge_vars.count);
        textX2 = g_gorn_hud_text_x - 60;
        text_draw_medium(textX2, label_y((void *)textX2, g_gorn_hud_text_y - 8, g_screen_l15_scale, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 2: {
        s32 textX2;

        gorn_hud_draw_sprites(0, 1, 0, 1);
        label = GetLocalizedString(0x3067);
        sprintf(text, g_str_gorn_label_count, label, CountActiveLinkedListObjects(level_find_object_by_class_id(0x1211)));
        textX2 = g_gorn_hud_text_x - 60;
        text_draw_medium(textX2, label_y((void *)textX2, g_gorn_hud_text_y - 8, g_screen_l15_scale, 0.5f, 1), 0x80808080, text, 128);
        break;
    }
    case 3: {
        f32 half = 0.5f;
        s32 textX2;

        gorn_hud_draw_sprites(1, 1, 0, 1);
        label = GetLocalizedString(0x306d);
        sprintf(text, g_str_gorn_label_count, label, g_gorn_course_miss_count);
        textX = g_gorn_hud_text_x - 60;
        text_draw_medium(textX, label_y((void *)textX, g_gorn_hud_text_y - 8, g_screen_l15_scale, half, 1), 0x80808080, text, 128);
        math_split_time_into_parts(g_gorn_course_timer, &a, &b, &c);
        label = GetLocalizedString(0x2e19);
        sprintf(text, g_str_gorn_label_time, label, a, b, c);
        textX2 = g_gorn_hud_icon_x - 80;
        text_draw_medium(textX2, label_y((void *)textX2, g_gorn_hud_icon_y - 8, g_screen_l15_scale, half, 1), 0x80808080, text, 128);
        break;
    }
    }

    if (g_challenge_menu_data) {
        g_label_sprite_a = table_find_by_id(g_challenge_menu_data + 0x8710, 128);
        g_label_sprite_b = table_find_by_id(g_challenge_menu_data + 0x8710, 129);
        g_label_sprite_c = table_find_by_id(g_challenge_menu_data + 0x8710, 130);
        g_label_sprite_d = table_find_by_id(g_challenge_menu_data + 0x8710, 131);
        g_label_sprite_e = table_find_by_id(g_challenge_menu_data + 0x8710, 132);
        g_label_sprite_f = table_find_by_id(g_challenge_menu_data + 0x8710, 133);
        x = IntToFloat(g_screen_width) * 0.5f;
        y = screen_coord(g_screen_l15_mode, 200.0f, 4.0f);
        gfx_draw_scaled_object(g_label_sprite_a, x, y, 0x60442d00, 1.0f, 0.0f);
        gfx_draw_scaled_object(g_label_sprite_b, x, y, 0x55f0c070, 1.0f, 0.0f);

        /* The weapon's level gauge, red to green in one, two or three segments. */
        idx = table_find_last_used_entry(6);
        ratio = IntToFloat(g_weapon_l15_table[idx].value) / IntToFloat(g_weapon_l15_table[idx].maxLevel);
        switch (idx) {
        case 6:
            if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio);
                gfx_draw_scaled_object(g_label_sprite_d, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 12:
            if (ratio > 0.5f) {
                ratio -= 0.5f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                gfx_draw_scaled_object(g_label_sprite_e, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_label_sprite_d, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio + ratio);
                gfx_draw_scaled_object(g_label_sprite_d, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        case 14:
            if (ratio > 0.6666667f) {
                ratio -= 0.6666667f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_label_sprite_f, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_label_sprite_e, x, y, 0x8000ff00, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_label_sprite_d, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.33333334f) {
                ratio -= 0.33333334f;
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_label_sprite_e, x, y, (s32)tweenColor, 1.0f, 0.0f);
                gfx_draw_scaled_object(g_label_sprite_d, x, y, 0x8000ff00, 1.0f, 0.0f);
            } else if (ratio > 0.0f) {
                tweenColor = FastTweenColor(0x800000ff, 0x8000ff00, ratio * 3.0f);
                gfx_draw_scaled_object(g_label_sprite_d, x, y, (s32)tweenColor, 1.0f, 0.0f);
            }
            break;
        }

        /* Health bar: blinks below 30%. */
        fill = g_gorn_challenge_vars.health * 0.01f;
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

        /* Ammo bar. */
        idx = table_find_last_used_entry(7);
        ratio = IntToFloat(g_weapon_l15_table[idx].value);
        fill = ratio / IntToFloat(g_weapon_l15_table[idx].maxAmmo);
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
        b0 = g_gorn_hud_color_a;
        b1 = g_gorn_hud_color_b;
        b2 = g_gorn_hud_color_c;
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 1), 21, 7, 30, 30, &b1);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 0), 21, 7, 30, 30, &b0);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, g_weapon_l15_table[table_find_last_used_entry(g_gorn_weapon_slot_index)].icon), 21, 7, 30, 30, &b2);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, 1), 462, 9, 30, 30, &b1);
        hud_draw_sprite_gradient(GetIconFrame(0xea97, g_weapon_l15_table[table_find_last_used_entry(7)].icon), 462, 9, 30, 30, &b2);
        sprintf(text, g_str_gorn_label_value, g_weapon_l15_table[table_find_last_used_entry(g_gorn_weapon_slot_index)].value,
                      g_weapon_l15_table[table_find_last_used_entry(g_gorn_weapon_slot_index)].maxAmmo);
        text_draw_small(67, 5, 0x80808080, text, 128);

        /* Weapon switch. */
        func_US2_L05_00327640(2);
        newidx = level_lookup_step_table();
        if (newidx >= 0) {
            g_weapon_l15_table[table_find_last_used_entry(g_gorn_weapon_slot_index)].active = 0;
            g_gorn_weapon_slot_index = newidx;
            g_weapon_l15_table[table_find_last_used_entry(newidx)].active = 1;
        }
        gfx_draw_scaled_object(g_label_sprite_c, x, y, 0x80f0f0f0, 1.0f, 0.0f);
    }

    func_US2_0029CC48();
    sprite0 = table_find_by_id(g_challenge_menu_data + 0x8710, 186);
    /* data, done with, holds the second sprite. */
    data = table_find_by_id(g_challenge_menu_data + 0x8710, 187);
    sprite2 = table_find_by_id(g_challenge_menu_data + 0x8710, 188);
    gfx_draw_scaled_object(sprite0, g_label_offset_x + 4.0f, label_y(sprite0, g_label_offset_y + 4.0f, g_screen_l15_scale, 0.5f, 1), 0x60442d00, 0.8f, 0.0f);
    gfx_draw_scaled_object(data, g_label_offset_x + 4.0f, label_y(data, g_label_offset_y + 4.0f, g_screen_l15_scale, 0.5f, 1), 0x60241700, 0.8f, 0.0f);
    gfx_draw_scaled_object(sprite2, g_label_offset_x + 4.0f, label_y(sprite2, g_label_offset_y + 4.0f, g_screen_l15_scale, 0.5f, 1), 0x55f0c070, 0.8f, 0.0f);
    hud_draw_object_markers();
    return 1;
}
