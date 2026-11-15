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

/* Forgets any of the four linked mobys that have died or run out of health. */
void moby_clear_dead_linked(s8 *moby) {
    s32 remaining;
    s8 **slot;
    s8 *linked;
    s8 *linked_vars;

    remaining = 3;
    slot = (s8 **)((*(s8 **)((char *)(moby) + (0x68))) + 0xE0);
    do {
        linked = *slot;
        remaining -= 1;
        if (linked != 0) {
            linked_vars = (*(s8 **)((char *)(linked) + (0x68)));
            if ((*(s8 *)((char *)(linked) + (0x20))) < 0) {
                goto store;
            }
            if ((*(f32 *)((char *)(linked_vars) + (0x40))) <= 0.0f) {
            store:
                *slot = 0;
            }
        }
        slot = slot + 1;
    } while (remaining >= 0);
}
