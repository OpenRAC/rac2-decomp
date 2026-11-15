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

extern s32 func_00115F28(s32);
extern s32 *func_001236C8(void *, s32);
extern s32 func_00123930(s32);
extern void func_00123978(s32, void *, void *, void *);

/* Gathers and sorts the frame records of a code module the first time they are needed. */
void func_00123A00(void *module) {
    u32 builder[6];
    s32 *listCursor;
    s32 *fdeLists;
    s32 *fdeLists2;
    s32 total;
    s32 byteCount;

    fdeLists = (*(s32 **)((s8 *)(module) + (0xC)));
    if (fdeLists != 0) {
        listCursor = fdeLists;
        total = 0;
        if (*listCursor != 0) {
            do {
                total += CountUsableFdeRecords(*listCursor);
                listCursor++;
            } while (*listCursor != 0);
        }
    } else {
        total = CountUsableFdeRecords((*(s32 *)((s8 *)(module) + (8))));
    }
    byteCount = total * 4;
    (*(s32 *)((s8 *)(module) + (0x10))) = total;
    builder[0] = Malloc(byteCount);
    builder[2] = Malloc(byteCount);
    builder[4] = 0xFFFFFFFF;
    builder[1] = 0;
    builder[3] = 0;
    builder[5] = 0;
    fdeLists2 = (*(s32 **)((s8 *)(module) + (0xC)));
    if (fdeLists2 != 0) {
        listCursor = fdeLists2;
        if (*listCursor != 0) {
            do {
                CollectFdeRecords(*listCursor, builder, &builder[4], &builder[5]);
                listCursor++;
            } while (*listCursor != 0);
        }
    } else {
        CollectFdeRecords((*(s32 *)((s8 *)(module) + (8))), builder, &builder[4], &builder[5]);
    }
    (*(s32 **)((s8 *)(module) + (0xC))) = SortFdeVector(builder, total);
    (*(s32 *)((s8 *)(module) + (0))) = builder[4];
    (*(s32 *)((s8 *)(module) + (4))) = builder[5];
}
