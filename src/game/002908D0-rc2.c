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

extern s32 func_00288768(s32 a0);
extern s8 D_001A7B68[];
extern s8 D_001A7B88[];

/* Walks the item list, clears every entry that is not allowed, and tells whether all were fine. */
s32 func_002908D0(void) {
    s32 entry;
    s32 listEnd;
    s32 allValid;
    u8 raw;
    s32 itemId;

    s32 skipId = 0x1E;
    entry = (s32)D_001A7B68;
    listEnd = (s32)D_001A7B88;
    allValid = 1;
    do {
        raw = *(u8 *)entry;
        if (raw == 0xFF) {
            entry++;
            continue;
        }
        itemId = raw & 0x3F;
        if (itemId == skipId) {
            entry++;
            continue;
        }
        if (IsHelpIdInMappingTable(itemId) == 0 || itemId == 0) {
            *(u8 *)entry = 0xFF;
            allValid = 0;
        }
        entry++;
    } while (entry < listEnd);
    return allValid;
}
