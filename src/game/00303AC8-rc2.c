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

extern s8 D_00222AE0[];
extern s8 D_002222E0[];
extern s8 D_00189EA0[];
extern s32 func_002ACBC8(s32 noisePtr, s32 index);

/* Sets the height of each surface grid point from its base height plus the wave noise. */
void func_00303AC8(void *object) {
    void *state;
    s32 index;
    s32 flags;
    s32 row;
    s32 tableOffset;
    s8 *noisePtr;
    s8 *heightPtr;
    s8 *tablePtr;

    state = (*(void **)((s8 *)(object) + (0x68)));
    index = (*(s32 *)((s8 *)(state) + (0x44)));
    if (index != -1 && IsPointInCuboid((s32)gHeroPosition, index) != 0 && !((*(u32 *)((s8 *)(state) + (0x4C))) & 4)) {
        tableOffset = (*(s32 *)((s8 *)(state) + (0x40))) << 10;
        tablePtr = (s8 *)D_00222AE0;
        tablePtr += 8;
        heightPtr = tablePtr + tableOffset;
        noisePtr = D_002222E0;
        for (index = 0; index < 0x40; index++) {
            *(f32 *)heightPtr = (*(f32 *)((s8 *)(state) + (0x70))) + (*(f32 *)((s8 *)(state) + (4)));
            flags = (*(s32 *)((s8 *)(state) + (0x4C)));
            if (~flags & 0x10) {
                if ((index % 8 != 0 && index % 8 != 7) || ((flags ^ 1) & 1)) {
                    row = index / 8;
                    if ((row != 0 && row != 7) || !((*(s32 *)((s8 *)(state) + (0x4C))) & 2)) {
                        *(f32 *)heightPtr += *(f32 *)noisePtr * (*(f32 *)((s8 *)(state) + (0x34)));
                    }
                }
            }
            noisePtr += 0x20;
            heightPtr += 0x10;
        }
    }
}
