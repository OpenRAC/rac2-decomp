
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

/* The resident table already holds the retail label addresses. The unused
 * label list keeps each C branch available; it is not read by the program. */
extern void *D_L01_002A4420[];

extern s32 ref_L08_00398A90_00 __attribute__((sda));
extern s32 ref_L08_00398A90_01 __attribute__((sda));
extern s32 ref_L08_00398A90_02 __attribute__((sda));
extern s32 ref_L08_00398A90_03 __attribute__((sda));
extern s32 ref_L08_00398A90_04 __attribute__((sda));
extern s32 ref_L08_00398A90_05 __attribute__((sda));
extern void ref_L08_00398A90_06(s32, s32, s32);

extern s32 D_001A79F0;
/* Picks a per-level table from the level number and uses the moby's setting to choose the entry to apply. */
void func_L01_00398A90(s8 *moby) {
    s8 *vars;
    s32 *tab;
    s32 idx;
    s32 k;

    vars = *(s8 **)(0x68 + moby);
    idx = gCurrentMapIndex;
    idx -= 1;
    {
    static void *volatile rc2_labels[] = {&&rc2_case_0, &&rc2_default, &&rc2_default, &&rc2_default, &&rc2_default, &&rc2_default, &&rc2_default, &&rc2_case_7, &&rc2_case_8, &&rc2_default, &&rc2_default, &&rc2_case_11, &&rc2_default, &&rc2_default, &&rc2_default, &&rc2_default, &&rc2_case_16, &&rc2_default, &&rc2_default, &&rc2_case_19};
    u32 rc2_selector = (u32)(idx);
    if (rc2_selector > 19U) goto rc2_default;
goto *D_L01_002A4420[rc2_selector];

    rc2_case_0:
        ref_L08_00398A90_06(4, (&ref_L08_00398A90_00)[*(s32 *)(vars + 0x10)], 1);
        return;
    rc2_case_7:
        ref_L08_00398A90_06(4, (&ref_L08_00398A90_01)[*(s32 *)(vars + 0x10)], 1);
        return;
    rc2_case_8:
        ref_L08_00398A90_06(4, (&ref_L08_00398A90_02)[*(s32 *)(vars + 0x10)], 1);
        return;
    rc2_case_11:
        ref_L08_00398A90_06(4, (&ref_L08_00398A90_03)[*(s32 *)(vars + 0x10)], 1);
        return;
    rc2_case_16:
        ref_L08_00398A90_06(4, (&ref_L08_00398A90_04)[*(s32 *)(vars + 0x10)], 1);
        return;
    rc2_case_19:
        ref_L08_00398A90_06(4, (&ref_L08_00398A90_05)[*(s32 *)(vars + 0x10)], 1);
        return;
    rc2_default:
        return;
    
rc2_switch_end: ;
}
}
