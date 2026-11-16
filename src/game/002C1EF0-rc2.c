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

struct V4 { f32 x; f32 y; f32 z; s32 w; };
typedef int TI __attribute__((mode(TI)));
extern TI g_coll_hit_position;
extern s32 CollLine(s8 *a0, s8 *a1, s32 a2, s32 a3, s32 a4);
extern s32 FastDecTimer(s8 *p);
extern void FastVecAdd(s8 *a0, s8 *a1, struct V4 *saved);
extern void part_kill(s8 *p);

/* Updates a particle that moves along a line. It is removed when its timer ends,
   and it is reset if it hits something. */
void part_update_streak_collision(s8 *particle) {
    struct V4 step;
    s8 *trail;
    s8 *motion;
    s8 *position;

    position = particle + 0x10;
    motion = particle + 0x30;
    trail = particle + 0x20;
    step.x = *(f32 *)(particle + 0x30);
    step.y = *(f32 *)(motion + 4);
    step.z = *(f32 *)(motion + 8);
    step.w = 0;
    FastVecAdd(position, position, &step);
    FastVecAdd(trail, trail, &step);
    if (FastDecTimer(particle + 0xA) != 0) {
        part_kill(particle);
        return;
    }
    if (CollLine(trail, position, 0x10, *(s32 *)(motion + 0xC), 0) != 0) {
        TI saved = g_coll_hit_position;
        *(s16 *)(particle + 0xA) = 0;
        *(volatile TI *)(particle + 0x10) = saved;
    }
}
