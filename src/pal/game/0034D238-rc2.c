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

extern void *object_init_type_pointer();
extern void *object_construct_derived_a();
extern void *object_construct_derived_c();
extern char *hud_construct_widget_base();
extern u8 *menu_clear_sixteen_words();
extern u8 *effect_clear_row_groups();
extern char *meter_screen_init_parts();

extern s8 g_meter_vtable_a[];
extern s8 g_meter_vtable_b[];
/* Builds the empty HUD object: starts every text, sprite, meter and animation part so the HUD can be filled in later (PAL: same as hud_construct, with a different layout after +0x100). */
s32 hud_construct_pal(s32 hud) {
    s32 part_1214;
    s32 part_133c;
    s32 part_1464;
    s32 part_e2c;
    s32 part_1468;
    s32 part_fd0;
    s32 part_146c;
    s32 part_10f8;
    s32 part_eb4;
    s32 part_14f4;
    s32 part_1180;
    s32 part_12a8;
    s32 part_13d0;
    s32 part_f3c;
    s32 part_1064;
    s32 text_ptr;
    s32 sprite_ptr;
    s32 text_count;
    s32 sprite_count;

    text_count = 7;
    text_ptr = hud + 0x378;
    object_construct_derived_a(hud);
    object_construct_derived_a(hud + 0x4C);
    object_construct_derived_a(hud + 0x98);
    hud_construct_widget_base(hud + 0x100);
    object_construct_derived_c(hud + 0x158);
    object_construct_derived_a(hud + 0x194);
    object_construct_derived_a(hud + 0x1e0);
    hud_construct_widget_base(hud + 0x248);
    object_construct_derived_c(hud + 0x2a0);
    object_construct_derived_a(hud + 0x2e0);
    object_construct_derived_a(hud + 0x32c);
    do {
        text_count -= 1;
        object_construct_derived_a(text_ptr);
        text_ptr += 0x4C;
    } while (text_count != -1);
    sprite_ptr = hud + 0x624;
    object_construct_derived_a(hud + 0x5d8);
    sprite_count = 7;
    part_e2c = hud + 0xe2c;
    part_eb4 = hud + 0xeb4;
    part_f3c = hud + 0xf3c;
    part_fd0 = hud + 0xfd0;
    part_1064 = hud + 0x1064;
    part_10f8 = hud + 0x10f8;
    part_1180 = hud + 0x1180;
    part_1214 = hud + 0x1214;
    part_12a8 = hud + 0x12a8;
    part_133c = hud + 0x133c;
    part_13d0 = hud + 0x13d0;
    part_1464 = hud + 0x1464;
    part_1468 = hud + 0x1468;
    part_146c = hud + 0x146c;
    part_14f4 = hud + 0x14f4;
    do {
        sprite_count -= 1;
        object_construct_derived_c(sprite_ptr);
        sprite_ptr += 0x3C;
    } while (sprite_count != -1);
    meter_screen_init_parts(hud + 0x808);
    menu_clear_sixteen_words(hud + 0xc0c);
    menu_clear_sixteen_words(hud + 0xc94);
    menu_clear_sixteen_words(hud + 0xd1c);
    menu_clear_sixteen_words(hud + 0xda4);
    menu_clear_sixteen_words(part_e2c);
    menu_clear_sixteen_words(part_eb4);
    effect_clear_row_groups(part_f3c);
    effect_clear_row_groups(part_fd0);
    effect_clear_row_groups(part_1064);
    menu_clear_sixteen_words(part_10f8);
    effect_clear_row_groups(part_1180);
    effect_clear_row_groups(part_1214);
    effect_clear_row_groups(part_12a8);
    effect_clear_row_groups(part_133c);
    effect_clear_row_groups(part_13d0);
    object_init_type_pointer(part_1464);
    (*(s32 *)((s8 *)(hud) + (0x1464))) = ((s32)g_meter_vtable_a);
    object_init_type_pointer(part_1468);
    (*(s32 *)((s8 *)(hud) + (0x1468))) = ((s32)g_meter_vtable_b);
    menu_clear_sixteen_words(part_146c);
    menu_clear_sixteen_words(part_14f4);
    return hud;
}
