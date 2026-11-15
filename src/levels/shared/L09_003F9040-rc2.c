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

extern void ref_L09_003F9040_00(s8 *, s32, s32, s32);
extern s32 g_current_map_index;
extern s32 ref_L09_003F9040_01 __attribute__((sda));
extern s32 ref_L09_003F9040_02 __attribute__((sda));
extern s32 ref_L09_003F9040_03 __attribute__((sda));
extern s32 ref_L09_003F9040_04 __attribute__((sda));

/* On two levels, applies that level's colour tint to the object. */
void level_apply_colour_tint(s8 *moby) {
    s32 colorWord;
    s32 alphaMask;
    s32 packedValue;

    switch (g_current_map_index) {
    case 8:
        packedValue = ref_L09_003F9040_01;
        alphaMask = 0xFF000000;
        if ((packedValue & alphaMask) != 0) {
            ref_L09_003F9040_00(moby, packedValue & 0xFF, (packedValue >> 8) & 0xFF, (packedValue >> 16) & 0xFF);
        }
        colorWord = ref_L09_003F9040_02;
        goto block_9;
    case 20:
        packedValue = ref_L09_003F9040_03;
        alphaMask = 0xFF000000;
        if ((packedValue & alphaMask) != 0) {
            ref_L09_003F9040_00(moby, packedValue & 0xFF, (packedValue >> 8) & 0xFF, (packedValue >> 16) & 0xFF);
        }
        colorWord = ref_L09_003F9040_04;
        goto block_9;
    }
    return;
block_9:
    if ((colorWord & alphaMask) != 0) {
        (*(s32 *)((s8 *)(moby) + (0x78))) = colorWord;
        (*(u16 *)((s8 *)(moby) + (0x34))) = (*(u16 *)((s8 *)(moby) + (0x34))) | 0x10;
    }
}
