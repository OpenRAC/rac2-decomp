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

extern s32 ref_L00_0037E5F0_literal_0;
extern s32 ref_L00_0037E5F0_00;
extern s32 g_001B26B4 __attribute__((sda));
extern f32 g_001B26B0 __attribute__((sda));

/* Lowers the fade value by the given amount and returns how far it dropped below zero. */
f32 fade_reduce_value(f32 amount) {
    f32 remaining;
    f32 overshoot = 0.0f;

    if (ref_L00_0037E5F0_00 != 0) {
        return 0.0f;
    }
    remaining = g_001B26B0 - amount;
    g_001B26B0 = remaining;
    if (remaining < 0.0f) {
        overshoot = -remaining;
        *(s32*)(&ref_L00_0037E5F0_literal_0) = 0;
    }
    g_001B26B4 = 0xF;
    return overshoot;
}
