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

extern s32 ref_L00_003FE8D0_00 __attribute__((sda));

/* First-frame setup: clears the object's private data and moves it to the running state. */
void moby_init_private_data(void *object) {
    s8 *vars ;
    s32 count ;
    s8 *slot;

    vars = (*(s8 **)((s8 *)(object) + (0x68)));
    if ((*(u8 *)((s8 *)(object) + (0x20))) == 0) {
        count = ref_L00_003FE8D0_00;
        (*(s32 *)((s8 *)(vars) + (0))) = 0;
        (*(s16 *)((s8 *)(vars) + (6))) = 0;
        if (count > 0) {
            slot = vars + 0x10;
            do {
                *(s32 *)slot = 0;
                count -= 1;
                slot += 4;
            } while (count != 0);
        }
        (*(u8 *)((s8 *)(object) + (0x20))) = 1U;
    }
}
