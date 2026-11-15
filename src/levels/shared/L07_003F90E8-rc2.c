
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

extern s32 ref_L07_003F90E8_00 __attribute__((sda));
extern f32 ref_L07_003F90E8_01(s32);

/* Blends smoothly between two values depending on where a global value sits between two limits. */
f32 func_L07_003F90E8(s32 lowLimit, s32 highLimit, f32 lowValue, f32 highValue) {
    f32 highTerm;
    f32 currentTerm;
    f32 lowTerm;

    if (lowLimit >= ref_L07_003F90E8_00) {
        return lowValue;
    }
    if (ref_L07_003F90E8_00 >= highLimit) {
        return highValue;
    }
    currentTerm = ref_L07_003F90E8_01(ref_L07_003F90E8_00);
    lowTerm = ref_L07_003F90E8_01(lowLimit);
    highTerm = ref_L07_003F90E8_01(highLimit);
    {
        f32 den = highTerm - ref_L07_003F90E8_01(lowLimit);
        f32 num = currentTerm - lowTerm;
        f32 dif = highValue - lowValue;
        num = num / den;
        return lowValue + (dif * num);
    }
}
