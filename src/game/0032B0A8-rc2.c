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

extern void FastVecAdd(void *, void *, s32);
extern void gfx_draw_facing_sprite_copy(void *, s32, s32, s32, s32, f32, f32, f32);
extern s8 g_hero_state[];
extern s8 g_trail_nodes[];

/* Draws every trail node of an owner as two glowing sprites. */
void part_draw_trail_nodes(s32 owner) {
    f32 offset[4];
    s8 *hero = g_hero_state;
    s32 i;
    for (i = 0; i < 0x80; i++) {
        s32 node = (s32)g_trail_nodes + i * 0x50;
        if (*(s32 *)(node + 0x44) == owner) {
            f32 second_size;
            FastVecAdd(offset, (void *)node, *(s32 *)(hero + 0x2290) + 0x10);
            gfx_draw_facing_sprite_copy(offset, 0x7F7F7F, *(s32 *)(node + 0x34), 0x31, 2, *(f32 *)(node + 0x20), *(f32 *)(node + 0x2C), 0.001f);
            second_size = *(volatile f32 *)(node + 0x24);
            gfx_draw_facing_sprite_copy(offset, *(s32 *)(node + 0x38), *(s32 *)(node + 0x34) >> 1, 0x31, 2, second_size, *(f32 *)(node + 0x2C), 0.001f);
        }
    }
}
