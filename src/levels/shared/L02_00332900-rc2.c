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

extern f32 ref_L02_00332900_00(s32);
extern s32 ref_L02_00332900_01 __attribute__((sda));
extern s32 ref_L02_00332900_02 __attribute__((sda));
extern f32 ref_L02_00332900_03 __attribute__((sda));
extern f32 ref_L02_00332900_04 __attribute__((sda));
extern volatile s32 ref_L02_00332900_05;

void func_L02_00332900(void) {
    if (ref_L02_00332900_01 != ref_L02_00332900_05) {
        if (ref_L02_00332900_02 != 0) {
            ref_L02_00332900_04 = ref_L02_00332900_03 / ref_L02_00332900_00(ref_L02_00332900_02);
        } else {
            ref_L02_00332900_04 = 0.0f;
        }
        ref_L02_00332900_02 = 0;
        ref_L02_00332900_01 = ref_L02_00332900_05;
        ref_L02_00332900_03 = 0.0f;
    }
    T0_MODE = 0x81;
    T0_COUNT = 0;
}
