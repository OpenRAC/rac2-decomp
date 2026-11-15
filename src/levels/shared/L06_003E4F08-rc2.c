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

extern f32 ref_L06_003E4F08_00 __attribute__((sda));
extern f32 ref_L06_003E4F08_01 __attribute__((sda));
extern f32 ref_L06_003E4F08_02 __attribute__((sda));
extern f32 ref_L06_003E4F08_03 __attribute__((sda));
extern f32 ref_L06_003E4F08_04 __attribute__((sda));
extern void ref_L06_003E4F08_05(void *, void *, void *, f32, f32, f32);
extern void ref_L06_003E4F08_06(void *, void *, void *, f32, f32, f32);

/* Turns the two moving parts of the object toward their targets, except while it is in states 5 or 7. */
void func_L06_003E4F08(void *moby) {
    u8 state;
    s8 *vars;

    state = (*(u8 *)((s8 *)(moby) + (0x20)));
    vars = (*(s8 **)((s8 *)(moby) + (0x68)));
    if ((state != 5) && (state != 7)) {
        ref_L06_003E4F08_05(moby, vars + 0xEC, vars + 0xE8, ref_L06_003E4F08_00, ref_L06_003E4F08_01 * 0.000290888245217502117156982421875f, (*(f32 *)((s8 *)(vars) + (0x108))));
    }
    ref_L06_003E4F08_06(moby, vars + 0xF0, vars + 0xF4, ref_L06_003E4F08_02, ref_L06_003E4F08_03 * 0.000290888245217502117156982421875f, ref_L06_003E4F08_04 * 0.000290888245217502117156982421875f);
}
