#include "names.h"
/* func_0034B2C8 (6,048 bytes, 28 places). Own unit:
 * -O2 -G0 -ffunction-sections -frac2-keep-float-pun-source -frac2-sched-store-clobbered-first.
 * The last two PRE copies before a call store $v1 first, then $s5 in the delay slot, as retail;
 * the switch orders such sched2 ties (docs/build/compiler-notes.md). Owner standard of
 * 12 November 2026; forced on for every USA v1.01 unit it changes 89 functions.
 */
#include "common.h"

typedef union {
    s32 i;
    f32 f;
} HudBits_34B2C8;

extern char g_hud_ammo_bolt_widget_data_a[];
extern char g_hud_ammo_bolt_widget_data_b[];
extern char g_hud_ammo_bolt_widget_data_c[];
extern char g_hud_ammo_bolt_widget_data_d[];
extern char g_hud_ammo_bolt_widget_data_e[];
extern char g_hud_ammo_bolt_widget_data_f[];
extern char g_hud_ammo_bolt_widget_data_g[];
extern char g_hud_ammo_bolt_widget_data_h[];
extern char g_hud_ammo_bolt_widget_data_i[];
extern char g_ammo_bolt_widget_desc_first[];
extern char g_ammo_bolt_widget_desc_second[];
extern char g_ammo_bolt_widget_desc_third[];
extern char g_str_ammo_bolt_name_format_first[];
extern char g_str_ammo_bolt_name_format_second[];
extern s32 g_is_pal_video __attribute__((sda));
extern s32 g_player_bolts[] __attribute__((sda));

extern void object_init_derived_arrays(char *o, char *text, s32 arg);
extern void object_set_helper_result(char *o, char *font, s32 n);
extern void object_set_first_float4(char *o, f32 x, f32 y, f32 z, f32 w);
extern void object_set_second_float4(char *o, f32 x, f32 y, f32 z, f32 w);
extern s32 *object_get_fourth_field(char *o);
extern float *object_get_second_field(char *o);
extern s32 *object_get_first_field(char *o);
extern void *memset(void *dst, s32 c, s32 n);
extern void hud_init_widget_defaults(char *o, char *text, s32 arg);
extern void hud_set_widget_field_b(char *o, char *buf);
extern void hud_set_widget_field_a(char *o, s32 n);
extern void object_init_derived_c(char *o, char *text, s32 arg);
extern void hud_set_widget_value_pair(char *o, s32 id, s32 n);
extern void *pool_alloc_cell(s32 arg);
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

    *(f32 *)(o + 0x1288) = lo;
}

/* The ammo/bolt HUD setup: initialises the HUD's text, sprite and fade widgets. */
void hud_ammo_bolt_init(char *hud, char *font, s32 context)
{
    char *self = hud;
    char name_buf[16];
    s32 i;
    s32 color;
    f32 *zero_block;

    *(s32 *)(self + 0x157C) = 0;
    *(s32 *)(self + 0x1580) = 0;
    object_init_derived_arrays(self, g_hud_ammo_bolt_widget_data_a, context);
    object_set_helper_result(self, font + 0x8710, 1);
    object_set_first_float4(self, 10.0f, 10.0f, 0.0f, 0.0f);
    object_init_derived_arrays(self + 0x4C, g_hud_ammo_bolt_widget_data_b, context);
    object_set_first_float4(self + 0x4C, 10.0f, 10.0f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x4C, font + 0x8710, 2);
    object_init_derived_arrays(self + 0x98, g_hud_ammo_bolt_widget_data_c, context);
    object_set_first_float4(self + 0x98, 10.0f, 18.5f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x98, font + 0x8710, 5);
    memset(self + 0xE4, 0, 0x18);
    hud_init_widget_defaults(self + 0x100, g_hud_ammo_bolt_widget_data_d, context);
    object_set_second_float4(self + 0x100, 0.9f, 0.0f, 0.0f, 0.0f);
    hud_set_widget_field_b(self + 0x100, self + 0xE4);
    object_set_first_float4(self + 0x100, 64.0f, 15.0f, 0.0f, 0.0f);
    hud_set_widget_field_a(self + 0x100, 0);
    object_init_derived_c(self + 0x148, g_hud_ammo_bolt_widget_data_e, context);
    object_set_second_float4(self + 0x148, 32.0f, 32.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x148, 20.0f, 15.0f, 0.0f, 0.0f);
    *object_get_fourth_field(self + 0x148) = 0x60F0F0B0;
    object_init_derived_arrays(self + 0x184, g_hud_ammo_bolt_widget_data_f, context);
    object_set_first_float4(self + 0x184, 498.0f, 10.0f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x184, font + 0x8710, 3);
    object_init_derived_arrays(self + 0x1D0, g_hud_ammo_bolt_widget_data_g, context);
    object_set_first_float4(self + 0x1D0, 498.0f, 10.0f, 0.0f, 0.0f);
    object_set_helper_result(self + 0x1D0, font + 0x8710, 4);
    memset(self + 0x21C, 0, 0x18);
    hud_init_widget_defaults(self + 0x238, g_hud_ammo_bolt_widget_data_h, context);
    object_set_second_float4(self + 0x238, 0.9f, 0.0f, 0.0f, 0.0f);
    hud_set_widget_field_b(self + 0x238, self + 0x21C);
    object_set_first_float4(self + 0x238, 440.0f, 15.0f, 0.0f, 0.0f);
    hud_set_widget_field_a(self + 0x238, 2);
    object_init_derived_c(self + 0x280, g_hud_ammo_bolt_widget_data_i, context);
    object_set_second_float4(self + 0x280, 32.0f, 32.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x280, 457.0f, 15.0f, 0.0f, 0.0f);
    hud_set_widget_value_pair(self + 0x280, 0x7567, 0);

    if (context != 0) {
        zero_block = ui_return_second_arg(0x10, pool_alloc_cell(context));
        *(f32 **)(self + 0x7E4) = zero_block;
        zero_block[1] = 0.0f;
        zero_block[2] = 0.0f;
        zero_block[3] = 0.0f;
        zero_block[0] = 0.0f;
    }

    object_init_derived_arrays(self + 0x2C0, g_ammo_bolt_widget_desc_first, context);
    object_set_helper_result(self + 0x2C0, font + 0x8710, 7);
    object_set_second_float4(self + 0x2C0, 1.0f, 1.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x2C0, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0x442D00;
    *object_get_fourth_field(self + 0x2C0) = color;
    object_change_second_value(self + 0x2C0, *(f32 **)(self + 0x7E4));
    object_init_derived_arrays(self + 0x30C, g_ammo_bolt_widget_desc_second, context);
    object_set_helper_result(self + 0x30C, font + 0x8710, 6);
    object_set_second_float4(self + 0x30C, 1.0f, 1.0f, 0.0f, 0.0f);
    object_set_first_float4(self + 0x30C, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xF0C070;
    *object_get_fourth_field(self + 0x30C) = color;
    object_change_second_value(self + 0x30C, *(f32 **)(self + 0x7E4));
    object_init_derived_arrays(self + 0x5B8, g_ammo_bolt_widget_desc_third, context);
    object_set_helper_result(self + 0x5B8, font + 0x8710, 0x10);
    object_set_first_float4(self + 0x5B8, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xFFFEED;
    *object_get_fourth_field(self + 0x5B8) = color;
    object_set_flag_value(self + 0x5B8, 0);

    for (i = 0; i < 8; i++) {
        char *text_widget;
        char *icon_widget;
        f32 icon_angle;
        f32 icon_x;

        sprintf(name_buf, g_str_ammo_bolt_name_format_first, i);
        text_widget = self + (i * 0x4C + 0x358);
        object_init_derived_arrays(text_widget, name_buf, context);
        object_set_helper_result(text_widget, font + 0x8710, i + 8);
        object_set_second_float4(text_widget, 1.0f, 1.0f, 0.0f, 0.0f);
        object_set_first_float4(text_widget, 125.0f, 208.0f, 0.0f, 0.0f);
        object_change_second_value(text_widget, *(f32 **)(self + 0x7E4));
        color = 0x442D00;
        *object_get_fourth_field(text_widget) = color;
        sprintf(name_buf, g_str_ammo_bolt_name_format_second, i);
        icon_widget = self + (i * 0x3C + 0x604);
        object_init_derived_c(icon_widget, name_buf, context);
        object_set_flag_value(icon_widget, 0);
        icon_angle = FastAddRotations((f32)i * 2.0f * 0.39269909f - 3.14159274f, 1.57079637f);
        icon_x = (s32)(math_fast_sin_or_cos_a(icon_angle) * 82.14f) + 109;
        object_set_first_float4(icon_widget, icon_x, (s32)(math_fast_sin_or_cos_b(icon_angle) * 76.442f) + 189, 0.0f, 0.0f);
        object_set_second_float4(icon_widget, 32.0f, 32.0f, 0.0f, 0.0f);
        color = 0xF0F0B0;
        *object_get_fourth_field(icon_widget) = color;
    }
    {
        s32 j;

        for (j = 1; j < 8; j++) {
            object_change_first_value(self + 0x358 + j * 0x4C, object_get_second_field(self + 0x358));
            object_change_first_value(self + 0x604 + j * 0x3C, object_get_second_field(self + 0x604));
        }
    }
    object_change_first_value(self + 0x2C0, object_get_second_field(self + 0x358));

    hud_fade_widget_init(self + 0x7E8, font, context);
    menu_set_object_position(self + 0x7E8, 147.0f, 10.0f);
    hud_clear_0C_34B2C8(self + 0x7E8);

    fade_init(self + 0xBEC, context);
    effect_set_field_84(self + 0xBEC, 3);
    fade_set_parameter_row(self + 0xBEC, 0, 0.0f, hud_bits_34B2C8(0x442D00), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xBEC, 1, 0.3f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xBEC, 2, 1.0f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xBEC, 1, 0.0f, 2.0f);
    fade_set_field_2c(self + 0xBEC, object_get_fourth_field(self + 0x358));
    effect_set_field_20(self + 0xBEC, 0);
    fade_set_field_80(self + 0xBEC, self + 0x1448);
    fade_start_direction(self + 0xBEC, -1);
    fade_set_speed(self + 0xBEC, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xBEC, 0);

    fade_init(self + 0xC74, context);
    effect_set_field_84(self + 0xC74, 3);
    fade_set_parameter_row(self + 0xC74, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xC74, 1, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xC74, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xC74, object_get_second_field(self + 0x358));
    effect_set_field_20(self + 0xC74, 0);
    fade_set_field_80(self + 0xC74, self + 0x1444);
    fade_start_direction(self + 0xC74, -1);
    fade_set_speed(self + 0xC74, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xC74, 0);

    fade_init(self + 0xE0C, context);
    effect_set_field_84(self + 0xE0C, 3);
    fade_set_parameter_row(self + 0xE0C, 0, 0.0f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xE0C, 1, 0.5f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xE0C, 0, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xE0C, 2, 1.0f, hud_bits_34B2C8(0x60F0F0B0), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xE0C, 1, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xE0C, object_get_fourth_field(self + 0x604));
    effect_set_field_20(self + 0xE0C, 0);
    fade_set_field_80(self + 0xE0C, self + 0x1448);
    fade_start_direction(self + 0xE0C, -1);
    fade_set_speed(self + 0xE0C, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xE0C, 0);

    fade_init(self + 0xCFC, context);
    effect_set_field_84(self + 0xCFC, 3);
    fade_set_parameter_row(self + 0xCFC, 0, 0.0f, hud_bits_34B2C8(0xF0C070), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xCFC, 1, 0.3f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xCFC, 2, 1.0f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f);
    anim_set_key_range(self + 0xCFC, 1, 0.0f, 3.0f);
    fade_set_field_2c(self + 0xCFC, object_get_fourth_field(self + 0x30C));
    effect_set_field_20(self + 0xCFC, 0);
    fade_set_field_80(self + 0xCFC, self + 0x1448);
    fade_start_direction(self + 0xCFC, -1);
    fade_set_speed(self + 0xCFC, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xCFC, 0);

    fade_init(self + 0xD84, context);
    effect_set_field_84(self + 0xD84, 3);
    fade_set_parameter_row(self + 0xD84, 0, 0.0f, 1.2f, 1.2f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xD84, 1, 0.3f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xD84, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xD84, object_get_second_field(self + 0x30C));
    effect_set_field_20(self + 0xD84, 0);
    fade_set_field_80(self + 0xD84, self + 0x1444);
    fade_start_direction(self + 0xD84, -1);
    fade_set_speed(self + 0xD84, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xD84, 0);

    fade_init(self + 0xE94, context);
    effect_set_field_84(self + 0xE94, 3);
    fade_set_parameter_row(self + 0xE94, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xE94, 1, 0.01f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0xE94, 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0xE94, *(f32 **)(self + 0x7E4));
    effect_set_field_20(self + 0xE94, 0);
    fade_set_field_80(self + 0xE94, self + 0x1444);
    fade_start_direction(self + 0xE94, -1);
    fade_set_speed(self + 0xE94, g_is_pal_video != 0 ? 0.14f : 0.116666675f);
    fade_swap_field_28(self + 0xE94, 0);

    color_effect_init(self + 0xF1C, context);
    effect_set_table_slot(self + 0xF1C, 0, object_get_fourth_field(self));
    effect_set_table_slot_8c(self + 0xF1C, 0, 0x442D00);
    effect_set_table_slot_8c(self + 0xF1C, 1, 0x60442D00);
    hud_fade_range_34B2C8(self + 0xF1C, 0.0f, 2.0f);
    effect_set_table_slot(self + 0xF1C, 1, object_get_second_field(self));
    color_effect_set_grid_row(self + 0xF1C, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xF1C, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    effect_set_table_slot(self + 0xF1C, 2, object_get_first_field(self));
    color_effect_set_grid_row(self + 0xF1C, 2, 0, 50.0f, 25.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xF1C, 2, 1, 10.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0xFB0, context);
    effect_set_table_slot(self + 0xFB0, 0, object_get_fourth_field(self + 0x4C));
    effect_set_table_slot_8c(self + 0xFB0, 0, 0xF0C070);
    effect_set_table_slot_8c(self + 0xFB0, 1, 0x55F0C070);
    hud_fade_range_34B2C8(self + 0xF1C, 0.0f, 3.0f);
    effect_set_table_slot(self + 0xFB0, 1, object_get_second_field(self + 0x4C));
    color_effect_set_grid_row(self + 0xFB0, 1, 0, 1.2f, 1.2f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xFB0, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    effect_set_table_slot(self + 0xFB0, 2, object_get_first_field(self + 0x4C));
    color_effect_set_grid_row(self + 0xFB0, 2, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0xFB0, 2, 1, 10.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0x1044, context);
    effect_set_table_slot(self + 0x1044, 0, object_get_fourth_field(self + 0x100));
    effect_set_table_slot_8c(self + 0x1044, 0, 0xF0F0F0);
    effect_set_table_slot_8c(self + 0x1044, 1, 0x80F0F0F0);
    hud_fade_range_34B2C8(self + 0x1044, 0.0f, 3.0f);

    fade_init(self + 0x10D8, context);
    effect_set_field_84(self + 0x10D8, 3);
    fade_set_parameter_row(self + 0x10D8, 0, 0.0f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x10D8, 1, 0.5f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x10D8, 2, 1.0f, hud_bits_34B2C8(0x80001EFF), 0.0f, 0.0f, 0.0f);
    fade_set_field_2c(self + 0x10D8, object_get_fourth_field(self + 0x98));
    effect_set_field_20(self + 0x10D8, 0);
    fade_set_field_80(self + 0x10D8, self + 0x1448);
    fade_start_direction(self + 0x10D8, 1);
    fade_set_speed(self + 0x10D8, 0.06666f);

    color_effect_init(self + 0x1160, context);
    effect_set_table_slot(self + 0x1160, 0, object_get_fourth_field(self + 0x148));
    effect_set_table_slot_8c(self + 0x1160, 0, 0xF0F0B0);
    effect_set_table_slot_8c(self + 0x1160, 1, 0x60F0F0B0);
    hud_fade_range_34B2C8(self + 0x1160, 0.0f, 3.0f);
    fade_set_amount(self + 0x1160, 0.06666f);

    color_effect_init(self + 0x11F4, context);
    effect_set_table_slot(self + 0x11F4, 0, object_get_fourth_field(self + 0x184));
    effect_set_table_slot_8c(self + 0x11F4, 0, 0x442D00);
    effect_set_table_slot_8c(self + 0x11F4, 1, 0x60442D00);
    hud_fade_range_34B2C8(self + 0x11F4, 0.0f, 2.0f);
    effect_set_table_slot(self + 0x11F4, 1, object_get_second_field(self + 0x184));
    color_effect_set_grid_row(self + 0x11F4, 1, 0, 0.0f, 0.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x11F4, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    effect_set_table_slot(self + 0x11F4, 2, object_get_first_field(self + 0x184));
    color_effect_set_grid_row(self + 0x11F4, 2, 0, 458.0f, 25.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x11F4, 2, 1, 498.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0x1288, context);
    effect_set_table_slot(self + 0x1288, 0, object_get_fourth_field(self + 0x1D0));
    effect_set_table_slot_8c(self + 0x1288, 0, 0xF0C070);
    effect_set_table_slot_8c(self + 0x1288, 1, 0x55F0C070);
    hud_fade_range_34B2C8(self + 0x1288, 0.0f, 3.0f);
    effect_set_table_slot(self + 0x1288, 1, object_get_second_field(self + 0x1D0));
    color_effect_set_grid_row(self + 0x1288, 1, 0, 1.2f, 1.2f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x1288, 1, 1, 1.0f, 1.0f, 0.0f, 0.0f);
    hud_ammo_fade_lo_34B2C8(&hud, 0.0f);
    hud_fade_hi_34B2C8(self + 0x1288, 3.0f);
    effect_set_table_slot(self + 0x1288, 2, object_get_first_field(self + 0x1D0));
    color_effect_set_grid_row(self + 0x1288, 2, 0, 514.0f, 4.0f, 0.0f, 0.0f);
    color_effect_set_grid_row(self + 0x1288, 2, 1, 498.0f, 10.0f, 0.0f, 0.0f);

    color_effect_init(self + 0x131C, context);
    effect_set_table_slot(self + 0x131C, 0, object_get_fourth_field(self + 0x238));
    effect_set_table_slot_8c(self + 0x131C, 0, 0xF0F0F0);
    effect_set_table_slot_8c(self + 0x131C, 1, 0x80F0F0F0);
    hud_fade_range_34B2C8(self + 0x131C, 0.0f, 3.0f);

    color_effect_init(self + 0x13B0, context);
    effect_set_table_slot(self + 0x13B0, 0, object_get_fourth_field(self + 0x280));
    effect_set_table_slot_8c(self + 0x13B0, 0, 0xF0F0B0);
    effect_set_table_slot_8c(self + 0x13B0, 1, 0x60F0F0B0);
    hud_fade_range_34B2C8(self + 0x13B0, 0.0f, 3.0f);

    fade_init(self + 0x144C, context);
    effect_set_field_84(self + 0x144C, 2);
    fade_set_field_2c(self + 0x144C, object_get_fourth_field(self));
    fade_set_field_80(self + 0x144C, self + 0x1448);
    fade_set_speed(self + 0x144C, 0.02f);
    fade_set_parameter_row(self + 0x144C, 0, 0.0f, hud_bits_34B2C8(0x70202080), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x144C, 1, 1.0f, hud_bits_34B2C8(0x70242335), 0.0f, 0.0f, 0.0f);
    effect_set_field_20(self + 0x144C, 2);
    fade_start_direction(self + 0x144C, 1);
    fade_swap_field_28(self + 0x144C, 0);

    fade_init(self + 0x14D4, context);
    effect_set_field_84(self + 0x14D4, 2);
    fade_set_field_2c(self + 0x14D4, object_get_fourth_field(self + 0x4C));
    fade_set_field_80(self + 0x14D4, self + 0x1448);
    fade_set_speed(self + 0x14D4, 0.02f);
    fade_set_parameter_row(self + 0x14D4, 0, 0.0f, hud_bits_34B2C8(0x606060C0), 0.0f, 0.0f, 0.0f);
    fade_set_parameter_row(self + 0x14D4, 1, 1.0f, hud_bits_34B2C8(0x60424162), 0.0f, 0.0f, 0.0f);
    effect_set_field_20(self + 0x14D4, 2);
    fade_start_direction(self + 0x14D4, 1);
    fade_swap_field_28(self + 0x14D4, 0);

    *(s32 **)(self + 0x2BC) = g_player_bolts;
    *(s32 *)(self + 0x1564) = 0;
    *(s32 *)(self + 0x1568) = -1;
    *(s32 *)(self + 0x156C) = 0;
    *(s32 *)(self + 0x1570) = -1;
    *(s32 *)(self + 0x1574) = 0;
    *(s32 *)(self + 0x1578) = -1;
    menu_set_screen_mode_and_sound(self, 0);
    *(s32 *)(self + 0x1588) = save_count_items_above_baseline();
}
