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

extern void ref_L12_0041BDF8_00(void *);

/* Gives the two beam helper objects back their normal collision. */
void func_L12_0041BDF8(s8 *object) {
    s8 *vars;
    s8 **slot;
    s32 remaining;
    s8 *child;

    if (object != NULL) {
        if (*(s16 *)(object + 0xAA) == 0xFAE /* moby class 4014 */) {
            vars = *(s8 **)(object + 0x68);
            ref_L12_0041BDF8_00(object);
            slot = (s8 **)(vars + 8);
            remaining = 1;
            do {
                child = *slot;
                remaining -= 1;
                if (child != NULL) {
                    *(s32 *)(child + 0x98) = *(s32 *)(*(s8 **)(child + 0x24) + 0x10);
                }
                slot += 1;
            } while (remaining >= 0);
        }
    }
}
