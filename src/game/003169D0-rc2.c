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

extern s8 D_0022AA10[];
extern void gfx_draw_lightning_bolt(s32 a, s32 b);
extern void gfx_draw_billboard_quad(void *o, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13, f32 f14);
extern f32 math_random_float_range(f32 a, f32 b);

/* Draws the lightning curve for each effect slot owned by this object, plus three glowing sprites while the slot is still running. */
void gfx_draw_owner_effect_slots(s32 owner) {
    s32 i;
    s32 state;
    s8 *slot;
    s8 *pool;

    pool = D_0022AA10;
    slot = pool + 0x30;
    state = (s32) pool;
    for (i = 0; i < 3; i++) {
        if ((*(s32 *)((s8 *)(slot) + (0x5C))) == owner) {
            gfx_draw_lightning_bolt(owner, state);
            if ((*(s32 *)((s8 *)(slot) + (0x64))) == 0) {
                gfx_draw_billboard_quad(slot, 0x31, 0x3F007F00, 1, math_random_float_range(0.125f, 0.25f) * 5.0f, 1.25f, 0.0f);
                gfx_draw_billboard_quad(slot, 0x31, 0x5F7F7F7F, 1, math_random_float_range(0.0625f, 0.125f) * 5.0f, 1.24f, 0.0f);
                gfx_draw_billboard_quad(slot, 0xB, 0x10003F00, 1, math_random_float_range(0.15f, 0.35f) * 5.0f, 1.23f, 0.0f);
            }
        }
        slot += 0xA0;
        state += 0xA0;
    }
}
