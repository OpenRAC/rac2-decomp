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

extern f32 func_00283CE0();
extern s32 func_00283CF0(f32);

/* Fades a sound volume from loud to quiet as the distance grows from the near limit to the far limit. */
s32 func_002E45C8(s32 curve, f32 distance, f32 nearDistance, f32 farDistance) {
    f32 remaining;
    f32 span;
    f32 volumeRange;
    f32 remainingLinear;
    f32 var_f1;

    if ((*(u8 *)((s8 *)(curve) + (0x19))) & 1) {
        if (distance <= nearDistance) {
            return (*(s32 *)((s8 *)(curve) + (0xC)));
        }
        if (farDistance <= distance) {
            return (*(s32 *)((s8 *)(curve) + (8)));
        }
        volumeRange = IntToFloat((*(s32 *)((s8 *)(curve) + (0xC))) - (*(s32 *)((s8 *)(curve) + (8))));
        remaining = farDistance - distance;
        span = farDistance - nearDistance;
        return (*(s32 *)((s8 *)(curve) + (8))) + FloatToInt(((remaining * remaining) * volumeRange) / (span * span));
    }
    if (distance <= nearDistance) {
        return (*(s32 *)((s8 *)(curve) + (0xC)));
    }
    if (!(farDistance <= distance)) {
        volumeRange = IntToFloat((*(s32 *)((s8 *)(curve) + (0xC))) - (*(s32 *)((s8 *)(curve) + (8))));
        remainingLinear = farDistance - distance;
        return (*(s32 *)((s8 *)(curve) + (8))) + FloatToInt((remainingLinear * volumeRange) / (farDistance - nearDistance));
    }
    return (*(s32 *)((s8 *)(curve) + (8)));
}
