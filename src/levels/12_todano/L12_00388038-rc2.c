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
#ifndef NULL
#define NULL 0
#endif

extern s32 ref_L12_00388038_00;
extern struct { s32 w0; s32 w1; s32 w2; } ref_L12_00388038_01;
extern void *ref_L12_00388038_02 __attribute__((sda));

/* Moby class 3871 update. Resets and re-flags every object in a linked chain, but only in the
   one level state where that is wanted. */
void linked_chain_reset(void) {
    s8 *p ;

    if (ref_L12_00388038_00 == 2) {
        s32 five  = 5;
        s32 val  = ref_L12_00388038_01.w0;

        if (val == five) {
            p = ref_L12_00388038_02;
            if (p != NULL) {
                do {
                    *(s32 *)(p + 0x98) = 0;
                    *(u16 *)(p + 0x34) = (u16) ((*(u16 *)(p + 0x34) | 0x41) & 0xEFFF);
                    p = *(s8 **)(p + 0x28);
                } while (p != NULL);
            }
        }
    }
}
