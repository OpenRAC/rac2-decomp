#include "names.h"
/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "common.h"

extern s32 GetLocalizedString();
extern s32 object_get_fourth_field();
extern s32 object_set_second_float4(s32, f32, f32, f32, f32);
extern s32 object_init_derived_arrays();
extern s32 object_set_helper_result();
extern s32 object_init_derived_b();
extern s32 object_set_first_pair();
extern s32 object_set_second_pair();
extern s32 object_init_derived_c();
extern s32 hud_init_widget_defaults();
extern s32 hud_set_widget_field_a();
extern s32 hud_set_widget_field_b();
extern s32 meter_set_max();
extern s32 meter_set_value();
extern s32 widget_store_field();
extern s32 widget_set_pos_y();
extern s32 text_set_alignment();
extern s32 ui_return_second_arg();
extern s32 pool_alloc_cell();
extern s32 UpdateItemGridMenu();
extern s32 D_001A8CFC;
extern s8 D_001AE4D8[];
extern s8 D_001ADFC0[];
extern s8 D_001ADFA0[];
extern s8 D_001ADFD8[];
extern s8 D_001ADC18[];
extern s8 D_001ADC10[];
extern s8 D_001ADFC8[];
extern s8 D_001ADC28[];
extern s8 D_001ADFD0[];
extern s8 D_001AE4D0[];
extern s8 D_001AE040[];
extern s8 D_001ADC30[];
extern s8 D_001AE4E8[];
extern s8 D_001AE4F8[];

/* Sets up the item grid menu: creates all its texts, icons and bars, gives them colors and places them in the grid. */
void item_grid_menu_init(s32 menu, s32 context) {
    s32 widget4C;
    s32 widget130;
    s32 widget98;
    s32 widget400;
    s32 widget44C;
    s32 widget_e4;
    s32 widget17C;
    s32 icon_widget;
    s32 text210;
    s32 text258;
    s32 text2A0;
    s32 text2E8;
    s32 text330;
    s32 *color_slot;
    s32 *color_slot2;
    s32 bar_widget;
    s32 backdrop_widget;
    s32 position_data;

    (*(s32 *)((s8 *)(menu) + (0x49C))) = context;
    if (context != 0) {
        position_data = ui_return_second_arg(0x10, pool_alloc_cell(context));
        (*(s32 *)((s8 *)(menu) + (0x498))) = position_data;
        (*(s32 *)((s8 *)(position_data) + (4))) = 0;
        (*(s32 *)((s8 *)(position_data) + (8))) = 0;
        (*(s32 *)((s8 *)(position_data) + (0xC))) = 0;
        (*(s32 *)((s8 *)(position_data) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(menu) + (0x4F8))) = 1;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(menu) + (0x498)))) + (0))) = 250.0f;
    widget4C = menu + 0x4C;
    bar_widget = menu + 0x1C8;
    widget130 = menu + 0x130;
    widget98 = menu + 0x98;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(menu) + (0x498)))) + (4))) = 207.0f;
    widget400 = menu + 0x400;
    object_init_derived_arrays(menu, D_001ADC10, context);
    widget44C = menu + 0x44C;
    object_init_derived_arrays(widget4C, D_001ADC18, context);
    object_init_derived_arrays(widget130, D_001ADFC8, context);
    widget_e4 = menu + 0xE4;
    object_init_derived_arrays(widget98, D_001ADC28, context);
    widget17C = menu + 0x17C;
    object_init_derived_arrays(widget400, D_001ADFD0, context);
    object_init_derived_arrays(widget44C, D_001AE4D0, context);
    object_init_derived_b(bar_widget, 0x20, 0, D_001AE040, context);
    widget_set_pos_y(bar_widget, 5);
    meter_set_max(bar_widget, 0x64);
    meter_set_value(bar_widget, 0);
    object_set_first_pair(bar_widget, 0x6049C1FF, 0x60001EFF);
    object_set_second_pair(bar_widget, 0x50F0C070, 0x50F0C070);
    icon_widget = menu + 0x378;
    text_set_alignment(bar_widget, 0x80000000);
    widget_store_field(bar_widget, 0);
    backdrop_widget = menu + 0x3B4;
    object_init_derived_arrays(widget_e4, D_001ADFC0, context);
    text210 = menu + 0x210;
    object_init_derived_arrays(widget17C, D_001AE4D8, context);
    text2A0 = menu + 0x2A0;
    text258 = menu + 0x258;
    color_slot = object_get_fourth_field(menu);
    text2E8 = menu + 0x2E8;
    *color_slot = 0x60442D00;
    color_slot2 = object_get_fourth_field(widget4C);
    text330 = menu + 0x330;
    *color_slot2 = 0x55F0C070;
    *(s32 *)object_get_fourth_field(widget130) = 0x80FFDE8D;
    *(s32 *)object_get_fourth_field(widget98) = 0x55F0C070;
    *(s32 *)object_get_fourth_field(widget_e4) = 0x80FFDE8D;
    *(s32 *)object_get_fourth_field(widget17C) = 0x60241700;
    *(s32 *)object_get_fourth_field(widget400) = 0x60442D00;
    *(s32 *)object_get_fourth_field(widget44C) = 0x55F0C070;
    object_set_helper_result(menu, D_001A8CFC + 0x8710, 0x21);
    object_set_helper_result(widget4C, D_001A8CFC + 0x8710, 0x22);
    object_set_helper_result(widget130, D_001A8CFC + 0x8710, 0x28);
    object_set_helper_result(widget98, D_001A8CFC + 0x8710, 0x23);
    object_set_helper_result(widget_e4, D_001A8CFC + 0x8710, 0x27);
    object_set_helper_result(widget17C, D_001A8CFC + 0x8710, 0x2A);
    object_set_helper_result(widget400, D_001A8CFC + 0x8710, 0x2C);
    object_set_helper_result(widget44C, D_001A8CFC + 0x8710, 0x2B);
    (*(s32 *)((s8 *)(menu) + (0x4FC))) = 0;
    (*(s32 *)((s8 *)(menu) + (0x500))) = 0;
    object_init_derived_c(icon_widget, D_001ADFD8, context);
    *(s32 *)object_get_fourth_field(icon_widget) = 0x60F0F0B0;
    object_set_second_float4(icon_widget, 32.0f, 32.0f, 0.0f, 0.0f);
    object_init_derived_arrays(backdrop_widget, D_001ADFA0, context);
    *(s32 *)object_get_fourth_field(backdrop_widget) = 0x60241700;
    object_set_helper_result(backdrop_widget, D_001A8CFC + 0x8710, 0x29);
    object_set_second_float4(backdrop_widget, 1.0f, 1.0f, 0.0f, 0.0f);
    hud_init_widget_defaults(text210, D_001ADC30, context);
    hud_init_widget_defaults(text258, D_001ADC30, context);
    hud_set_widget_field_a(text258, 1);
    hud_init_widget_defaults(text2A0, D_001ADC30, context);
    hud_set_widget_field_a(text2A0, 1);
    hud_init_widget_defaults(text2E8, D_001AE4E8, context);
    hud_set_widget_field_a(text2E8, 1);
    hud_init_widget_defaults(text330, D_001AE4F8, context);
    hud_set_widget_field_a(text330, 1);
    *(s32 *)object_get_fourth_field(text210) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(text258) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(text2A0) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(text2E8) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(text330) = 0x80F0F0F0;
    hud_set_widget_field_b(text210, GetLocalizedString(0x2D51));
    hud_set_widget_field_b(text258, menu + 0x4A0);
    hud_set_widget_field_b(text2A0, menu + 0x4B8);
    UpdateItemGridMenu(menu, 0);
}
