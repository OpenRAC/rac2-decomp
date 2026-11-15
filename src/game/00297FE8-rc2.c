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

extern f32 *func_00297F98(s32);
extern s32 D_001A79F0;

/* Turns a world position into a 0-1 position on the map screen for the given map (or the current map when -1 is passed). */
void func_00297FE8(f32 worldX, f32 worldY, f32 *outMapX, f32 *outMapY, s32 requestedMap) {
    f32 *xTransform;
    f32 *yTransform;
    s32 mapIndex;

    mapIndex = (~requestedMap != 0) ? requestedMap : gCurrentMapIndex;
    if (mapIndex <= -1) {
        mapIndex = 0;
    }
    if (mapIndex >= 0x15) {
        mapIndex = 0;
    }
    xTransform = GetMapCoefficients(mapIndex);
    *outMapX = (xTransform[0] + (GetMapCoefficients(mapIndex)[1] * worldX)) * 0.001953125f;
    yTransform = GetMapCoefficients(mapIndex);
    *outMapY = (yTransform[2] + (GetMapCoefficients(mapIndex)[3] * worldY)) * 0.001953125f;
}
