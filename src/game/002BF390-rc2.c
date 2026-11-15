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

/* Pulls two points of an effect towards the object it is tied to. It disappears when that object is gone or the points get too close. */
void func_002BF390(s32 effect) {
    s32 scaled[4];
    TI result;
    s32 target;
    u8 targetState;
    s32 pointB;
    s32 pointA;

    target = (*(s32 *)((s8 *)(effect) + (0x30)));
    if (target == 0 || (targetState = (*(u8 *)((s8 *)(target) + (0x20))), targetState == 0xFE) || targetState == 0xFD || FastDecTimer(effect + 0xA) != 0) {
        KillParticle(effect);
        return;
    }
    pointA = effect + 0x10;
    FastVecSub(&result, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10, pointA);
    pointB = effect + 0x20;
    *(TI *)scaled = result;
    FastVecScale(scaled, scaled, (D_001AA364 - 1.0f) + 1.0f);
    FastVecAdd(&result, scaled, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(effect) + (0x10))) = result;
    FastVecSub(&result, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10, pointB);
    *(TI *)scaled = result;
    FastVecScale(scaled, scaled, (D_001AA368 - 1.0f) + 1.0f);
    FastVecAdd(&result, scaled, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(effect) + (0x20))) = result;
    if (fast_vec_dist(pointA, pointB) < 0.1f || fast_vec_dist(pointA, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10) < 1.0f) {
        KillParticle(effect);
    }
}
