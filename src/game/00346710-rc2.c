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

extern char *GetLocalizedString();
extern int *object_get_fourth_field();
extern void object_set_second_float4(s32, f32, f32, f32, f32);
extern void object_init_derived_arrays();
extern void object_set_helper_result();
extern void object_init_derived_b();
extern void object_set_first_pair();
extern void object_set_second_pair();
extern void object_init_derived_c();
extern void hud_init_widget_defaults();
extern void hud_set_widget_field_a();
extern void hud_set_widget_field_b();
extern void meter_set_max();
extern void meter_set_value();
extern void widget_store_field();
extern void widget_set_pos_y();
extern void text_set_alignment();
extern void *ui_return_second_arg();
extern void *pool_alloc_cell();
extern s32 UpdateItemGridMenu();
extern s32 g_resident_data_base;
extern s8 g_item_grid_array_init_b[];
extern s8 g_menu_frame_desc[];
extern s8 g_menu_backdrop_desc[];
extern s8 g_menu_icon_desc[];
extern s8 g_menu_widget_desc_second[];
extern s8 g_menu_widget_desc_first[];
extern s8 g_menu_panel_desc[];
extern s8 g_menu_widget_desc_fourth[];
extern s8 g_menu_extra_widget_desc[];
extern s8 g_item_grid_array_init_a[];
extern s8 g_menu_bar_desc[];
extern s8 g_menu_hud_label_desc[];
extern s8 g_item_grid_widget_defaults_a[];
extern s8 g_item_grid_widget_defaults_b[];

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
    object_init_derived_arrays(menu, g_menu_widget_desc_first, context);
    widget44C = menu + 0x44C;
    object_init_derived_arrays(widget4C, g_menu_widget_desc_second, context);
    object_init_derived_arrays(widget130, g_menu_panel_desc, context);
    widget_e4 = menu + 0xE4;
    object_init_derived_arrays(widget98, g_menu_widget_desc_fourth, context);
    widget17C = menu + 0x17C;
    object_init_derived_arrays(widget400, g_menu_extra_widget_desc, context);
    object_init_derived_arrays(widget44C, g_item_grid_array_init_a, context);
    object_init_derived_b(bar_widget, 0x20, 0, g_menu_bar_desc, context);
    widget_set_pos_y(bar_widget, 5);
    meter_set_max(bar_widget, 0x64);
    meter_set_value(bar_widget, 0);
    object_set_first_pair(bar_widget, 0x6049C1FF, 0x60001EFF);
    object_set_second_pair(bar_widget, 0x50F0C070, 0x50F0C070);
    icon_widget = menu + 0x378;
    text_set_alignment(bar_widget, 0x80000000);
    widget_store_field(bar_widget, 0);
    backdrop_widget = menu + 0x3B4;
    object_init_derived_arrays(widget_e4, g_menu_frame_desc, context);
    text210 = menu + 0x210;
    object_init_derived_arrays(widget17C, g_item_grid_array_init_b, context);
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
    object_set_helper_result(menu, g_resident_data_base + 0x8710, 0x21);
    object_set_helper_result(widget4C, g_resident_data_base + 0x8710, 0x22);
    object_set_helper_result(widget130, g_resident_data_base + 0x8710, 0x28);
    object_set_helper_result(widget98, g_resident_data_base + 0x8710, 0x23);
    object_set_helper_result(widget_e4, g_resident_data_base + 0x8710, 0x27);
    object_set_helper_result(widget17C, g_resident_data_base + 0x8710, 0x2A);
    object_set_helper_result(widget400, g_resident_data_base + 0x8710, 0x2C);
    object_set_helper_result(widget44C, g_resident_data_base + 0x8710, 0x2B);
    (*(s32 *)((s8 *)(menu) + (0x4FC))) = 0;
    (*(s32 *)((s8 *)(menu) + (0x500))) = 0;
    object_init_derived_c(icon_widget, g_menu_icon_desc, context);
    *(s32 *)object_get_fourth_field(icon_widget) = 0x60F0F0B0;
    object_set_second_float4(icon_widget, 32.0f, 32.0f, 0.0f, 0.0f);
    object_init_derived_arrays(backdrop_widget, g_menu_backdrop_desc, context);
    *(s32 *)object_get_fourth_field(backdrop_widget) = 0x60241700;
    object_set_helper_result(backdrop_widget, g_resident_data_base + 0x8710, 0x29);
    object_set_second_float4(backdrop_widget, 1.0f, 1.0f, 0.0f, 0.0f);
    hud_init_widget_defaults(text210, g_menu_hud_label_desc, context);
    hud_init_widget_defaults(text258, g_menu_hud_label_desc, context);
    hud_set_widget_field_a(text258, 1);
    hud_init_widget_defaults(text2A0, g_menu_hud_label_desc, context);
    hud_set_widget_field_a(text2A0, 1);
    hud_init_widget_defaults(text2E8, g_item_grid_widget_defaults_a, context);
    hud_set_widget_field_a(text2E8, 1);
    hud_init_widget_defaults(text330, g_item_grid_widget_defaults_b, context);
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
