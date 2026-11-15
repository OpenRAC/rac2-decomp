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

extern s8 D_001A63A8[];

/* Tries to claim the single attack turn: if nobody has it, records this enemy and starts a delay taken from its table. Returns 1 on success. */
s32 func_L12_0041A6D0(s8 *moby, u32 slot) {
    s8 *turnState;
    s8 *vars;
    s32 delay;

    turnState = gMusicState;
    if ((*(s32 *)(turnState + 0x68) == 0) && (*(s32 *)(turnState + 0x24) == -1)) {
        vars = *(s8 **)(moby + 0x68);
        if (slot >= 10) {
            return 0;
        }
        delay = *(s32 *)(vars + (slot << 2) + 0x230);
        *(s8 **)(turnState + 0x28) = moby;
        *(s32 *)(turnState + 0x24) = delay + 0x7D0;
        return 1;
    }
    return 0;
}
