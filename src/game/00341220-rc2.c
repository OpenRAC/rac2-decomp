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

extern void *memset(s8 *, s32, s32);
extern char *GetLocalizedString(s32);
extern s32 *object_get_fourth_field(s8 *);
extern void object_set_second_float4(s8 *, f32, f32, f32, f32);
extern void object_init_derived_arrays(s8 *, s8 *, s8 *);
extern void object_set_helper_result(s8 *, s32, s32);
extern void object_set_value_float(s8 *, f32);
extern void object_init_derived_c(s8 *, s8 *, s8 *);
extern void hud_set_widget_value_pair(s8 *, s32, s32);
extern void hud_init_widget_defaults(s8 *, s8 *, s8 *);
extern void hud_set_widget_field_b(s8 *, s32);
extern s8 *ui_return_second_arg(s32, s32);
extern void *pool_alloc_cell(s8 *);
extern void list_menu_reset_attach_items(s8 *, s8 *);
extern s32 D_001A8CFC;
extern s8 D_001ADC10[];
extern s8 D_001ADC18[];
extern s8 D_001ADC20[];
extern s8 D_001ADC28[];
extern s8 D_001ADC30[];
extern s8 D_001ADFC0[];
extern s8 D_001AE0C0[];

/* Sets up the parts of a tabbed menu: panels, frame, cursor, label and icon. */
void tab_menu_init(s8 *self, s8 *parent) {
    s8 *allocation;
    s8 *cursor;
    s8 *panel_one;
    s8 *panel_two;
    s8 *frame;
    s8 *icon;
    s8 *label;

    (*(s8 **)((s8 *)(self) + (0x21C))) = parent;
    if (parent != 0) {
        allocation = ui_return_second_arg(0x10, pool_alloc_cell(parent));
        (*(s8 **)((s8 *)(self) + (0x218))) = allocation;
        (*(s32 *)((s8 *)(allocation) + (4))) = 0;
        (*(s32 *)((s8 *)(allocation) + (8))) = 0;
        (*(s32 *)((s8 *)(allocation) + (0xC))) = 0;
        (*(s32 *)((s8 *)(allocation) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(self) + (0x220))) = 1;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(self) + (0x218)))) + (0))) = 251.0f;
    cursor = self + 0x98;
    panel_one = self + 0x4C;
    panel_two = self + 0xE4;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(self) + (0x218)))) + (4))) = 170.0f;
    frame = self + 0x130;
    object_init_derived_arrays(self, D_001ADC10, parent);
    icon = self + 0x17C;
    label = self + 0x1D0;
    object_init_derived_arrays(cursor, D_001ADC18, parent);
    object_init_derived_arrays(panel_one, D_001ADC20, parent);
    object_init_derived_arrays(panel_two, D_001ADC28, parent);
    object_init_derived_arrays(frame, D_001ADFC0, parent);
    hud_init_widget_defaults(label, D_001ADC30, parent);
    object_init_derived_c(icon, D_001AE0C0, parent);
    list_menu_reset_attach_items(self + 0x228, parent);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(cursor) = 0x80FFDE8D;
    *object_get_fourth_field(panel_one) = 0x55F0C070;
    *object_get_fourth_field(panel_two) = 0x55F0C070;
    *object_get_fourth_field(frame) = 0x70FFFEED;
    *object_get_fourth_field(label) = 0x80F0F0F0;
    *object_get_fourth_field(icon) = 0x60F0F0B0;
    object_set_value_float(self, 1.0f);
    object_set_value_float(panel_one, 1.0f);
    object_set_value_float(panel_two, 1.0f);
    object_set_helper_result(self, D_001A8CFC + 0x8710, 0x91);
    object_set_helper_result(cursor, D_001A8CFC + 0x8710, 0x94);
    object_set_helper_result(panel_one, D_001A8CFC + 0x8710, 0x92);
    object_set_helper_result(panel_two, D_001A8CFC + 0x8710, 0x93);
    object_set_helper_result(frame, D_001A8CFC + 0x8710, 0x95);
    object_set_second_float4(frame, 1.0f, 1.05f, 0.0f, 0.0f);
    hud_set_widget_field_b(label, GetLocalizedString(0x2D55));
    hud_set_widget_value_pair(icon, 0xEA9D, 0);
    memset(self + 0x1B8, 0, 12);
    object_set_second_float4(icon, 32.0f, 32.0f, 0.0f, 0.0f);
}
