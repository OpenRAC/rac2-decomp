/* func_PAL_0034D490 (6,048 bytes): PAL copy of func_0034B2C8 (src/game/0034B2C8-hud.c). */
#include "common.h"

typedef union {
    s32 i;
    f32 f;
} HudBits_34B2C8;

extern char D_001AE668[];
extern char D_001AE678[];
extern char D_001AE688[];
extern char D_001AE690[];
extern char D_001AE6A0[];
extern char D_001AE6B0[];
extern char D_001AE6C0[];
extern char D_001AE6D0[];
extern char D_001AE6E0[];
extern char D_001ADFE0[];
extern char D_001ADFF0[];
extern char D_001AE000[];
extern char D_001AE010[];
extern char D_001AE020[];
extern s32 g_is_pal_video __attribute__((sda));
extern s32 g_player_bolts[] __attribute__((sda));

extern void object_init_derived_arrays(char *o, char *text, s32 arg);
extern void object_set_helper_result(char *o, char *font, s32 n);
extern void object_set_first_float4(char *o, f32 x, f32 y, f32 z, f32 w);
extern void object_set_second_float4(char *o, f32 x, f32 y, f32 z, f32 w);
extern s32 *object_get_fourth_field(char *o);
extern s32 *object_get_second_field(char *o);
extern s32 *object_get_first_field(char *o);
extern void *memset(void *dst, s32 c, s32 n);
extern void hud_init_widget_defaults(char *o, char *text, s32 arg);
extern void hud_set_widget_field_b(char *o, char *buf);
extern void hud_set_widget_field_a(char *o, s32 n);
extern void object_init_derived_c(char *o, char *text, s32 arg);
extern void hud_set_widget_value_pair(char *o, s32 id, s32 n);
extern s32 pool_alloc_cell(s32 arg);
extern f32 *ui_return_second_arg(s32 n, s32 a);
extern void object_change_second_value(char *o, f32 *v);
extern void object_set_flag_value(char *o, s32 n);
extern int sprintf(char *buf, char *fmt, ...);
extern f32 FastAddRotations(f32 a, f32 b);
extern f32 math_fast_sin_or_cos_a(f32 a);
extern f32 math_fast_sin_or_cos_b(f32 a);
extern void object_change_first_value(char *o, s32 *v);
extern void hud_fade_widget_init(char *o, char *font, s32 arg);
extern void menu_set_object_position(char *o, f32 x, f32 y);
extern void fade_init(char *o, s32 arg);
extern void effect_set_field_84(char *o, s32 n);
extern void fade_set_parameter_row(char *o, s32 index, f32 weight, f32 x, f32 y, f32 z, f32 w);
extern void anim_set_key_range(char *o, s32 n, f32 a, f32 b);
extern void fade_set_field_2c(char *o, void *v);
extern void effect_set_field_20(char *o, s32 v);
extern void fade_set_field_80(char *o, char *v);
extern void fade_start_direction(char *o, s32 v);
extern void fade_set_speed(char *o, f32 v);
extern s32 fade_swap_field_28(char *o, s32 v);
extern void color_effect_init(char *o, s32 arg);
extern void effect_set_table_slot(char *o, s32 n, void *v);
extern void effect_set_table_slot_8c(char *o, s32 n, s32 v);
extern void color_effect_set_grid_row(char *o, s32 row, s32 group, f32 x, f32 y, f32 z, f32 w);
extern void fade_set_amount(char *o, f32 v);
extern void menu_set_screen_mode_and_sound(char *o, s32 mode);
extern s32 save_count_items_above_baseline(void);

static inline f32 hud_bits_34B2C8(s32 i)
{
    f32 f;

    *(s32 *)&f = i;
    return f;
}

/* Two float fields of a fade/blend object (+0x8, +0xC). */
static inline void hud_fade_range_34B2C8(char *o, f32 lo, f32 hi)
{
    *(f32 *)(o + 0x8) = lo;
    *(f32 *)(o + 0xC) = hi;
}

/* Two float fields of a fade/blend object (+0x0, +0x4). */
static inline void hud_fade_start_34B2C8(char *o, f32 lo, f32 hi)
{
    *(f32 *)(o + 0x0) = lo;
    *(f32 *)(o + 0x4) = hi;
}

/* An int field at +0xC. */
static inline void hud_clear_0C_34B2C8(char *o)
{
    *(s32 *)(o + 0xC) = 0;
}

static inline void hud_fade_hi_34B2C8(char *o, f32 hi)
{
    *(f32 *)(o + 0x4) = hi;
}

/* helper takes &o so the 0x1288 block uses a fresh base pseudo, as retail's PRE slot order shows; allowed by owner ruling (2026-11-09) */
static inline void hud_ammo_fade_lo_34B2C8(char **pobj, f32 lo)
{
    char *o = *pobj;

    *(f32 *)(o + 0x12A8) = lo;
}

/* The ammo/bolt HUD setup: initialises the HUD's text, sprite and fade widgets. */
void func_PAL_0034D490(char *o, char *font, s32 arg)
{
    char *self = o;
    char buf[16];
    s32 i;
    s32 color;
    f32 *v;

    *(s32 *)(self + 0x159C) = 0;
    *(s32 *)(self + 0x15A0) = 0;
    object_init_derived_arrays(self, D_001AE668, arg);
    object_set_helper_result(self, font + 0x8710, 1);
    object_set_first_float4(self, 10.0f, 10.0f, 0.0f, 0.0f);
    object_init_derived_arrays(self + 0x4C, D_001AE678, arg);
    object_set_first_float4(self + 0x4C, 10.0f, 10.0f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x4C, font + 0x8710, 2);
    object_init_derived_arrays(self + 0x98, D_001AE688, arg);
    object_set_first_float4(self + 0x98, 10.0f, 18.5f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x98, font + 0x8710, 5);
    memset(self + 0xE4, 0, 0x18);
    hud_init_widget_defaults(self + 0x100, D_001AE690, arg);
    object_set_second_float4(self + 0x100, 0.9f, 0.0f, 0.0f, 0.0f);
    hud_set_widget_field_b(self + 0x100, self + 0xE4);
    object_set_first_float4(self + 0x100, 64.0f, 15.0f, 0.0f, 0.0f);
    hud_set_widget_field_a(self + 0x100, 0);
    object_init_derived_c(self + 0x158, D_001AE6A0, arg);
    object_set_second_float4(self + 0x158, 32.0f, 32.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x158, 20.0f, 15.0f, 0.0f, 0.0f);
    *object_get_fourth_field(self + 0x158) = 0x60F0F0B0;
    object_init_derived_arrays(self + 0x194, D_001AE6B0, arg);
    object_set_first_float4(self + 0x194, 498.0f, 10.0f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x194, font + 0x8710, 3);
    object_init_derived_arrays(self + 0x1E0, D_001AE6C0, arg);
    object_set_first_float4(self + 0x1E0, 498.0f, 10.0f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x1E0, font + 0x8710, 4);
    memset(self + 0x22C, 0, 0x18);
    hud_init_widget_defaults(self + 0x248, D_001AE6D0, arg);
    object_set_second_float4(self + 0x248, 0.9f, 0.0f, 0.0f, 0.0f);
    hud_set_widget_field_b(self + 0x248, self + 0x22C);
    object_set_first_float4(self + 0x248, 440.0f, 15.0f, 0.0f, 0.0f);
    hud_set_widget_field_a(self + 0x248, 2);
    object_init_derived_c(self + 0x2A0, D_001AE6E0, arg);
    object_set_second_float4(self + 0x2A0, 32.0f, 32.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x2A0, 457.0f, 15.0f, 0.0f, 0.0f);
    hud_set_widget_value_pair(self + 0x2A0, 0x7567, 0);

    if (arg != 0) {
        v = ui_return_second_arg(0x10, pool_alloc_cell(arg));
        *(f32 **)(self + 0x804) = v;
        v[1] = 0.0f;
        v[2] = 0.0f;
        v[3] = 0.0f;
        v[0] = 0.0f;
    }

    object_init_derived_arrays(self + 0x2E0, D_001ADFE0, arg);
    object_set_helper_result(self + 0x2E0, font + 0x8710, 7);
    object_set_second_float4(self + 0x2E0, 1.0f, 1.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x2E0, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0x442D00;
    *object_get_fourth_field(self + 0x2E0) = color;
    object_change_second_value(self + 0x2E0, *(f32 **)(self + 0x804));
    object_init_derived_arrays(self + 0x32C, D_001ADFF0, arg);
    object_set_helper_result(self + 0x32C, font + 0x8710, 6);
    object_set_second_float4(self + 0x32C, 1.0f, 1.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x32C, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xF0C070;
    *object_get_fourth_field(self + 0x32C) = color;
    object_change_second_value(self + 0x32C, *(f32 **)(self + 0x804));
    object_init_derived_arrays(self + 0x5D8, D_001AE000, arg);
    object_set_helper_result(self + 0x5D8, font + 0x8710, 0x10);
    object_set_first_float4(self + 0x5D8, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xFFFEED;
    *object_get_fourth_field(self + 0x5D8) = color;
    object_set_flag_value(self + 0x5D8, 0);

    for (i = 0; i < 8; i++) {
        char *w;
        char *ico;
        f32 angle;
        f32 x;

        sprintf(buf, D_001AE010, i);
        w = self + (i * 0x4C + 0x378);
        object_init_derived_arrays(w, buf, arg);
        object_set_helper_result(w, font + 0x8710, i + 8);
        object_set_second_float4(w, 1.0f, 1.0f, 0.0f, 0.0f);
        object_set_first_float4(w, 125.0f, 208.0f, 0.0f, 0.0f);
        object_change_second_value(w, *(f32 **)(self + 0x804));
        color = 0x442D00;
        *object_get_fourth_field(w) = color;
        sprintf(buf, D_001AE020, i);
        ico = self + (i * 0x3C + 0x624);
        object_init_derived_c(ico, buf, arg);
        object_set_flag_value(ico, 0);
        angle = FastAddRotations((f32)i * 2.0f * 0.39269909f - 3.14159274f, 1.57079637f);
        x = (s32)(math_fast_sin_or_cos_a(angle) * 82.14f) + 109;
        object_set_first_float4(ico, x, (s32)(math_fast_sin_or_cos_b(angle) * 76.442f) + 189, 0.0f, 0.0f);
        object_set_second_float4(ico, 32.0f, 32.0f, 0.0f, 0.0f);
        color = 0xF0F0B0;
        *object_get_fourth_field(ico) = color;
    }
    {
        s32 j;

        for (j = 1; j < 8; j++) {
            object_change_first_value(self + 0x378 + j * 0x4C, object_get_second_field(self + 0x378));
            object_change_first_value(self + 0x624 + j * 0x3C, object_get_second_field(self + 0x624));
        }
    }
    object_change_first_value(self + 0x2E0, object_get_second_field(self + 0x378));

    hud_fade_widget_init(self + 0x808, font, arg);
    menu_set_object_position(self + 0x808, 147.0f, 10.0f);
    hud_clear_0C_34B2C8(self + 0x808);

    fade_init(self + 0xC0C, arg);
    effect_set_field_84(self + 0xC0C, 3);
    fade_set_parameter_row(self + 0xC0C, 0, 0.0f, hud_bits_34B2C8(0x442D00), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xC0C, 1, 0.3f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xC0C, 2, 1.0f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xC0C, 1, 0.0f, 2.0f);
    fade_set_field_2c(self + 0xC0C, object_get_fourth_field(self + 0x378));
    effect_set_field_20(self + 0xC0C, 0);
    fade_set_field_80(self + 0xC0C, self + 0x1468);
    fade_start_direction(self + 0xC0C, -1);
    fade_set_speed(self + 0xC0C, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xC0C, 0);

    fade_init(self + 0xC94, arg);
    effect_set_field_84(self + 0xC94, 3);
    fade_set_parameter_row(self + 0xC94, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xC94, 1, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xC94, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xC94, object_get_second_field(self + 0x378));
    effect_set_field_20(self + 0xC94, 0);
    fade_set_field_80(self + 0xC94, self + 0x1464);
    fade_start_direction(self + 0xC94, -1);
    fade_set_speed(self + 0xC94, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xC94, 0);

    fade_init(self + 0xE2C, arg);
    effect_set_field_84(self + 0xE2C, 3);
    fade_set_parameter_row(self + 0xE2C, 0, 0.0f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xE2C, 1, 0.5f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xE2C, 0, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xE2C, 2, 1.0f, hud_bits_34B2C8(0x60F0F0B0), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xE2C, 1, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xE2C, object_get_fourth_field(self + 0x624));
    effect_set_field_20(self + 0xE2C, 0);
    fade_set_field_80(self + 0xE2C, self + 0x1468);
    fade_start_direction(self + 0xE2C, -1);
    fade_set_speed(self + 0xE2C, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xE2C, 0);

    fade_init(self + 0xD1C, arg);
    effect_set_field_84(self + 0xD1C, 3);
    fade_set_parameter_row(self + 0xD1C, 0, 0.0f, hud_bits_34B2C8(0xF0C070), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xD1C, 1, 0.3f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xD1C, 2, 1.0f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xD1C, 1, 0.0f, 3.0f);
    fade_set_field_2c(self + 0xD1C, object_get_fourth_field(self + 0x32C));
    effect_set_field_20(self + 0xD1C, 0);
    fade_set_field_80(self + 0xD1C, self + 0x1468);
    fade_start_direction(self + 0xD1C, -1);
    fade_set_speed(self + 0xD1C, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xD1C, 0);

    fade_init(self + 0xDA4, arg);
    effect_set_field_84(self + 0xDA4, 3);
    fade_set_parameter_row(self + 0xDA4, 0, 0.0f, 1.2f, 1.2f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xDA4, 1, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xDA4, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xDA4, object_get_second_field(self + 0x32C));
    effect_set_field_20(self + 0xDA4, 0);
    fade_set_field_80(self + 0xDA4, self + 0x1464);
    fade_start_direction(self + 0xDA4, -1);
    fade_set_speed(self + 0xDA4, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xDA4, 0);

    fade_init(self + 0xEB4, arg);
    effect_set_field_84(self + 0xEB4, 3);
    fade_set_parameter_row(self + 0xEB4, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xEB4, 1, 0.01f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xEB4, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xEB4, *(f32 **)(self + 0x804));
    effect_set_field_20(self + 0xEB4, 0);
    fade_set_field_80(self + 0xEB4, self + 0x1464);
    fade_start_direction(self + 0xEB4, -1);
    fade_set_speed(self + 0xEB4, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xEB4, 0);

    color_effect_init(self + 0xF3C, arg);
    effect_set_table_slot(self + 0xF3C, 0, object_get_fourth_field(self));
    effect_set_table_slot_8c(self + 0xF3C, 0, 0x442D00);
    effect_set_table_slot_8c(self + 0xF3C, 1, 0x60442D00);
    hud_fade_range_34B2C8(self + 0xF3C, 0.0f, 2.0f);
    effect_set_table_slot(self + 0xF3C, 1, object_get_second_field(self));
    color_effect_set_grid_row(self + 0xF3C, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xF3C, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    effect_set_table_slot(self + 0xF3C, 2, object_get_first_field(self));
    color_effect_set_grid_row(self + 0xF3C, 2, 0, 50.0f, 25.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xF3C, 2, 1, 10.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0xFD0, arg);
    effect_set_table_slot(self + 0xFD0, 0, object_get_fourth_field(self + 0x4C));
    effect_set_table_slot_8c(self + 0xFD0, 0, 0xF0C070);
    effect_set_table_slot_8c(self + 0xFD0, 1, 0x55F0C070);
    hud_fade_range_34B2C8(self + 0xF3C, 0.0f, 3.0f);
    effect_set_table_slot(self + 0xFD0, 1, object_get_second_field(self + 0x4C));
    color_effect_set_grid_row(self + 0xFD0, 1, 0, 1.2f, 1.2f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xFD0, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    effect_set_table_slot(self + 0xFD0, 2, object_get_first_field(self + 0x4C));
    color_effect_set_grid_row(self + 0xFD0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xFD0, 2, 1, 10.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0x1064, arg);
    effect_set_table_slot(self + 0x1064, 0, object_get_fourth_field(self + 0x100));
    effect_set_table_slot_8c(self + 0x1064, 0, 0xF0F0F0);
    effect_set_table_slot_8c(self + 0x1064, 1, 0x80F0F0F0);
    hud_fade_range_34B2C8(self + 0x1064, 0.0f, 3.0f);

    fade_init(self + 0x10F8, arg);
    effect_set_field_84(self + 0x10F8, 3);
    fade_set_parameter_row(self + 0x10F8, 0, 0.0f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x10F8, 1, 0.5f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x10F8, 2, 1.0f, hud_bits_34B2C8(0x80001EFF), 0.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0x10F8, object_get_fourth_field(self + 0x98));
    effect_set_field_20(self + 0x10F8, 0);
    fade_set_field_80(self + 0x10F8, self + 0x1468);
    fade_start_direction(self + 0x10F8, 1);
    fade_set_speed(self + 0x10F8, 0.06666f);

    color_effect_init(self + 0x1180, arg);
    effect_set_table_slot(self + 0x1180, 0, object_get_fourth_field(self + 0x158));
    effect_set_table_slot_8c(self + 0x1180, 0, 0xF0F0B0);
    effect_set_table_slot_8c(self + 0x1180, 1, 0x60F0F0B0);
    hud_fade_range_34B2C8(self + 0x1180, 0.0f, 3.0f);
    fade_set_amount(self + 0x1180, 0.06666f);

    color_effect_init(self + 0x1214, arg);
    effect_set_table_slot(self + 0x1214, 0, object_get_fourth_field(self + 0x194));
    effect_set_table_slot_8c(self + 0x1214, 0, 0x442D00);
    effect_set_table_slot_8c(self + 0x1214, 1, 0x60442D00);
    hud_fade_range_34B2C8(self + 0x1214, 0.0f, 2.0f);
    effect_set_table_slot(self + 0x1214, 1, object_get_second_field(self + 0x194));
    color_effect_set_grid_row(self + 0x1214, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x1214, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    effect_set_table_slot(self + 0x1214, 2, object_get_first_field(self + 0x194));
    color_effect_set_grid_row(self + 0x1214, 2, 0, 458.0f, 25.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x1214, 2, 1, 498.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0x12A8, arg);
    effect_set_table_slot(self + 0x12A8, 0, object_get_fourth_field(self + 0x1E0));
    effect_set_table_slot_8c(self + 0x12A8, 0, 0xF0C070);
    effect_set_table_slot_8c(self + 0x12A8, 1, 0x55F0C070);
    hud_fade_range_34B2C8(self + 0x12A8, 0.0f, 3.0f);
    effect_set_table_slot(self + 0x12A8, 1, object_get_second_field(self + 0x1E0));
    color_effect_set_grid_row(self + 0x12A8, 1, 0, 1.2f, 1.2f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x12A8, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    hud_ammo_fade_lo_34B2C8(&o, 0.0f);
    hud_fade_hi_34B2C8(self + 0x12A8, 3.0f);
    effect_set_table_slot(self + 0x12A8, 2, object_get_first_field(self + 0x1E0));
    color_effect_set_grid_row(self + 0x12A8, 2, 0, 514.0f, 4.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x12A8, 2, 1, 498.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0x133C, arg);
    effect_set_table_slot(self + 0x133C, 0, object_get_fourth_field(self + 0x248));
    effect_set_table_slot_8c(self + 0x133C, 0, 0xF0F0F0);
    effect_set_table_slot_8c(self + 0x133C, 1, 0x80F0F0F0);
    hud_fade_range_34B2C8(self + 0x133C, 0.0f, 3.0f);

    color_effect_init(self + 0x13D0, arg);
    effect_set_table_slot(self + 0x13D0, 0, object_get_fourth_field(self + 0x2A0));
    effect_set_table_slot_8c(self + 0x13D0, 0, 0xF0F0B0);
    effect_set_table_slot_8c(self + 0x13D0, 1, 0x60F0F0B0);
    hud_fade_range_34B2C8(self + 0x13D0, 0.0f, 3.0f);

    fade_init(self + 0x146C, arg);
    effect_set_field_84(self + 0x146C, 2);
    fade_set_field_2c(self + 0x146C, object_get_fourth_field(self));
    fade_set_field_80(self + 0x146C, self + 0x1468);
    fade_set_speed(self + 0x146C, 0.02f);
    fade_set_parameter_row(self + 0x146C, 0, 0.0f, hud_bits_34B2C8(0x70202080), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x146C, 1, 1.0f, hud_bits_34B2C8(0x70242335), 0.0f, 0.0f, 0.0f);
    effect_set_field_20(self + 0x146C, 2);
    fade_start_direction(self + 0x146C, 1);
    fade_swap_field_28(self + 0x146C, 0);

    fade_init(self + 0x14F4, arg);
    effect_set_field_84(self + 0x14F4, 2);
    fade_set_field_2c(self + 0x14F4, object_get_fourth_field(self + 0x4C));
    fade_set_field_80(self + 0x14F4, self + 0x1468);
    fade_set_speed(self + 0x14F4, 0.02f);
    fade_set_parameter_row(self + 0x14F4, 0, 0.0f, hud_bits_34B2C8(0x606060C0), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x14F4, 1, 1.0f, hud_bits_34B2C8(0x60424162), 0.0f, 0.0f, 0.0f);
    effect_set_field_20(self + 0x14F4, 2);
    fade_start_direction(self + 0x14F4, 1);
    fade_swap_field_28(self + 0x14F4, 0);

    *(s32 **)(self + 0x2DC) = g_player_bolts;
    *(s32 *)(self + 0x1584) = 0;
    *(s32 *)(self + 0x1588) = -1;
    *(s32 *)(self + 0x158C) = 0;
    *(s32 *)(self + 0x1590) = -1;
    *(s32 *)(self + 0x1594) = 0;
    *(s32 *)(self + 0x1598) = -1;
    menu_set_screen_mode_and_sound(self, 0);
    *(s32 *)(self + 0x15A8) = save_count_items_above_baseline();
}
