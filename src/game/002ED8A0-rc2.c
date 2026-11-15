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

extern s8 D_00262958[];

/* Follows a chain of 0x28-byte table entries starting at the given index and returns the last used entry, or -1 if there is none. */
s32 table_find_last_used_entry(s32 index) {
    s32 table;
    s32 offset;
    s8 *nextBase;
    s32 stride ;
    s32 cur;
    s32 last ;

    cur = index;
    last = -1;
    table = (s32)D_00262958;
    stride = 0x28;
    nextBase = (s8 *)(table - 0x14);
    for (;;) {
        if (cur < 0) {
            goto done;
        }
        offset = cur * stride;

        if (*(s32 *)(offset + table) == 0) {
            return last;
        }
        last = cur;
        cur = *(s32 *)(offset + (s32)nextBase);
    }
done:
    return last;
}
