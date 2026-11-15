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

extern s32 ref_L04_003A0008_literal_0;
extern void ref_L04_003A0008_00(void *patches, void *count, void *arg2, f32 arg3);
extern void ref_L04_003A0008_01(void);
extern s32 ref_L04_003A0008_02;
extern s32 ref_L04_003A0008_03;
extern s32 ref_L04_003A0008_04;
extern f32 ref_L04_003A0008_05 __attribute__((sda));

/* Advances the water ripple animation by one step and blends the patches. */
void func_L04_003A0008(void *patches, s32 count) {
    f32 step = *(f32*)(&ref_L04_003A0008_literal_0);

    if ((1.0f - step) <= ref_L04_003A0008_05) {
        ref_L04_003A0008_05 = step;
        ref_L04_003A0008_01();
        ref_L04_003A0008_04 = ref_L04_003A0008_03;
    } else {
        ref_L04_003A0008_04 = 2;
        if (count > 0) {
            u8 *patch = (u8 *)patches;
            s32 remaining = count;
            do {
                if (*(u16 *)(patch + 0x1E) != 0) {
                    ref_L04_003A0008_00(
                        patch + (ref_L04_003A0008_04 * 0x5C0 + 0x50),
                        patch + (ref_L04_003A0008_03 * 0x5C0 + 0x50),
                        patch + (ref_L04_003A0008_02 * 0x5C0 + 0x50),
                        ref_L04_003A0008_05);
                }
                remaining -= 1;
                patch += 0x1190;
            } while (remaining != 0);
        }
    }
    ref_L04_003A0008_05 += *(f32*)(&ref_L04_003A0008_literal_0);
}
