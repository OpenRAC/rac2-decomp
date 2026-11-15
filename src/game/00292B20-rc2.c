#include "names.h"

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

extern s32 fast_decompress();

/* Unpacks the packed data of one HUD bank into the given memory address and clears that bank's flag. */
void hud_unpack_bank_data(s32 bank_index, s32 target) {
    s32 root;
    s32 aligned_target;
    s32 bank_base;
    s32 entry_base;

    aligned_target = (target + 0xF) & 0xFFFFFFF0;
    if (aligned_target != 0) {
        root = D_001A7288;
        entry_base = root + (bank_index * 8);
        fast_decompress((*(s32 *)((char *)(entry_base) + (0x20))) + root, aligned_target);
    }
    bank_base = D_001B1888[0] + (bank_index * 4);
    (*(s32 *)((char *)(bank_base) + (0x74))) = 0;
}
