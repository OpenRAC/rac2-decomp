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

extern s8 D_00189EA0[];
extern s32 ref_L00_003CF438_00(s32, s32);
extern void ref_L00_003CF438_01(s32, s32, void *);
extern f32 ref_L00_003CF438_02(f32);
extern f32 ref_L00_003CF438_03(f32);
extern void ref_L00_003CF438_04(void *, void *, void *);
extern void ref_L00_003CF438_05(void *);

typedef struct { f32 first; f32 second; s32 flag; s32 pad; } StackArgs;
/* Waits for a trigger, then pushes the object along its heading for about 100 frames and removes it. */
void func_L00_003CF438(void *object) {
    s32 *state  = *(s32 **)((s8 *)object + 0x68);
    f32 angle ;
    f32 pi ;
    f32 ratio ;
    StackArgs args;
    s32 count;
    if (*(volatile u8 *)((s8 *)object + 0x20) == 0 && ref_L00_003CF438_00((s32)gHeroPosition, state[0]) != 0) {
        *(volatile u8 *)((s8 *)object + 0x20) = 1;
        state[1] = 0;
        ref_L00_003CF438_01(0, 0, object);
    }
    if (*(volatile u8 *)((s8 *)object + 0x20) == 1) {
        angle = *(volatile f32 *)((s8 *)object + 0xF8);
        pi = 3.141593f;
        ratio = 0.4166667f;
        args.first = ref_L00_003CF438_02(angle + pi) * ratio;
        args.second = ref_L00_003CF438_03(*(volatile f32 *)((s8 *)object + 0xF8) + pi) * ratio;
        args.flag = 0;
        ref_L00_003CF438_04((s8 *)object + 0x10, (s8 *)object + 0x10, &args);
        count = state[1] + 1;
        state[1] = count;
        if (count >= 0x65) {
            ref_L00_003CF438_05(object);
        }
    }
}
