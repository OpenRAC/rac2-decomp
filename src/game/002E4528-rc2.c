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

extern s32 func_002761F8();
extern s32 func_00282CC0();
extern s32 func_00282CF0();
extern s32 func_00282D30(s32, s32, f32);
extern s32 func_00282FB8(s32, s32, f32);

extern s8 D_001B5340[];
/* Tests whether something blocks the line between a sound and a listener point. */
s32 func_002E4528(s32 voice, s32 samplePoint) {
    s32 hitResult;
    s32 probe[1];
    FastVecSub(probe, voice + 0x20, ((s32)gCameraState_001B5340));
    FastVecScale(probe, probe, 0.75f);
    FastVectorDivideHelper(probe, probe, 64.0f);
    FastVecAdd(probe, probe, ((s32)gCameraState_001B5340));
    hitResult = CollLine(samplePoint, probe, 0x82, (*(s32 *)((s8 *)(voice) + (0x18))), 0);
    return hitResult;
}
