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

extern s32 g_choice_slide_choice __attribute__((sda));
extern s32 g_choice_slide_values __attribute__((sda));
extern s8 g_menu_choice_number_source[];
extern s8 g_menu_choice_counter[];

/* Sets the given menu item to show the current choice and starts it sliding in from the side when the choice changed, then moves on to the next choice. */
s32 menu_choice_slide_init(s32 display) {
    s32 choice_number;
    s32 byte_offset;

    choice_number = *(s32 *)g_menu_choice_number_source;
    if (g_choice_slide_choice != choice_number) {
        (*(s32 *)((s8 *)(display) + (0x3C))) = -0x2BC;
        g_choice_slide_choice = choice_number;
    }
    byte_offset = choice_number * 4;
    (*(s32 *)((s8 *)(display) + (0x34))) = *(s32 *)((s8 *)&g_choice_slide_values + byte_offset);
    *(s32 *)g_menu_choice_counter = choice_number + 1;
    return 0;
}
