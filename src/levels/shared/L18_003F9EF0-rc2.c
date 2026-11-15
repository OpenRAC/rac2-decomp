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

extern s32 ref_L18_003F9EF0_00 __attribute__((sda));
extern s32 ref_L18_003F9EF0_01 __attribute__((sda));
extern s32 ref_L18_003F9EF0_02 __attribute__((sda));
extern s32 ref_L18_003F9EF0_03 __attribute__((sda));
extern void ref_L18_003F9EF0_04(s32);
extern void ref_L18_003F9EF0_05(void *);
extern void ref_L18_003F9EF0_06(void *);
extern void ref_L18_003F9EF0_07(s32, s32);
extern void ref_L18_003F9EF0_08(s32, s16);

/* Advances the timed effect sequence by one frame and stops it when its time is up. */
void func_L18_003F9EF0(void *moby) {
    s16 frame;
    s32 entryOffset;
    s32 phaseLength;
    s32 unusedValue;
    s32 phaseStart;
    void *vars;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    frame = (*(s16 *)((s8 *)(vars) + (0xAC)));
    entryOffset = (s32)(*(s16 *)((s8 *)(vars) + (0xAE))) * 4;
    phaseStart = *(s32 *)((s8 *)&ref_L18_003F9EF0_02 + entryOffset);
    phaseLength = *(s32 *)((s8 *)&ref_L18_003F9EF0_03 + entryOffset);

    if ((phaseStart + phaseLength) < frame) {
        (*(s16 *)((s8 *)(vars) + (0xAC))) = 0;
        ref_L18_003F9EF0_08(0, frame);
        ref_L18_003F9EF0_04(0);
        (*(s16 *)((s8 *)(vars) + (0xAE))) = -1;
        return;
    }
    if (phaseStart < frame) {
        ref_L18_003F9EF0_07(1, 0);
    }
    ref_L18_003F9EF0_05((s8 *)&ref_L18_003F9EF0_00 + (s32)(*(s16 *)((s8 *)(vars) + (0xAE))) * 16);
    ref_L18_003F9EF0_06((s8 *)&ref_L18_003F9EF0_01 + (s32)(*(s16 *)((s8 *)(vars) + (0xAE))) * 16);
    (*(s16 *)((s8 *)(vars) + (0xAC))) = (s16)((u16)(*(s16 *)((s8 *)(vars) + (0xAC))) + 1);
}
