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

/* Returns 1 when this object is a live enemy of one of the three shooter classes. */
s32 shooter_is_enemy_alive(s8 *moby) {
    s32 result = 0;
    if (moby != 0) {
        u8 state_id = *(u8 *)(moby + 0x20);
        if (state_id != 0xFE) {
            if (state_id != 0xFD) {
                s16 class_id = *(s16 *)(moby + 0xAA);
                if (class_id == 0xEC0 /* moby class 3776 */ || class_id == 0xED4 /* moby class 3796 */ || class_id == MOBY_CLASS_RECEIVER_BOT) {
                    result = 1;
                }
            }
        }
    }
    return result;
}
