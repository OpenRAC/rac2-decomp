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

extern s32 object_init_type_pointer();
extern s32 object_construct_derived_a();
extern s32 object_construct_derived_c();
extern s32 hud_construct_widget_base();
extern s32 menu_clear_sixteen_words();
extern s32 effect_clear_row_groups();
extern s32 meter_screen_init_parts();

extern s8 D_001AD928[];
extern s8 D_001AD908[];
/* Builds the empty HUD object: starts every text, sprite, meter and animation part so the HUD can be filled in later. */
s32 hud_construct(s32 hud) {
    s32 anim14D4;
    s32 fade1160;
    s32 fade1288;
    s32 fade13B0;
    s32 fadeF1C;
    s32 fade1044;
    s32 fade11F4;
    s32 fade131C;
    s32 link1444;
    s32 animE0C;
    s32 link1448;
    s32 fadeFB0;
    s32 anim144C;
    s32 anim10D8;
    s32 animE94;
    s32 slotPtr;
    s32 iconPtr;
    s32 slotLeft;
    s32 iconLeft;

    slotLeft = 7;
    slotPtr = hud + 0x358;
    object_construct_derived_a(hud);
    object_construct_derived_a(hud + 0x4C);
    object_construct_derived_a(hud + 0x98);
    hud_construct_widget_base(hud + 0x100);
    object_construct_derived_c(hud + 0x148);
    object_construct_derived_a(hud + 0x184);
    object_construct_derived_a(hud + 0x1D0);
    hud_construct_widget_base(hud + 0x238);
    object_construct_derived_c(hud + 0x280);
    object_construct_derived_a(hud + 0x2C0);
    object_construct_derived_a(hud + 0x30C);
    do {
        slotLeft -= 1;
        object_construct_derived_a(slotPtr);
        slotPtr += 0x4C;
    } while (slotLeft != -1);
    iconPtr = hud + 0x604;
    object_construct_derived_a(hud + 0x5B8);
    iconLeft = 7;
    animE0C = hud + 0xE0C;
    animE94 = hud + 0xE94;
    fadeF1C = hud + 0xF1C;
    fadeFB0 = hud + 0xFB0;
    fade1044 = hud + 0x1044;
    anim10D8 = hud + 0x10D8;
    fade1160 = hud + 0x1160;
    fade11F4 = hud + 0x11F4;
    fade1288 = hud + 0x1288;
    fade131C = hud + 0x131C;
    fade13B0 = hud + 0x13B0;
    link1444 = hud + 0x1444;
    link1448 = hud + 0x1448;
    anim144C = hud + 0x144C;
    anim14D4 = hud + 0x14D4;
    do {
        iconLeft -= 1;
        object_construct_derived_c(iconPtr);
        iconPtr += 0x3C;
    } while (iconLeft != -1);
    meter_screen_init_parts(hud + 0x7E8);
    menu_clear_sixteen_words(hud + 0xBEC);
    menu_clear_sixteen_words(hud + 0xC74);
    menu_clear_sixteen_words(hud + 0xCFC);
    menu_clear_sixteen_words(hud + 0xD84);
    menu_clear_sixteen_words(animE0C);
    menu_clear_sixteen_words(animE94);
    effect_clear_row_groups(fadeF1C);
    effect_clear_row_groups(fadeFB0);
    effect_clear_row_groups(fade1044);
    menu_clear_sixteen_words(anim10D8);
    effect_clear_row_groups(fade1160);
    effect_clear_row_groups(fade11F4);
    effect_clear_row_groups(fade1288);
    effect_clear_row_groups(fade131C);
    effect_clear_row_groups(fade13B0);
    object_init_type_pointer(link1444);
    (*(s32 *)((s8 *)(hud) + (0x1444))) = ((s32)D_001AD928);
    object_init_type_pointer(link1448);
    (*(s32 *)((s8 *)(hud) + (0x1448))) = ((s32)D_001AD908);
    menu_clear_sixteen_words(anim144C);
    menu_clear_sixteen_words(anim14D4);
    return hud;
}
