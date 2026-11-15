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

extern f32 ref_L06_004576C8_00 __attribute__((sda));
extern s32 ref_L06_004576C8_01;
extern s32 ref_L06_004576C8_02;
extern f32 ref_L06_004576C8_03(f32);
extern void ref_L06_004576C8_04(void *, f32, f32, f32);
extern s32 ref_L06_004576C8_05(void *, void *, s32, void *, s32, s32);

/* Sets up eight effect emitters around the object, each aimed in its own direction. */
void func_L06_004576C8(void *moby) {
    f32 *angles;
    f32 pitchDeg;
    f32 yaw;
    s32 *handles;
    s8 *dirs;
    s8 *vars;
    s32 remaining;

    angles = &ref_L06_004576C8_00;
    remaining = 7;
    vars = (*(s8 **)((s8 *)(moby) + (0x68)));
    handles = (s32 *)(vars + 0x80);
    dirs = vars + 0xA0;
    do {
        remaining -= 1;
        yaw = ref_L06_004576C8_03(angles[0] * 0.017453294f);
        pitchDeg = angles[1];
        angles += 2;
        ref_L06_004576C8_04(dirs, 1.0f, yaw, ref_L06_004576C8_03(pitchDeg * 0.017453294f));
        dirs += 0x10;
        *handles = ref_L06_004576C8_05(&ref_L06_004576C8_01, &ref_L06_004576C8_02, 0x3C3C3C78, moby, 0x19, 0);
        handles += 1;
    } while (remaining >= 0);
}
