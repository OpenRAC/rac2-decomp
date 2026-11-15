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

/* Returns the address of the selected entry in the table of the current tab. */
s32 func_003415B8(s32 self) {
    s32 tab;
    s32 table;
    s32 index;
    s32 base;

    tab = (*(s32 *)((s8 *)(self) + (0x2FC)));
    if (tab == 0) {
        goto block_2;
    }
    goto block_5;
block_2:
    index = (*(s32 *)((s8 *)(self) + (0x1B8)));
    table = (*(s32 *)((s8 *)(self) + (0x2F0)));
block_4:
    return table + (index * 0x14);
block_5:
    if (tab != 1) {
        base = self + (tab * 4);
        return (*(s32 *)((s8 *)(self) + (0x2F8))) + ((*(s32 *)((s8 *)(base) + (0x1B8))) * 0x14);
    }
    table = (*(s32 *)((s8 *)(self) + (0x2F4)));
    return table + (((*(s32 *)((s8 *)(self) + (0x1BC)))) * 0x14);
block_7:
    return (*(s32 *)((s8 *)(self) + (0x2F8))) + ((*(s32 *)((s8 *)((self + (tab * 4))) + (0x1B8))) * 0x14);
}
