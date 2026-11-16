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

typedef int TI __attribute__((mode(TI)));
extern s32 FastDecTimer();
extern void FastVecAdd();
extern void FastVecSub();
extern void FastVecScale(void *, void *, f32);
extern f32 fast_vec_dist();
extern void part_kill();
extern f32 g_tether_scale_a __attribute__((sda));
extern f32 g_tether_scale_b __attribute__((sda));

/* Pulls two points of an effect towards the object it is tied to. It disappears when that object is gone or the points get too close. */
void part_update_tethered(s32 effect) {
    s32 scaled[4];
    TI result;
    s32 target;
    u8 target_state;
    s32 point_b;
    s32 point_a;

    target = (*(s32 *)((s8 *)(effect) + (0x30)));
    if (target == 0 || (target_state = (*(u8 *)((s8 *)(target) + (0x20))), target_state == 0xFE) || target_state == 0xFD || FastDecTimer(effect + 0xA) != 0) {
        part_kill(effect);
        return;
    }
    point_a = effect + 0x10;
    FastVecSub(&result, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10, point_a);
    point_b = effect + 0x20;
    *(TI *)scaled = result;
    FastVecScale(scaled, scaled, (g_tether_scale_a - 1.0f) + 1.0f);
    FastVecAdd(&result, scaled, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(effect) + (0x10))) = result;
    FastVecSub(&result, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10, point_b);
    *(TI *)scaled = result;
    FastVecScale(scaled, scaled, (g_tether_scale_b - 1.0f) + 1.0f);
    FastVecAdd(&result, scaled, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10);
    (*(TI *)((s8 *)(effect) + (0x20))) = result;
    if (fast_vec_dist(point_a, point_b) < 0.1f || fast_vec_dist(point_a, (*(s32 *)((s8 *)(effect) + (0x30))) + 0x10) < 1.0f) {
        part_kill(effect);
    }
}
