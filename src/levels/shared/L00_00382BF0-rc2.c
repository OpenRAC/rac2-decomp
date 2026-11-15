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

extern volatile s32 g_screen_height;
extern void ref_L00_00382BF0_00(void *, s32, s8 *);
extern f32 ref_L00_00382BF0_01(void *, s8 *);
extern void ref_L00_00382BF0_02(s32, s32 *, s32 *);
extern s32 ref_L00_00382BF0_03(s32, u16, u16, s32, s32, s32, f32 *);
extern s32 g_screen_width __attribute__((sda));
extern f32 ref_L00_00382BF0_04 __attribute__((sda));
extern s8 ref_L00_00382BF0_05[];

/* Returns how visible the sun is on screen, or -1 if it is off screen or hidden behind something. */
f32 lens_flare_get_visibility(void *object) {
    s8 point[0x10];
    s32 screen_x;
    s32 screen_y;
    f32 depth;
    s32 vars;

    vars = *(s32 *)((s8 *)object + 0x68);
    ref_L00_00382BF0_00(point, vars, ref_L00_00382BF0_05);
    depth = ref_L00_00382BF0_01(point, ref_L00_00382BF0_05 + 0x230);
    ref_L00_00382BF0_02(vars, &screen_x, &screen_y);
    if ((screen_x < 0) || (screen_x >= (g_screen_width - 0x10)) || (screen_y < 0) || (screen_y >= (g_screen_height - 8)) || !(depth > 0.0f) || (ref_L00_00382BF0_03(-1, (u16) screen_x, (u16) screen_y, 0x10, 8, 0, &ref_L00_00382BF0_04) == -1)) {
        ref_L00_00382BF0_04 = -1.0f;
    }
    return ref_L00_00382BF0_04;
}
