
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

/* Counts the function pointers in the table at D_001A7000 (using the first word when it is not
   -1) and calls them from last to first. */
void func_0011FB8C(void) {
    s64 var_a1;
    s32 var_s1;
    s32 *var_s0;
    s32 var_v0;

    var_a1 = D_001A7000[0];
    if (var_a1 == -1) {
        var_a1 = 0;
        if (D_001A7000[1] != 0) {
            do {
                var_a1 = var_a1 + 1;
            } while (D_001A7000[var_a1 + 1] != 0);
        }
    }
    var_s1 = var_a1;
    if (var_s1 != 0) {
        var_s0 = (s32 *) ((s8 *) D_001A0000 + 0x7000) + var_s1;
        var_v0 = *var_s0;
        do {
            var_s1 -= 1;
            var_s0 -= 1;
            ((void (*)(void)) var_v0)();
            if (var_s1 != 0) {
                var_v0 = *var_s0;
            }
        } while (var_s1 != 0);
    }
}
