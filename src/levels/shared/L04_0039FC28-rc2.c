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

extern s32 ref_L04_0039FC28_literal_0;
extern s32 ref_L04_0039FC28_literal_1;
extern s32 ref_L04_0039FC28_00(f32);
extern f32 ref_L04_0039FC28_01 __attribute__((sda));

/* Converts a position and a size into fixed-point numbers for the renderer. */
void func_L04_0039FC28(void *pos, void *out) {
    (*(s32 *)((s8 *)(out) + (0))) = ref_L04_0039FC28_00(((*(f32 *)((s8 *)(pos) + (0))) + *(f32*)(&ref_L04_0039FC28_literal_0)) * 1024.0f);
    (*(s32 *)((s8 *)(out) + (4))) = ref_L04_0039FC28_00(((*(f32 *)((s8 *)(pos) + (4))) + *(f32*)(&ref_L04_0039FC28_literal_1)) * 1024.0f);
    (*(s32 *)((s8 *)(out) + (8))) = ref_L04_0039FC28_00(((*(f32 *)((s8 *)(pos) + (8))) - 1.0f) * 1024.0f);
    (*(s16 *)((s8 *)(out) + (0xC))) = ref_L04_0039FC28_00(ref_L04_0039FC28_01 * 1024.0f);
    (*(s16 *)((s8 *)(out) + (0xE))) = ref_L04_0039FC28_00(ref_L04_0039FC28_01 * 1024.0f);
}
