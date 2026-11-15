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

typedef int rc2_qword __attribute__((mode(TI)));
typedef int TI __attribute__((mode(TI)));
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    s32 padC;
    TI v10;
} Stack_0040BED0;
extern void ref_L04_0040BED0_00(void *, void *, TI *);
extern void ref_L04_0040BED0_01(void *, s32, s32);
extern void ref_L04_0040BED0_02(TI *, TI *, f32);
extern void ref_L04_0040BED0_03(void *, void *, f32);
extern s32 ref_L04_0040BED0_04(f32);
extern s32 ref_L04_0040BED0_05(s32, s32);
extern f32 ref_L04_0040BED0_06(f32, f32);
extern f32 ref_L04_0040BED0_07(f32, f32);
extern void ref_L04_0040BED0_08(s32, void *, s32, f32, f32, s32);
extern void *ref_L04_0040BED0_09(s32, void *, s32, s32, s32);

/* Throws a burst of sparks and puffs of smoke from a point. A higher intensity makes more of them. */
void part_spawn_spark_and_smoke_burst(s32 owner, rc2_qword *position, s32 quiet, s32 offset, f32 intensity) {
    Stack_0040BED0 sp;
    TI copyValue  = *(TI *)position;
    s32 sparkIndex = 0;
    s32 puffIndex;
    void *puff;

    sp.v10 = copyValue;
    ref_L04_0040BED0_01(&sp, owner, offset + 0x10);
    ref_L04_0040BED0_03(&sp, &sp, 0.01f);
    while (sparkIndex < ref_L04_0040BED0_04(intensity * 30.0f)) {
        sparkIndex += 1;
        sp.f0 += ref_L04_0040BED0_07(0.01f, 0.03f);
        sp.f4 += ref_L04_0040BED0_07(0.01f, 0.015f);
        sp.f8 += ref_L04_0040BED0_07(0.01f, 0.02f);
        ref_L04_0040BED0_02(&sp.v10, &sp.v10, 0.6f);
        ref_L04_0040BED0_00(&sp, &sp, &sp.v10);
        ref_L04_0040BED0_08(owner, &sp, 0xF, 0.0027777778f, intensity, 0x7FFFFFFF);
    }
    if (quiet == 0) {
        puffIndex = 0;
        while (puffIndex < ref_L04_0040BED0_04(intensity * 5.0f)) {
            puffIndex += 1;
            puff = ref_L04_0040BED0_09(owner, &sp, ref_L04_0040BED0_05(30, 60), 0, 0);
            *(f32 *)((u8 *)puff + 0x2C) *= ref_L04_0040BED0_06(0.2f, 0.4f);
        }
    }
}
