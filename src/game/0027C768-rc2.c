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

extern void func_00282CF0(f32 *a, s32 b, s8 *c);
extern void func_00282D30(f32 *a, f32 *b, f32 c);
extern void func_002830C0(f32 *a, f32 *b, s8 *c);
extern s8 D_001B5340[];
extern s8 D_001B9250[];
extern s32 D_001A7340;
extern s32 D_001A7344;

/* Turns a point in the world into a screen position between 0 and 1. */
void func_0027C768(s32 worldPos, f32 *screenX, f32 *screenY) {
    f32 point[4];
    s8 *matrices;
    f32 w;
    f32 pixelX;
    f32 pixelY;

    matrices = gCameraState_001B5340;
    FastVecSub(point, worldPos, matrices);
    FastVecScale(point, point, 1024.0f);
    point[3] = 1.0f;
    transform_vector(point, point, matrices - 0x100);
    w = point[3];
    FastVecScale(point, point, *(f32 *)D_001B9250 / w);
    pixelX = point[0] + (f32)(gScreenWidth >> 1);
    *screenX = pixelX;
    *screenX = pixelX / (f32)gScreenWidth;
    pixelY = point[1] + (f32)(gScreenHeight >> 1);
    *screenY = pixelY;
    *screenY = pixelY / (f32)gScreenHeight;
}
