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

extern s32 ref_L09_003F7C50_00(s8 *, s32, s32, s32);
extern s32 ref_L09_003F7C50_01(s8 *, s32, f32);

/* Chooses a path for the enemy to follow and returns its current point, or -1 if there is no path. */
s32 func_L09_003F7C50(s8 *moby, s32 pathIndex, s32 mode) {
    s8 *vars;
    s32 pathParam;

    vars = (*(s8 **)((s8 *)(moby) + (0x68)));
    (*(s32 *)((s8 *)(vars) + (0x2DC))) = pathIndex;
    if (pathIndex == -1) {
        (*(s16 *)((s8 *)(vars) + (0x1C8))) = (s16) pathIndex;
        return -1;
    }
    pathParam = ref_L09_003F7C50_01(moby + 0x10, pathIndex, 0.0f);
    if (ref_L09_003F7C50_00(moby, pathIndex, mode, pathParam) != 0) {
        return (*(s16 *)((s8 *)(vars) + (0x1C8)));
    }
    (*(s16 *)((s8 *)(vars) + (0x1C8))) = 0;
    return -1;
}
