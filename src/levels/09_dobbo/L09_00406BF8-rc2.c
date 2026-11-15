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

extern s8 D_00189EA0[];
extern s32 ref_L09_00406BF8_00(s8 *, s32);
extern void ref_L09_00406BF8_01(s32, s32);

/* Checks whether the hero has hit the given trigger, records the result for a slot, and returns 1 if it was hit. */
s32 func_L09_00406BF8(s32 triggerId, s32 slot) {
    s32 resultCode;
    s32 triggered;

    resultCode = 0;
    triggered = 0;
    if (triggerId != -1) {
        if (ref_L09_00406BF8_00(gHeroPosition, triggerId) != 0) {
            resultCode = triggered;
            triggered = 1;
        } else {
            resultCode = 2;
        }
    }
    ref_L09_00406BF8_01(slot, resultCode);
    return triggered;
}
