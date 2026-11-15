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

extern s8 ref_L26_003DC048_00[];
extern void ref_L26_003DC048_01(s8 *);
extern void ref_L26_003DC048_02(s8 *, s8 *);
extern f32 ref_L26_003DC048_03(f32, f32);
extern void ref_L26_003DC048_04(s8 *, s8 *, s32, s8 *, f32);

/* Counts down two timers, eases a turning angle towards its goal and keeps the age counter going up. */
void creature_tick_timers(s8 *moby) {
    s8 *vars;
    f32 angle;
    u16 age;

    vars = *(s8 **)(moby + 0x68);
    ref_L26_003DC048_01(vars + 0x220);
    ref_L26_003DC048_01(vars + 0x222);
    ref_L26_003DC048_02(moby, vars + 0x278);
    if (*(u8 *)(moby + 0x95) == 2) {
        angle = ref_L26_003DC048_03(*(f32 *)(vars + 0x27C), 0.209439546f);
        *(f32 *)(vars + 0x27C) = angle;
        ref_L26_003DC048_04(moby, vars + 0x270, 1, ref_L26_003DC048_00, angle);
    } else {
        angle = ref_L26_003DC048_03(*(f32 *)(vars + 0x27C), 0.0116355307f);
        *(f32 *)(vars + 0x27C) = angle;
        ref_L26_003DC048_04(moby, vars + 0x270, 0, ref_L26_003DC048_00, angle);
    }
    age = *(u16 *)(moby + 0x96);
    if (age <= 0xFFFE) {
        *(u16 *)(moby + 0x96) = age + 1;
    }
}
