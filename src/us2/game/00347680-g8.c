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
/* func_US2_00347680, the USA v2.00 copy of func_00346710: the same C for a smaller object. */
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
extern void hud_init_widget_defaults_us2();
extern void hud_set_widget_field_a();
extern void hud_set_widget_field_b();
extern void func_US2_00337A38();
extern void meter_set_value();
extern void widget_store_field();
extern void widget_set_pos_y();
extern void text_set_alignment();
extern void *ui_return_second_arg();
extern void *pool_alloc_cell();
extern s32 UpdateItemGridMenu_us2();
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

/* Builds the item grid menu: allocates its position, creates its widgets, the ammo bar and the icon, and
   places the first cell (USA v2.00 copy, a smaller object). */
void item_grid_menu_init_us2(s32 menu, s32 parent) {
    s32 part_4c;
    s32 part_130;
    s32 part_98;
    s32 part_3a0;
    s32 part_3ec;
    s32 part_e4;
    s32 part_17c;
    s32 label_2c0;
    s32 *color_ptr;
    s32 *color_ptr_2;
    s32 bar;
    s32 backdrop;
    s32 position;

    (*(s32 *)((s8 *)(menu) + (0x43C))) = parent;
    if (parent != 0) {
        position = ui_return_second_arg(0x10, pool_alloc_cell(parent));
        (*(s32 *)((s8 *)(menu) + (0x438))) = position;
        (*(s32 *)((s8 *)(position) + (4))) = 0;
        (*(s32 *)((s8 *)(position) + (8))) = 0;
        (*(s32 *)((s8 *)(position) + (0xC))) = 0;
        (*(s32 *)((s8 *)(position) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(menu) + (0x4C0))) = 1;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(menu) + (0x438)))) + (0))) = 250.0f;
    part_4c = menu + 0x4C;
    bar = menu + 0x1C8;
    part_130 = menu + 0x130;
    part_98 = menu + 0x98;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(menu) + (0x438)))) + (4))) = 207.0f;
    part_3a0 = menu + 0x3A0;
    object_init_derived_arrays(menu, g_menu_widget_desc_first, parent);
    part_3ec = menu + 0x3EC;
    object_init_derived_arrays(part_4c, g_menu_widget_desc_second, parent);
    object_init_derived_arrays(part_130, g_menu_panel_desc, parent);
    part_e4 = menu + 0xE4;
    object_init_derived_arrays(part_98, g_menu_widget_desc_fourth, parent);
    part_17c = menu + 0x17C;
    object_init_derived_arrays(part_3a0, g_menu_extra_widget_desc, parent);
    object_init_derived_arrays(part_3ec, g_item_grid_array_init_a, parent);
    object_init_derived_b(bar, 0x20, 0, g_menu_bar_desc, parent);
    widget_set_pos_y(bar, 5);
    func_US2_00337A38(bar, 0x64);
    meter_set_value(bar, 0);
    object_set_first_pair(bar, 0x6049C1FF, 0x60001EFF);
    object_set_second_pair(bar, 0x50F0C070, 0x50F0C070);
    text_set_alignment(bar, 0x80000000);
    widget_store_field(bar, 0);
    backdrop = menu + 0x354;
    object_init_derived_arrays(part_e4, g_menu_frame_desc, parent);
    object_init_derived_arrays(part_17c, g_item_grid_array_init_b, parent);
    color_ptr = object_get_fourth_field(menu);
    label_2c0 = menu + 0x2C0;
    *color_ptr = 0x60442D00;
    color_ptr_2 = object_get_fourth_field(part_4c);
    *color_ptr_2 = 0x55F0C070;
    *(s32 *)object_get_fourth_field(part_130) = 0x80FFDE8D;
    *(s32 *)object_get_fourth_field(part_98) = 0x55F0C070;
    *(s32 *)object_get_fourth_field(part_e4) = 0x80FFDE8D;
    *(s32 *)object_get_fourth_field(part_17c) = 0x60241700;
    *(s32 *)object_get_fourth_field(part_3a0) = 0x60442D00;
    *(s32 *)object_get_fourth_field(part_3ec) = 0x55F0C070;
    object_set_helper_result(menu, g_resident_data_base + 0x8710, 0x21);
    object_set_helper_result(part_4c, g_resident_data_base + 0x8710, 0x22);
    object_set_helper_result(part_130, g_resident_data_base + 0x8710, 0x28);
    object_set_helper_result(part_98, g_resident_data_base + 0x8710, 0x23);
    object_set_helper_result(part_e4, g_resident_data_base + 0x8710, 0x27);
    object_set_helper_result(part_17c, g_resident_data_base + 0x8710, 0x2A);
    object_set_helper_result(part_3a0, g_resident_data_base + 0x8710, 0x2C);
    object_set_helper_result(part_3ec, g_resident_data_base + 0x8710, 0x2B);
    (*(s32 *)((s8 *)(menu) + (0x4C4))) = 0;
    (*(s32 *)((s8 *)(menu) + (0x4C8))) = 0;
    object_init_derived_c(menu + 0x318, g_menu_icon_desc, parent);
    *(s32 *)object_get_fourth_field(menu + 0x318) = 0x60F0F0B0;
    object_set_second_float4(menu + 0x318, 32.0f, 32.0f, 0.0f, 0.0f);
    object_init_derived_arrays(backdrop, g_menu_backdrop_desc, parent);
    *(s32 *)object_get_fourth_field(backdrop) = 0x60241700;
    object_set_helper_result(backdrop, g_resident_data_base + 0x8710, 0x29);
    object_set_second_float4(backdrop, 1.0f, 1.0f, 0.0f, 0.0f);
    hud_init_widget_defaults_us2(menu + 0x210, g_menu_hud_label_desc, parent);
    hud_init_widget_defaults_us2(menu + 0x268, g_menu_hud_label_desc, parent);
    hud_set_widget_field_a(menu + 0x268, 1);
    hud_init_widget_defaults_us2(label_2c0, g_menu_hud_label_desc, parent);
    hud_set_widget_field_a(label_2c0, 1);
    (*(s32 *)((s8 *)(label_2c0) + (0x48))) = 1;
    (*(s32 *)((s8 *)(label_2c0) + (0x4C))) = 200;
    *(s32 *)object_get_fourth_field(menu + 0x210) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(menu + 0x268) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(label_2c0) = 0x80F0F0F0;
    hud_set_widget_field_b(menu + 0x210, GetLocalizedString(0x2BE7));
    hud_set_widget_field_b(menu + 0x268, menu + 0x440);
    hud_set_widget_field_b(label_2c0, menu + 0x480);
    UpdateItemGridMenu_us2(menu, 0);
}
