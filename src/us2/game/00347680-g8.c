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

extern s32 GetLocalizedString();
extern s32 object_get_fourth_field();
extern s32 object_set_second_float4(s32, f32, f32, f32, f32);
extern s32 object_init_derived_arrays();
extern s32 object_set_helper_result();
extern s32 object_init_derived_b();
extern s32 object_set_first_pair();
extern s32 object_set_second_pair();
extern s32 object_init_derived_c();
extern s32 func_US2_003377B0();
extern s32 hud_set_widget_field_a();
extern s32 hud_set_widget_field_b();
extern s32 func_US2_00337A38();
extern s32 meter_set_value();
extern s32 widget_store_field();
extern s32 widget_set_pos_y();
extern s32 text_set_alignment();
extern s32 ui_return_second_arg();
extern s32 pool_alloc_cell();
extern s32 func_US2_00347B88();
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

void func_US2_00347680(s32 arg0, s32 arg1) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp28;
    s32 *temp_v0_2;
    s32 *temp_v0_3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;

    (*(s32 *)((s8 *)(arg0) + (0x43C))) = arg1;
    if (arg1 != 0) {
        temp_v0 = ui_return_second_arg(0x10, pool_alloc_cell(arg1));
        (*(s32 *)((s8 *)(arg0) + (0x438))) = temp_v0;
        (*(s32 *)((s8 *)(temp_v0) + (4))) = 0;
        (*(s32 *)((s8 *)(temp_v0) + (8))) = 0;
        (*(s32 *)((s8 *)(temp_v0) + (0xC))) = 0;
        (*(s32 *)((s8 *)(temp_v0) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(arg0) + (0x4C0))) = 1;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(arg0) + (0x438)))) + (0))) = 250.0f;
    sp0 = arg0 + 0x4C;
    temp_s0 = arg0 + 0x1C8;
    sp4 = arg0 + 0x130;
    sp8 = arg0 + 0x98;
    (*(f32 *)((s8 *)((*(s32 *)((s8 *)(arg0) + (0x438)))) + (4))) = 207.0f;
    spC = arg0 + 0x3A0;
    object_init_derived_arrays(arg0, D_001ADC10, arg1);
    sp10 = arg0 + 0x3EC;
    object_init_derived_arrays(sp0, D_001ADC18, arg1);
    object_init_derived_arrays(sp4, D_001ADFC8, arg1);
    sp14 = arg0 + 0xE4;
    object_init_derived_arrays(sp8, D_001ADC28, arg1);
    sp18 = arg0 + 0x17C;
    object_init_derived_arrays(spC, D_001ADFD0, arg1);
    object_init_derived_arrays(sp10, D_001AE4D0, arg1);
    object_init_derived_b(temp_s0, 0x20, 0, D_001AE040, arg1);
    widget_set_pos_y(temp_s0, 5);
    func_US2_00337A38(temp_s0, 0x64);
    meter_set_value(temp_s0, 0);
    object_set_first_pair(temp_s0, 0x6049C1FF, 0x60001EFF);
    object_set_second_pair(temp_s0, 0x50F0C070, 0x50F0C070);
    text_set_alignment(temp_s0, 0x80000000);
    widget_store_field(temp_s0, 0);
    temp_s0_2 = arg0 + 0x354;
    object_init_derived_arrays(sp14, D_001ADFC0, arg1);
    object_init_derived_arrays(sp18, D_001AE4D8, arg1);
    temp_v0_2 = object_get_fourth_field(arg0);
    sp28 = arg0 + 0x2C0;
    *temp_v0_2 = 0x60442D00;
    temp_v0_3 = object_get_fourth_field(sp0);
    *temp_v0_3 = 0x55F0C070;
    *(s32 *)object_get_fourth_field(sp4) = 0x80FFDE8D;
    *(s32 *)object_get_fourth_field(sp8) = 0x55F0C070;
    *(s32 *)object_get_fourth_field(sp14) = 0x80FFDE8D;
    *(s32 *)object_get_fourth_field(sp18) = 0x60241700;
    *(s32 *)object_get_fourth_field(spC) = 0x60442D00;
    *(s32 *)object_get_fourth_field(sp10) = 0x55F0C070;
    object_set_helper_result(arg0, D_001A8CFC + 0x8710, 0x21);
    object_set_helper_result(sp0, D_001A8CFC + 0x8710, 0x22);
    object_set_helper_result(sp4, D_001A8CFC + 0x8710, 0x28);
    object_set_helper_result(sp8, D_001A8CFC + 0x8710, 0x23);
    object_set_helper_result(sp14, D_001A8CFC + 0x8710, 0x27);
    object_set_helper_result(sp18, D_001A8CFC + 0x8710, 0x2A);
    object_set_helper_result(spC, D_001A8CFC + 0x8710, 0x2C);
    object_set_helper_result(sp10, D_001A8CFC + 0x8710, 0x2B);
    (*(s32 *)((s8 *)(arg0) + (0x4C4))) = 0;
    (*(s32 *)((s8 *)(arg0) + (0x4C8))) = 0;
    object_init_derived_c(arg0 + 0x318, D_001ADFD8, arg1);
    *(s32 *)object_get_fourth_field(arg0 + 0x318) = 0x60F0F0B0;
    object_set_second_float4(arg0 + 0x318, 32.0f, 32.0f, 0.0f, 0.0f);
    object_init_derived_arrays(temp_s0_2, D_001ADFA0, arg1);
    *(s32 *)object_get_fourth_field(temp_s0_2) = 0x60241700;
    object_set_helper_result(temp_s0_2, D_001A8CFC + 0x8710, 0x29);
    object_set_second_float4(temp_s0_2, 1.0f, 1.0f, 0.0f, 0.0f);
    func_US2_003377B0(arg0 + 0x210, D_001ADC30, arg1);
    func_US2_003377B0(arg0 + 0x268, D_001ADC30, arg1);
    hud_set_widget_field_a(arg0 + 0x268, 1);
    func_US2_003377B0(sp28, D_001ADC30, arg1);
    hud_set_widget_field_a(sp28, 1);
    (*(s32 *)((s8 *)(sp28) + (0x48))) = 1;
    (*(s32 *)((s8 *)(sp28) + (0x4C))) = 200;
    *(s32 *)object_get_fourth_field(arg0 + 0x210) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(arg0 + 0x268) = 0x80F0F0F0;
    *(s32 *)object_get_fourth_field(sp28) = 0x80F0F0F0;
    hud_set_widget_field_b(arg0 + 0x210, GetLocalizedString(0x2BE7));
    hud_set_widget_field_b(arg0 + 0x268, arg0 + 0x440);
    hud_set_widget_field_b(sp28, arg0 + 0x480);
    func_US2_00347B88(arg0, 0);
}
