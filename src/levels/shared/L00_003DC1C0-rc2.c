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

extern s8 g_hero_state[];
extern f32 ref_L00_003DC1C0_00 __attribute__((sda));
extern f32 ref_L00_003DC1C0_01 __attribute__((sda));
extern f32 ref_L00_003DC1C0_02 __attribute__((sda));
extern f32 ref_L00_003DC1C0_03 __attribute__((sda));
extern s32 ref_L00_003DC1C0_04(s32, s32, s32, s32, f32, f32, f32, f32);
extern f32 ref_L00_003DC1C0_05(f32, f32);
extern void ref_L00_003DC1C0_06(s32, s32, s32, f32);
extern void ref_L00_003DC1C0_07(s32, s32, s32, s32, f32, f32, f32, f32);

/* Tries to throw something in an arc away from the camera and, if that fails, tilts the vector a little. */
s32 weapon_throw_along_camera_arc(s32 object, s32 outVector, s32 unused, s32 flags) {
    s8 *camera;
    s32 cameraUp;
    s32 result;

    camera = g_hero_state;
    result = ref_L00_003DC1C0_04(*(s32 *)(camera + 0x2290) + 0xC0, 5, 0, flags, ref_L00_003DC1C0_01, *(f32 *)(camera + 0x98), 0.39269909f, 0.39269909f);
    ref_L00_003DC1C0_07(outVector, object + 0x10, result, 0, ref_L00_003DC1C0_02, ref_L00_003DC1C0_05(ref_L00_003DC1C0_02, ref_L00_003DC1C0_01), ref_L00_003DC1C0_00 * 0.016666668f, ref_L00_003DC1C0_03 * 0.00027777778f);
    if (result == 0) {
        cameraUp = *(s32 *)(camera + 0x2290) + 0xE0;
        ref_L00_003DC1C0_06(outVector, outVector, cameraUp, ref_L00_003DC1C0_05(-0.19634955f, 0.19634955f));
    }
    return result;
}
