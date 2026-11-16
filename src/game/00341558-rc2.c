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

extern s8 g_tab_menu_values[];
/* Returns the value of the selected entry of the current tab, or 0 when it is locked. */
void *tab_menu_get_selected_value(s32 self) {
    s32 tab;
    s32 result;
    s32 base;

    tab = (*(s32 *)((s8 *)(self) + (0x2FC)));
    base = self + (tab * 4);
    result = *(s32 *)(((s32)g_tab_menu_values) + (s32) (((*(s32 *)((s8 *)(base) + (0x1B8))) * 4) + (tab << 5)));
    if ((tab == 2) && (*(u8 *)0x1A7A0A == 0)) {
        result = ((*(s32 *)((s8 *)(self) + (0x1C0))) >= 3) ? 0 : result;
    }
    return result;
}
