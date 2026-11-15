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

extern s8 D_00232760[];
extern s8 D_00189E20[];
extern s32 func_00282948(s8 *);
extern void func_00282CC0(s8 *, s8 *, s8 *);
extern void func_00282F20(s8 *, s8 *, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern void func_002ACEC0(s8 *, s8 *, s8 *, f32);
extern void func_002FE8D8(s32, s8 *);
extern void func_0032AE30(s32, s8 *, s32);

/* Moves the flying debris pieces of an owner, leaves a glowing trail node behind each, and removes a piece when its life runs out. */
void func_0032ACF0(s32 owner) {
    s8 targetOffset[16];
    s8 trailPos[16];
    f32 lifeNow;
    f32 lifeRatio;
    s8 *lifePtr;
    s8 *piece;
    s8 *tableEnd;
    s8 *table;
    s8 *hero;

    table = gDebrisPieces;
    lifePtr = table + 0x18;
    piece = table;
    tableEnd = piece + 0x240;
    hero = gHeroState;
    do {
        if ((*(s32 *)((s8 *)(piece) + (0x1C))) == owner) {
            GetObjectFacingDirection((*(s32 *)((s8 *)(hero) + (0x2290))) + 0x10, targetOffset);
            lifeNow = IntToFloat((*(s32 *)((s8 *)(piece) + (0x18))));
            lifeRatio = lifeNow / IntToFloat(0x25);
            ApplyAxisRotationToQuaternion(trailPos, piece, targetOffset, (*(f32 *)((s8 *)(piece) + (0x10))));
            ClaimTrailNode(owner, trailPos, FloatToInt(lifeRatio * 128.0f));
            (*(f32 *)((s8 *)(piece) + (0x10))) = FastAddRotations((*(f32 *)((s8 *)(piece) + (0x10))), (*(f32 *)((s8 *)(piece) + (0x14))));
            vec_scale_to_length(targetOffset, targetOffset, 0.04f);
            FastVecAdd(piece, piece, targetOffset);
            if (FastFloatHelperD(lifePtr) != 0) {
                (*(s32 *)((s8 *)(piece) + (0x1C))) = 0;
            }
        }
        piece += 0x30;
        lifePtr += 0x30;
    } while ((s32)piece < (s32)tableEnd);
}
