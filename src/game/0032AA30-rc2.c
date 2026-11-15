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
#ifndef NULL
#define NULL 0
#endif

extern s8 D_002359E0[];
extern s8 D_00189E20[];
extern f32 D_001B0594 __attribute__((sda));
extern f32 D_001B0598 __attribute__((sda));
extern void func_00282C88(void *);
extern s32 func_002A7820(s32, s32);
extern void *func_002C2210(void *, s32, s32, s32, s32, void *, s32, f32, f32, f32);
extern s32 func_00283CF0(f32);
extern void func_002FE8D8(s32, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);

/* Sets up 50 pairs of glowing sprites (one reddish, one red) along a trail that drifts toward the player's aim point. */
void func_0032AA30(void) {
    s8 zeroVec[16];
    s8 drift[16];
    s32 index;
    s32 alpha;
    s8 *point;
    s8 *sprite;
    s8 *hero;
    f32 redSize;

    index = 0;
    ClearVector128(zeroVec);
    do {
        alpha = RandomIntRange(0, 0x6F) << 24;
        point = D_002359E0 + index * 16;
        sprite = SpawnGroundEffectParticle(point, 0xC, alpha | 0x7F2020, 0, 1, zeroVec, 0, D_001B0594 * 0.5f, D_001B0594, 0.0f);
        if (sprite != NULL) {
            *(s8 *)(sprite + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        redSize = D_001B0598;
        sprite = SpawnGroundEffectParticle(point, 0xC, alpha | 0xFF4040, 1, 1, zeroVec, 0, redSize * 0.5f, redSize, 0.0f);
        if (sprite != NULL) {
            *(s8 *)(sprite + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        index += 1;
        hero = gHeroState;
        GetObjectFacingDirection(*(s32 *)(hero + 0x2290) + 0x10, drift);
        vec_scale_to_length(drift, drift, -0.00277777785f);
        FastVecAdd(point, point, drift);
    } while (index < 0x32);
}
