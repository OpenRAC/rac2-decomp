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

extern s32 ref_L18_00427B48_00;
extern u16 *ref_L18_00427B48_01[];

/* Marks every live shooter in the given group so it will start firing (sets a flag in its state). */
void shooter_flag_group(s32 unusedArg, s32 group) {
    u16 *entry;
    u16 *list;
    s8 *target;
    s32 entryValue;

    if (group != 0xFF) {
        list = ref_L18_00427B48_01[group];
        if (list != 0) {
            entry = list;
            do {
                target = (s8 *)ref_L18_00427B48_00 + ((*entry & 0x7FFF) << 8);
                if (target != 0) {
                    if (*(s16 *)(target + 0xAA) == 0xEC0 /* moby class 3776 */) {
                        s32 stateId = *(u8 *)(target + 0x20);
                        if (stateId != 0xFE) {
                            if (stateId != 0xFD) {
                                *(s8 *)(*(s8 **)(target + 0x68) + 0x39A) = 1;
                            }
                        }
                    }
                }
                entryValue = *(s16 *)entry;
                entry += 1;
            } while (entryValue >= 0);
        }
    }
}
