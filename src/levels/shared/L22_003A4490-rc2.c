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
#ifndef NULL
#define NULL 0
#endif

extern s32 ref_L22_003A4490_00(void *, void *, void *);
extern s32 ref_L22_003A4490_01(void *, s32 *, void *);
extern s32 ref_L22_003A4490_02(void *, s32, void *);
extern s32 ref_L22_003A4490_03(void *, void *, s32, s32);
extern s32 ref_L22_003A4490_04 __attribute__((sda));


/* Keeps the three parts attached to the ship lined up with it while it is being shown at the end. */
void func_L22_003A4490(void *obj) {
    void *part ;
    u8 stack_buffer[0x10];
    u8 state1;
    u8 state2;
    u8 state3;
    void *rotated;
    void *vars;

    vars = (*(void **)((s8 *)(obj) + (0x68)));
    part = (*(void **)((s8 *)(vars) + (0x440)));
    if ((part != NULL) && ((*(s16 *)((s8 *)(part) + (0xAA))) == 0xE0A /* moby class 3594 */)) {
        state1 = (*(u8 *)((s8 *)(part) + (0x20)));
        if (state1 != 0xFE) {
            if (state1 != 0xFD) {
                if (((u32)((*(u8 *)((s8 *)(part) + (0x43))) - 1) < 3U) ||
                    ((*(s16 *)((s8 *)(vars) + (0x460))) != 0)) {
                    ref_L22_003A4490_02(obj, 1, part + 0x10);
                } else {
                    ref_L22_003A4490_03(obj, part, 1, 0);
                }
                (*(f32 *)((s8 *)((*(void **)((s8 *)(vars) + (0x440)))) + (0x48))) =
                    (f32)(*(f32 *)((s8 *)(obj) + (0x48)));
            }
        }
    }

    part = (*(void **)((s8 *)(vars) + (0x444)));
    if ((part != NULL) && ((*(s16 *)((s8 *)(part) + (0xAA))) == 0xE0C /* moby class 3596 */)) {
        state2 = (*(u8 *)((s8 *)(part) + (0x20)));
        if (state2 != 0xFE) {
            if (state2 != 0xFD) {
                ref_L22_003A4490_03((*(void **)((s8 *)(vars) + (0x440))), part, 5, 0);
            }
        }
    }

    part = (*(void **)((s8 *)(vars) + (0x448)));
    if ((part != NULL) && ((*(s16 *)((s8 *)(part) + (0xAA))) == 0xF8F /* moby class 3983 */)) {
        state3 = (*(u8 *)((s8 *)(part) + (0x20)));
        if (state3 != 0xFE) {
            if (state3 != 0xFD) {
                if (((*(u16 *)((s8 *)(obj) + (0x34))) ^ 1) & 1) {
                    ref_L22_003A4490_03((*(void **)((s8 *)(vars) + (0x440))), part, 5, 0);
                    ref_L22_003A4490_01(stack_buffer, &ref_L22_003A4490_04,
                                  (*(void **)((s8 *)(vars) + (0x448))) + 0xC0);
                    rotated = (*(void **)((s8 *)(vars) + (0x448))) + 0x10;
                    ref_L22_003A4490_00(rotated, rotated, stack_buffer);
                }
            }
        }
    }
}
