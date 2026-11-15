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

extern s8 ref_L04_00407F80_00[];
extern s8 ref_L04_00407F80_01[];
extern void *ref_L04_00407F80_02 __attribute__((sda));
extern void *ref_L04_00407F80_03 __attribute__((sda));
extern void *ref_L04_00407F80_04 __attribute__((sda));
extern void ref_L04_00407F80_05(void *, void *, void *, void *);
extern s32 ref_L04_00407F80_06(s8 *, s32);
extern void ref_L04_00407F80_07(s8 *, void *);

/* Sets up the object on its first frame, then keeps registering its update routine until the linked trigger fires. */
void func_L04_00407F80(void *moby) {
    void *vars;
    s32 triggerId;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    if ((*(u8 *)((s8 *)(moby) + (0x20))) == 0) {
        ref_L04_00407F80_05(moby, ref_L04_00407F80_02, ref_L04_00407F80_03, ref_L04_00407F80_04);
        (*(u8 *)((s8 *)(moby) + (0x30))) = 0xC4;
        (*(u8 *)((s8 *)(moby) + (0x20))) = 1;
        (*(u16 *)((s8 *)(moby) + (0x34))) = (u16) ((*(u16 *)((s8 *)(moby) + (0x34))) | 1);
        (*(s16 *)((s8 *)(moby) + (0x32))) = 0;
        return;
    }
    triggerId = (*(s32 *)((s8 *)(vars) + (8)));
    if ((triggerId == -1) || (ref_L04_00407F80_06(ref_L04_00407F80_00, triggerId) != 0)) {
        ref_L04_00407F80_05(moby, ref_L04_00407F80_02, ref_L04_00407F80_03, ref_L04_00407F80_04);
        ref_L04_00407F80_07(ref_L04_00407F80_01, moby);
    }
}
