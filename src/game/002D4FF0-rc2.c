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

extern s32 D_001ABAA0 __attribute__((sda));
extern s32 D_001AAA38 __attribute__((sda));
extern s8 D_0025B9C0[];
extern s8 D_0025BA80[];

/* Sets the given menu item to show the current choice and starts it sliding in from the side when the choice changed, then moves on to the next choice. */
s32 menu_choice_slide_init(s32 display) {
    s32 choiceNumber;
    s32 byteOffset;

    choiceNumber = *(s32 *)D_0025B9C0;
    if (D_001ABAA0 != choiceNumber) {
        (*(s32 *)((s8 *)(display) + (0x3C))) = -0x2BC;
        D_001ABAA0 = choiceNumber;
    }
    byteOffset = choiceNumber * 4;
    (*(s32 *)((s8 *)(display) + (0x34))) = *(s32 *)((s8 *)&D_001AAA38 + byteOffset);
    *(s32 *)D_0025BA80 = choiceNumber + 1;
    return 0;
}
