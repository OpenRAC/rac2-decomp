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

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} vec4_local;

extern s8 g_data_block_base[];
f32 ref_L01_0042E0A8_00(f32);
void ref_L01_0042E0A8_01(void *, void *, void *);
void ref_L01_0042E0A8_02(void *, void *, void *);
void ref_L01_0042E0A8_03(s32, s32);

/* Checks if the player is inside a box around the moby and calls one of two actions when the player leaves on a side. */
void box_exit_trigger_update(void *moby) {
    u8 *self  = (u8 *)moby;
    s32 *state  = (*(s32 *)((s8 *)(moby) + (8)));
    f32 limit  = 1.0f;
    vec4_local input;
    vec4_local transformed;

    ref_L01_0042E0A8_01(&input, g_data_block_base - 0x6160, self + 0x40);
    input.w = 0.0f;
    ref_L01_0042E0A8_02(&transformed, &input, self + 0x50);
    if ((ref_L01_0042E0A8_00(transformed.x) <= limit) &&
        (ref_L01_0042E0A8_00(transformed.y) <= limit) &&
        (ref_L01_0042E0A8_00(transformed.z) <= limit)) {
        state[2] = 1;
        return;
    }
    if (state[2] != 0) {
        if (transformed.x < 0.0f) {
            ref_L01_0042E0A8_03(state[1], state[4]);
        } else {
            ref_L01_0042E0A8_03(state[0], state[3]);
        }
        state[2] = 0;
    }
}
