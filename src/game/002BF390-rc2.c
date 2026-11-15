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

typedef int TI __attribute__((mode(TI)));
extern s32 func_00282978();
extern void func_00282CC0();
extern void func_00282CF0();
extern void func_00282D30(void *, void *, f32);
extern f32 func_00282E48();
extern void func_002B9180();
extern f32 D_001AA364 __attribute__((sda));
extern f32 D_001AA368 __attribute__((sda));

void func_002BF390(s32 arg0) {
    s32 sp[4];
    TI sp10;
    s32 temp_v0;
    u8 temp_v1;
    s32 temp_s1;
    s32 temp_s3;

    temp_v0 = (*(s32 *)((s8 *)(arg0) + (0x30)));
    if (temp_v0 == 0 || (temp_v1 = (*(u8 *)((s8 *)(temp_v0) + (0x20))), temp_v1 == 0xFE) || temp_v1 == 0xFD || FastDecTimer(arg0 + 0xA) != 0) {
        func_002B9180(arg0);
        return;
    }
    temp_s3 = arg0 + 0x10;
    FastVecSub(&sp10, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10, temp_s3);
    temp_s1 = arg0 + 0x20;
    *(TI *)sp = sp10;
    FastVecScale(sp, sp, (D_001AA364 - 1.0f) + 1.0f);
    FastVecAdd(&sp10, sp, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(arg0) + (0x10))) = sp10;
    FastVecSub(&sp10, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10, temp_s1);
    *(TI *)sp = sp10;
    FastVecScale(sp, sp, (D_001AA368 - 1.0f) + 1.0f);
    FastVecAdd(&sp10, sp, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(arg0) + (0x20))) = sp10;
    if (fast_vec_dist(temp_s3, temp_s1) < 0.1f || fast_vec_dist(temp_s3, (*(s32 *)((s8 *)(arg0) + (0x30))) + 0x10) < 1.0f) {
        func_002B9180(arg0);
    }
}
