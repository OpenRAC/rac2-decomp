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

extern void func_0027C540(s32);
extern void func_0027C660(void);
extern void func_0027FAA8(s32, s32, u64, s32, s32);
extern s32 func_00288FB8(s32);
extern void func_002CE5D0(s32, s32);
extern void func_00300A00(s32, s32, f32, f32, f32, f32, f32);
extern s32 func_00336D50(s32, s32);
extern s32 D_001A8CFC;
extern s32 D_001A7340;
extern f32 D_001B23A8;
extern s32 g_001ABA5C __attribute__((sda));
extern s32 g_001ABA58 __attribute__((sda));

/* Draws the 18-page viewer with its title and left and right page arrows. */
s32 func_002D1E70(void) {
    f32 z;
    s32 sprite;

    SetupGifPaging(0);
    z = 0.0f;
    sprite = FindTableEntryById(D_001A8CFC + 0x8710, 0xDE);
    DrawScaledObjectTwoAxes(sprite, 0x60442D00, (f32)(gScreenWidth / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    sprite = FindTableEntryById(D_001A8CFC + 0x8710, 0xDF);
    DrawScaledObjectTwoAxes(sprite, 0x60241700, (f32)(gScreenWidth / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    sprite = FindTableEntryById(D_001A8CFC + 0x8710, 0xE0);
    DrawScaledObjectTwoAxes(sprite, 0x55F0C070, (f32)(gScreenWidth / 2), (f32)g_001ABA5C, 1.0f, D_001B23A8, z);
    DrawMenuNavigationFramesAndLabels(g_001ABA58 != 0, g_001ABA58 != 0x11);
    DrawTextCenteredSmallFont(0x1B0, 0x177, (u64)0x80F0F0F0, GetLocalizedString(0x2D4F), -1);
    DoGifPaging();
    return 0;
}
