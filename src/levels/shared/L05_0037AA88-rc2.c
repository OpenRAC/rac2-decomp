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

extern s8 ref_L05_0037AA88_00[];

/* Follows the chain of slots from the given one and returns the first active slot, or -1. */
s32 func_L05_0037AA88(s32 index) {
    s32 stride ;
    s32 active ;
    s8 *nextField;
    s8 *activeField;
    s32 current;
    s32 offset;

    stride = 0x28;
    nextField = ref_L05_0037AA88_00;
    activeField = nextField - 4;
    current = index;
loop_1:
    if (current < 0) {
        goto end_1;
    }
    offset = current * stride;
    active = *(s32 *)(offset + (s32)activeField);
    if (active != 0) {
        return current;
    }
    current = *(s32 *)(offset + (s32)nextField);
    goto loop_1;
end_1:
    return -1;
}
