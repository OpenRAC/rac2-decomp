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
    s32 *slotPtr;
    s32 racerIndex;
    s32 remaining;
    s32 noRacer;
    s32 flagOn;
    s32 activeState;

    vars = *(s8 **)(moby + 0x68);
    noRacer = -1;
    flagOn = 1;
    activeState = 2;

    slotPtr = (s32 *)(vars + 0x1E4);
    remaining = 0x14;
    do {
        racerIndex = *slotPtr;
        remaining -= 1;
        if (racerIndex != noRacer) {
            *(s8 *)(*(s8 **)((s32)((racerIndex << 8) + (s32)ref_L04_0040A5C0_00) + 0x68) + 0xA0) = flagOn;
            *(s8 *)((s32)((*slotPtr << 8) + (s32)ref_L04_0040A5C0_00) + 0x20) = activeState;
        }
        slotPtr += 1;
    } while (remaining >= 0);
}
