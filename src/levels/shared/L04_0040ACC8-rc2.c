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

extern s8 *ref_L04_0040ACC8_00 __attribute__((sda));
extern s32 ref_L04_0040ACC8_01 __attribute__((sda));
extern s32 ref_L04_0040ACC8_02 __attribute__((sda));
extern s32 ref_L04_0040ACC8_03 __attribute__((sda));

/* Counts how often a player event happens in a row. Three times in a row sets a flag, and a long gap resets the count. */
void racer_update_event_streak(void) {
    s8 *vars;
    s32 new_count;
    s32 event_flag;

    vars = *(s8 **)(ref_L04_0040ACC8_00 + 0x68);
    if (*(s32 *)(vars + 0x744) < 5) {
        event_flag = *(s32 *)(vars + 0x724);
        ref_L04_0040ACC8_01 = 1;
        if (event_flag != 0) {
            new_count = ref_L04_0040ACC8_03 + 1;
            ref_L04_0040ACC8_03 = new_count;
            if (new_count == 3) {
                ref_L04_0040ACC8_02 = 1;
            }
        }
    } else if (ref_L04_0040ACC8_03 < 4) {
        ref_L04_0040ACC8_03 = 0;
    }
    *(s32 *)(vars + 0x724) = 0;
    *(s32 *)(vars + 0x744) = 0;
}
