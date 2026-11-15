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

extern s32 D_001A7000[];
extern s32 D_001A0000[];

/* Runs every shutdown function in a list, last one first. */
void shutdown_run_callbacks(void) {
    s64 count;
    s32 remaining;
    s32 *entry;
    s32 callback;

    count = D_001A7000[0];
    if (count == -1) {
        count = 0;
        if (D_001A7000[1] != 0) {
            do {
                count = count + 1;
            } while (D_001A7000[count + 1] != 0);
        }
    }
    remaining = count;
    if (remaining != 0) {
        entry = (s32 *) ((s8 *) D_001A0000 + 0x7000) + remaining;
        callback = *entry;
        do {
            remaining -= 1;
            entry -= 1;
            ((void (*)(void)) callback)();
            if (remaining != 0) {
                callback = *entry;
            }
        } while (remaining != 0);
    }
}
