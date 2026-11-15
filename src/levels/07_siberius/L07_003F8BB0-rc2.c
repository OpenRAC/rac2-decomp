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

typedef int TI __attribute__((mode(TI)));

extern void ref_L07_003F8BB0_00(s32, s32, s8 *);
extern void ref_L07_003F8BB0_01(s8 *, s32, TI *);
extern void ref_L07_003F8BB0_02(s8 *, TI *);
extern void ref_L07_003F8BB0_03(s8 *, s32, TI *, TI *, f32);

/* Looks up a joint position and direction on the object and passes them, with the target and a power value, to an effect routine. */
void func_L07_003F8BB0(s8 *moby) {
    TI jointPos;
    TI jointDir;
    s8 *vars;

    vars = *(s8 **)(moby + 0x68);
    ref_L07_003F8BB0_00(3, 0, moby);
    ref_L07_003F8BB0_01(moby, 0, &jointPos);
    ref_L07_003F8BB0_02(moby, &jointDir);
    ref_L07_003F8BB0_03(moby, *(s32 *)(vars + 0x418), &jointPos, &jointDir, (f32)*(u8 *)(vars + 0x35));
}
