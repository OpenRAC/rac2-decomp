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
#ifndef NULL
#define NULL 0
#endif

extern void *func_002A9640(void *, s32, s32);
extern void func_002A7750(void *, s32, s32);
extern s32 ref_L01_003D9830_02 __attribute__((sda));

void func_PAL_L01_003DDD18(void *arg0) {
    s16 temp_v1;
    u8 temp_v1_2;
    void *temp_s1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = (*(void **)((s8 *)(arg0) + (0x68)));
    temp_v0 = func_002A9640(arg0, 1, 0);
    if ((temp_v0 != NULL) && (temp_v0_2 = (*(void **)((s8 *)(temp_v0) + (0x20))), (temp_v0_2 != NULL))) {
        temp_v1 = (*(s16 *)((s8 *)(temp_v0_2) + (0xAA)));
        if ((temp_v1 == 0xB24) || (temp_v1 == 0xA54)) {
            temp_v0_3 = (*(void **)((s8 *)(temp_s1) + (0xC8)));
            if (temp_v0_3 != NULL) {
                temp_v1_2 = (*(u8 *)((s8 *)(temp_v0_3) + (0x20)));
                if ((temp_v1_2 != 1) && (temp_v1_2 != 4) && (temp_v1_2 != 5)) {
                    (*(s32 *)((s8 *)(temp_s1) + (0xC4))) = (((s32)(ref_L01_003D9830_02) * 5 + 2) / 6);
                    func_002A7750(arg0, 2, -1);
                }
            }
        }
    }
    (*(u8 *)((s8 *)(arg0) + (0xA8))) = 0xFF;
}