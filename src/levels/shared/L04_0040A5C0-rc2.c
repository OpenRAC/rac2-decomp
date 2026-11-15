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

extern s8 *ref_L04_0040A5C0_00;

/* Wakes up every racer linked to this one: sets a flag in its variables and puts it in state 2. */
void racer_activate_linked(s8 *moby) {
    s8 *vars;
    s32 *slot_ptr;
    s32 racer_index;
    s32 remaining;
    s32 no_racer;
    s32 flag_on;
    s32 active_state;

    vars = *(s8 **)(moby + 0x68);
    no_racer = -1;
    flag_on = 1;
    active_state = 2;

    slot_ptr = (s32 *)(vars + 0x1E4);
    remaining = 0x14;
    do {
        racer_index = *slot_ptr;
        remaining -= 1;
        if (racer_index != no_racer) {
            *(s8 *)(*(s8 **)((s32)((racer_index << 8) + (s32)ref_L04_0040A5C0_00) + 0x68) + 0xA0) = flag_on;
            *(s8 *)((s32)((*slot_ptr << 8) + (s32)ref_L04_0040A5C0_00) + 0x20) = active_state;
        }
        slot_ptr += 1;
    } while (remaining >= 0);
}
