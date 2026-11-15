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

extern s32 ref_L00_00410430_00(s32, s32);
extern s32 ref_L00_00410430_01(s32, s32, void *);
extern void *ref_L00_00410430_02(void *, s32, s32, void *, f32, f32, f32, f32);
extern s32 ref_L00_00410430_03(void *, s32);
extern u8 ref_L00_00410430_04[];
extern volatile s32 ref_L00_00410430_05;

/* Starts an effect on the object. Mode 0 creates a new one; other modes set up counters and start it differently. */
void charge_shot_start_effect(void *moby, s32 param, s32 mode) {
    u8 *state = *(u8 **)((u8 *)moby + 0x68);
    void *spawned;
    s32 index;
    if (mode == 0) {
        ref_L00_00410430_01(5, 0, moby);
        spawned = ref_L00_00410430_02(moby, param, *(s32 *)(state + 0), ref_L00_00410430_04 - 0x70E0, *(f32 *)(state + 8), 2.0f, 5.0f, 0.6f);
        if (spawned != 0) {
            ref_L00_00410430_00(-1, 1);
            ref_L00_00410430_05 = 1;
            *(void **)((u8 *)spawned + 0xB8) = moby;
        }
    } else {
        index = mode - 1;
        *(s32 *)(state + 0x34) = mode;
        *(s32 *)(state + 0x28) = index;
        *(s32 *)(state + 0x2C) = index;
        ref_L00_00410430_01(5, 0, moby);
        ref_L00_00410430_03(moby, param);
    }
}
