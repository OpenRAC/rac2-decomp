
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

extern s32 D_001A7288 __attribute__((sda));
extern s32  D_001B1888[] __attribute__((sda));

extern s32 func_0029D4D0();

/* Unpacks the packed data of one HUD bank into the given memory address and clears that bank's flag. */
void func_00292B20(s32 bankIndex, s32 target) {
    s32 root;
    s32 alignedTarget;
    s32 bankBase;
    s32 entryBase;

    alignedTarget = (target + 0xF) & 0xFFFFFFF0;
    if (alignedTarget != 0) {
        root = D_001A7288;
        entryBase = root + (bankIndex * 8);
        fast_decompress((*(s32 *)((char *)(entryBase) + (0x20))) + root, alignedTarget);
    }
    bankBase = D_001B1888[0] + (bankIndex * 4);
    (*(s32 *)((char *)(bankBase) + (0x74))) = 0;
}
