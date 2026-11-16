#include "names.h"
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

/* func_PAL_L07_0040E120, the PAL copy of func_L07_00409300: the same C, where both float
 * arguments are scaled by 6/5 and case 1 first leaves when D_001A79F0 (the current area) is 0x33. */

extern s32 g_current_map_index MACRO_ADDR;
extern s32 ref_L07_00409300_00 __attribute__((sda));

extern void ref_L07_00409300_01(s8 *, s32, s32);
extern void ref_L07_00409300_02(s8 *, s8 *, s32, s32, f32);

/* Updates a TV Screens moby: sets it up in state 0, then keeps its screen picture running in state 1 (PAL: 50 Hz rates). */
void tv_l07_screens_update_pal(s8 *moby) {
    s8 *vars;
    u8 state;

    state = *(u8 *)(moby + 0x20);
    vars = *(s8 **)(moby + 0x68);
    switch (state) {
    case 0:
        ref_L07_00409300_01(moby, 1, -1);
        return;
    case 1:
        if (g_current_map_index == 0x33) {
            break;
        }
        if (vars != 0) {
            if (ref_L07_00409300_00 == 2) {
                ref_L07_00409300_02(moby, vars + 0xC, 0x80AABED2, 0x80466464, 0.06632252f);
            } else {
                ref_L07_00409300_02(moby, vars + 0xC, 0x8096AAAA, 0x80466464, 0.04537857f);
            }
        }
        break;
    }
}
