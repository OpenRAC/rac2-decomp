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

extern s32 ref_L12_003A6EF8_00;
extern s8 ref_L12_003A6EF8_01[];
extern void ref_L12_003A6EF8_02(void *, void *, s32 *);

/* Checks a level-wide setting and, when it differs from the one this object remembers, saves
   the new one and calls a callback for the object. */
void moby_sync_level_setting(void *moby) {
    s32 *current;
    s8 *vars;

    if (*(u8 *)((s8 *)moby + 0x21) != 0xFF) {
        s32 wanted  = ref_L12_003A6EF8_00;
        vars = *(s8 **)((s8 *)moby + 0x68);
        if (wanted != 0) {
            current = *(s32 **)(vars + 8);
            if (wanted != *current) {
                *current = wanted;
                ref_L12_003A6EF8_02(ref_L12_003A6EF8_01, moby, current);
            }
        }
    }
}
