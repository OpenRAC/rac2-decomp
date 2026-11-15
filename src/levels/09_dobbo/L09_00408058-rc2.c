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

/* Switches parts of an object on or off by setting its flag bits and model: each of the three modes turns something on if positive, off if negative. */
void dobbo_set_mode_flags(void *obj, s32 modeA, s32 modeB, s32 modeC) {
    u16 flags;
    u16 newFlags;
    u16 newFlags2 ;
    s32 stateByte ;
    void *classInfo;
    void *classInfo2;
    void *classInfo3;

    if ((obj != 0) &&
        (stateByte = (*(u8 *)((s8 *)(obj) + (0x20))), stateByte != 0xFE) &&
        (stateByte != 0xFD)) {
        if ((modeA != 0) &&
            ((classInfo = (*(void **)((s8 *)(obj) + (0x24))), classInfo == 0) ||
             ((*(s16 *)((s8 *)(classInfo) + (0x46))) != 0x12))) {
            flags = (*(u16 *)((s8 *)(obj) + (0x34)));
            if (modeA > 0) {
                newFlags = flags & 0xFFFD;
            } else {
                newFlags = flags | 2;
            }
            (*(u16 *)((s8 *)(obj) + (0x34))) = newFlags;
        }
        if ((modeB != 0) &&
            ((obj == 0) ||
             ((classInfo2 = (*(void **)((s8 *)(obj) + (0x24))), classInfo2 == 0) ||
              ((*(s16 *)((s8 *)(classInfo2) + (0x46))) != 0x12)))) {
            stateByte = 1;
            if (modeB > 0) {
                (*(s8 *)((s8 *)(obj) + (0x31))) = stateByte;
                newFlags2 = (*(u16 *)((s8 *)(obj) + (0x34))) & 0xFFFE;
            } else {
                (*(s8 *)((s8 *)(obj) + (0x31))) = 0;
                newFlags2 = (*(u16 *)((s8 *)(obj) + (0x34))) | 1;
            }
            (*(u16 *)((s8 *)(obj) + (0x34))) = newFlags2;
        }
        if (modeC != 0) {
            classInfo3 = (*(void **)((s8 *)(obj) + (0x24)));
            if (classInfo3 != 0) {
                if (modeC > 0) {
                    (*(s32 *)((s8 *)(obj) + (0x98))) = (s32)(*(s32 *)((s8 *)(classInfo3) + (0x10)));
                    return;
                }
                (*(s32 *)((s8 *)(obj) + (0x98))) = 0;
            }
        }
    }
}
