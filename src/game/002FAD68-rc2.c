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

extern s8 g_vendor_menu_state[];

/* Marks every entry for the given item in the shop list as owned. */
void shop_mark_item_owned(s32 item_id) {
    s32 i;
    s32 count;
    s32 owned_value;
    s8 *shop;
    s8 *shop_base;
    s8 *row;

    shop = g_vendor_menu_state;
    if ((*(s32 *)((s8 *)(shop) + (0x740))) > 0) {
        i = 0;
        shop_base = shop;
        owned_value = 1;
        row = shop_base + 0x150;
        do {
            if ((*(s32 *)((s8 *)(row) + (-0x10))) == item_id) {
                (*(s32 *)((s8 *)(row) + (0))) = owned_value;
            }
            row += 0x18;
            count = (*(s32 *)((s8 *)(shop_base) + (0x740)));
            i++;
        } while (i < count);
    }
}
