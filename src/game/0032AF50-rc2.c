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

extern s32 math_fast_float_d(s8 *);
extern void FastVecAdd(s8 *, s8 *, s8 *);
extern void FastVecScale(s8 *, s8 *, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern void moby_get_facing_direction(s32, s8 *);
extern s8 g_trail_nodes[];
extern s8 g_hero_state[];

/* Updates the trail nodes of an owner: they fade, spin and drift, and each one is removed when its time is over. */
void part_update_trail_nodes(s8 *owner) {
    s8 *table ;
    s8 *node;
    s8 *velocity;
    s8 *timerPtr;
    s8 *hero;
    s32 ownerCount;
    s32 count;
    s32 fadeLeft;
    f32 drift[3];
    f32 lifeNow;
    f32 lifeRatio;

    count = 0;
    table = g_trail_nodes;
    timerPtr = table + 0x3C;
    velocity = table + 0x10;
    node = table;
    hero = g_hero_state;
    ownerCount = *(s32 *)(owner + 0x68);
    do {
        count++;
        if ((s8 *)(s64)*(s32 *)(node + 0x44) == owner) {
            lifeNow = IntToFloat(*(s32 *)(node + 0x3C));
            lifeRatio = lifeNow / IntToFloat(*(s32 *)(node + 0x40));
            *(s32 *)(node + 0x34) = FloatToInt(IntToFloat(*(s32 *)(node + 0x30)) * lifeRatio);
            *(f32 *)(node + 0x2C) = FastAddRotations(*(f32 *)(node + 0x2C), *(f32 *)(node + 0x28));
            FastVecAdd(node, node, velocity);
            moby_get_facing_direction(*(s32 *)(hero + 0x2290) + 0x10, drift);
            FastVecScale(drift, drift, -0.00089999998454f);
            FastVecAdd(velocity, velocity, drift);
            if (math_fast_float_d(timerPtr) != 0) {
                fadeLeft = *(s32 *)(node + 0x34);
                if (fadeLeft > 0) {
                    *(s32 *)(node + 0x34) = fadeLeft - 1;
                } else {
                    *(s32 *)(node + 0x44) = 0;
                    *(s32 *)ownerCount -= 1;
                }
            }
        }
        timerPtr += 0x50;
        velocity += 0x50;
        node += 0x50;
    } while (count < 0x80);
}
