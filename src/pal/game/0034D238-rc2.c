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

/* func_PAL_0034D238, the PAL copy of func_0034B070: the same C, where the members after +0x100 move
 * and the spilled pointers take their stack slots in a different declaration order. */

extern s32 object_init_type_pointer();
extern s32 object_construct_derived_a();
extern s32 object_construct_derived_c();
extern s32 hud_construct_widget_base();
extern s32 menu_clear_sixteen_words();
extern s32 effect_clear_row_groups();
extern s32 meter_screen_init_parts();

extern s8 D_001AD928[];
extern s8 D_001AD908[];
s32 func_PAL_0034D238(s32 arg0) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s2_2;

    var_s2 = 7;
    var_s1 = arg0 + 0x378;
    object_construct_derived_a(arg0);
    object_construct_derived_a(arg0 + 0x4C);
    object_construct_derived_a(arg0 + 0x98);
    hud_construct_widget_base(arg0 + 0x100);
    object_construct_derived_c(arg0 + 0x158);
    object_construct_derived_a(arg0 + 0x194);
    object_construct_derived_a(arg0 + 0x1e0);
    hud_construct_widget_base(arg0 + 0x248);
    object_construct_derived_c(arg0 + 0x2a0);
    object_construct_derived_a(arg0 + 0x2e0);
    object_construct_derived_a(arg0 + 0x32c);
    do {
        var_s2 -= 1;
        object_construct_derived_a(var_s1);
        var_s1 += 0x4C;
    } while (var_s2 != -1);
    var_s1_2 = arg0 + 0x624;
    object_construct_derived_a(arg0 + 0x5d8);
    var_s2_2 = 7;
    spC = arg0 + 0xe2c;
    sp20 = arg0 + 0xeb4;
    sp34 = arg0 + 0xf3c;
    sp14 = arg0 + 0xfd0;
    sp38 = arg0 + 0x1064;
    sp1C = arg0 + 0x10f8;
    sp28 = arg0 + 0x1180;
    sp0 = arg0 + 0x1214;
    sp2C = arg0 + 0x12a8;
    sp4 = arg0 + 0x133c;
    sp30 = arg0 + 0x13d0;
    sp8 = arg0 + 0x1464;
    sp10 = arg0 + 0x1468;
    sp18 = arg0 + 0x146c;
    sp24 = arg0 + 0x14f4;
    do {
        var_s2_2 -= 1;
        object_construct_derived_c(var_s1_2);
        var_s1_2 += 0x3C;
    } while (var_s2_2 != -1);
    meter_screen_init_parts(arg0 + 0x808);
    menu_clear_sixteen_words(arg0 + 0xc0c);
    menu_clear_sixteen_words(arg0 + 0xc94);
    menu_clear_sixteen_words(arg0 + 0xd1c);
    menu_clear_sixteen_words(arg0 + 0xda4);
    menu_clear_sixteen_words(spC);
    menu_clear_sixteen_words(sp20);
    effect_clear_row_groups(sp34);
    effect_clear_row_groups(sp14);
    effect_clear_row_groups(sp38);
    menu_clear_sixteen_words(sp1C);
    effect_clear_row_groups(sp28);
    effect_clear_row_groups(sp0);
    effect_clear_row_groups(sp2C);
    effect_clear_row_groups(sp4);
    effect_clear_row_groups(sp30);
    object_init_type_pointer(sp8);
    (*(s32 *)((s8 *)(arg0) + (0x1464))) = ((s32)D_001AD928);
    object_init_type_pointer(sp10);
    (*(s32 *)((s8 *)(arg0) + (0x1468))) = ((s32)D_001AD908);
    menu_clear_sixteen_words(sp18);
    menu_clear_sixteen_words(sp24);
    return arg0;
}
