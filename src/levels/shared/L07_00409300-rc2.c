
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

extern s32 ref_L07_00409300_00 __attribute__((sda));

extern void ref_L07_00409300_01(s8 *, s32, s32);
extern void ref_L07_00409300_02(s8 *, s8 *, s32, s32, f32);

/* Updates a TV Screens moby: sets it up in state 0, then keeps its screen picture running in state 1. */
void func_L07_00409300(s8 *moby) {
    s8 *vars;
    u8 state;

    state = *(u8 *)(moby + 0x20);
    vars = *(s8 **)(moby + 0x68);
    switch (state) {
    case 0:
        ref_L07_00409300_01(moby, 1, -1);
        return;
    case 1:
        if (vars != 0) {
            if (ref_L07_00409300_00 == 2) {
                ref_L07_00409300_02(moby, vars + 0xC, 0x80AABED2, 0x80466464, 0.05526876822113991f);
            } else {
                ref_L07_00409300_02(moby, vars + 0xC, 0x8096AAAA, 0x80466464, 0.03781547397375107f);
            }
        }
        break;
    }
}
