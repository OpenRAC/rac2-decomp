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

extern void vec_clear_128(f32 *v);
extern f32 FastVecLength(f32 *v);
extern s8 g_hero_state[];
extern f32 g_stick_length;

/* Reads the stick input stored in the hero data, limits each axis to the range -1 to 1, saves it in the object and stores the stick length. */
void pad_read_clamped_stick(s8 *moby) {
    s8 *heroData;
    s8 *vars;
    f32 stickVec[2];

    vars = *(s8 **)(moby + 0x68);
    heroData = g_hero_state;
    (*(f32 *)((s8 *)(vars) + (0x54))) = -(*(f32 *)((s8 *)(heroData) + (0x1FB0)));
    (*(f32 *)((s8 *)(vars) + (0x50))) = -(*(f32 *)((s8 *)(heroData) + (0x1FB4)));
    if ((*(f32 *)((s8 *)(vars) + (0x54))) > 1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x54))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(vars) + (0x54))) < -1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x54))) = -1.0f;
    }
    if ((*(f32 *)((s8 *)(vars) + (0x50))) > 1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x50))) = 1.0f;
    } else if ((*(f32 *)((s8 *)(vars) + (0x50))) < -1.0f) {
        (*(f32 *)((s8 *)(vars) + (0x50))) = -1.0f;
    }
    vec_clear_128(stickVec);
    stickVec[0] = (*(f32 *)((s8 *)(vars) + (0x50)));
    stickVec[1] = (*(f32 *)((s8 *)(vars) + (0x54)));
    g_stick_length = FastVecLength(stickVec);
}
