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

extern volatile s32 D_001A7344[] __attribute__((sda));
extern void ref_L04_00422A00_00(void *dest, s32 *position, void *table);
extern f32 ref_L04_00422A00_01(void *work, void *table);
extern void ref_L04_00422A00_02(s32 *position, s32 *x, s32 *y);
extern s32 ref_L04_00422A00_03(s32 sentinel, u16 x, u16 y, s32 width, s32 rowBytes, s32 flags, f32 *out);
extern s32 D_001A7340;
extern f32 ref_L04_00422A00_04 __attribute__((sda));
extern s8 ref_L04_00422A00_05[];

typedef struct {
    s32 pad[4];
    s32 x;
    s32 y;
    s32 tail[2];
} QueryWork;

/* Projects the object's position onto the screen and, if it lands inside the view, looks up a value for that spot; returns -1 when it does not. */
f32 func_L04_00422A00(void *object) {
    QueryWork work;
    f32 queryResult;
    s32 positionPtr;

    positionPtr = *(s32 *)((s8 *)object + 0x68) + 0x30;
    ref_L04_00422A00_00(&work, (s32 *)positionPtr, ref_L04_00422A00_05);
    queryResult = ref_L04_00422A00_01(&work, ref_L04_00422A00_05 + 0x230);
    ref_L04_00422A00_02((s32 *)positionPtr, &work.x, &work.y);
    if (work.x < 0 ||
        work.x >= gScreenWidth - 0x10 ||
        work.y < 0 ||
        work.y >= gScreenHeight[0] - 8 ||
        !(queryResult > 0.0f) ||
        ref_L04_00422A00_03(-1, (u16)work.x, (u16)work.y, 0x10, 8, 0, &ref_L04_00422A00_04) == -1) {
        ref_L04_00422A00_04 = -1.0f;
    }
    return ref_L04_00422A00_04;
}
