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

extern f32 IntToFloat();
extern s32 FloatToInt(f32);

/* Fades a sound volume from loud to quiet as the distance grows from the near limit to the far limit. */
s32 snd_compute_falloff(s32 curve, f32 distance, f32 near_distance, f32 far_distance) {
    f32 remaining;
    f32 span;
    f32 volume_range;
    f32 remaining_linear;
    f32 var_f1;

    if ((*(u8 *)((s8 *)(curve) + (0x19))) & 1) {
        if (distance <= near_distance) {
            return (*(s32 *)((s8 *)(curve) + (0xC)));
        }
        if (far_distance <= distance) {
            return (*(s32 *)((s8 *)(curve) + (8)));
        }
        volume_range = IntToFloat((*(s32 *)((s8 *)(curve) + (0xC))) - (*(s32 *)((s8 *)(curve) + (8))));
        remaining = far_distance - distance;
        span = far_distance - near_distance;
        return (*(s32 *)((s8 *)(curve) + (8))) + FloatToInt(((remaining * remaining) * volume_range) / (span * span));
    }
    if (distance <= near_distance) {
        return (*(s32 *)((s8 *)(curve) + (0xC)));
    }
    if (!(far_distance <= distance)) {
        volume_range = IntToFloat((*(s32 *)((s8 *)(curve) + (0xC))) - (*(s32 *)((s8 *)(curve) + (8))));
        remaining_linear = far_distance - distance;
        return (*(s32 *)((s8 *)(curve) + (8))) + FloatToInt((remaining_linear * volume_range) / (far_distance - near_distance));
    }
    return (*(s32 *)((s8 *)(curve) + (8)));
}
