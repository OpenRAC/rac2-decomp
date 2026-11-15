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
void dobbo_set_mode_flags(void *obj, s32 mode_a, s32 mode_b, s32 mode_c) {
    u16 flags;
    u16 new_flags;
    u16 new_flags2 ;
    s32 state_byte ;
    void *class_info;
    void *class_info2;
    void *class_info3;

    if ((obj != 0) &&
        (state_byte = (*(u8 *)((s8 *)(obj) + (0x20))), state_byte != 0xFE) &&
        (state_byte != 0xFD)) {
        if ((mode_a != 0) &&
            ((class_info = (*(void **)((s8 *)(obj) + (0x24))), class_info == 0) ||
             ((*(s16 *)((s8 *)(class_info) + (0x46))) != 0x12))) {
            flags = (*(u16 *)((s8 *)(obj) + (0x34)));
            if (mode_a > 0) {
                new_flags = flags & 0xFFFD;
            } else {
                new_flags = flags | 2;
            }
            (*(u16 *)((s8 *)(obj) + (0x34))) = new_flags;
        }
        if ((mode_b != 0) &&
            ((obj == 0) ||
             ((class_info2 = (*(void **)((s8 *)(obj) + (0x24))), class_info2 == 0) ||
              ((*(s16 *)((s8 *)(class_info2) + (0x46))) != 0x12)))) {
            state_byte = 1;
            if (mode_b > 0) {
                (*(s8 *)((s8 *)(obj) + (0x31))) = state_byte;
                new_flags2 = (*(u16 *)((s8 *)(obj) + (0x34))) & 0xFFFE;
            } else {
                (*(s8 *)((s8 *)(obj) + (0x31))) = 0;
                new_flags2 = (*(u16 *)((s8 *)(obj) + (0x34))) | 1;
            }
            (*(u16 *)((s8 *)(obj) + (0x34))) = new_flags2;
        }
        if (mode_c != 0) {
            class_info3 = (*(void **)((s8 *)(obj) + (0x24)));
            if (class_info3 != 0) {
                if (mode_c > 0) {
                    (*(s32 *)((s8 *)(obj) + (0x98))) = (s32)(*(s32 *)((s8 *)(class_info3) + (0x10)));
                    return;
                }
                (*(s32 *)((s8 *)(obj) + (0x98))) = 0;
            }
        }
    }
}
