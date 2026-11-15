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
#ifndef NULL
#define NULL 0
#endif

extern s8 *ref_L12_00413EA8_00[];
extern s8 *ref_L12_00413EA8_01;

/* Marks every guard in the given group as having been alerted. */
void guard_alert_group(void *arg0, s32 group) {
    s8 *table ;
    s8 *entry ;
    s8 *record;
    s32 entryValue;

    if (group != 0xFF) {
        table = ref_L12_00413EA8_00[group];
        if (table != NULL) {
            entry = table;
            do {
                record = ref_L12_00413EA8_01 + ((*(u16 *)entry & 0x7FFF) << 8);
                if (*(s8 *)(record + 0x20) >= 0 && *(s16 *)(record + 0xAA) == 0xF31 /* moby class 3889 */) {
                    *(u8 *)(*(s8 **)(record + 0x68) + 0x2EA) = 1;
                }
                entryValue = *(s16 *)entry;
                entry += 2;
            } while (entryValue >= 0);
        }
    }
}
