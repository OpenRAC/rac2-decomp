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

extern s8 D_001BF200;

/* Finds the effect slot owned by this object. Returns it if it matches the flag mask, otherwise releases the slot when allowed. */
void *func_002A9640(void *object, u32 flagMask, s32 keepSlot) {
    u8 slotIndex;
    s8 *entry;
    void *owner;

    slotIndex = *(u8 *)((s8 *)object + 0xA8);
    if (slotIndex == 0xFF) {
        return 0;
    }
    entry = (s8 *)&D_001BF200 + (slotIndex << 6);
    owner = *(void **)(entry + 0x38);
    if (owner != object) {
        return 0;
    }
    if (*(u32 *)(entry + 0x24) & flagMask) {
        return entry;
    }
    if (keepSlot == 0) {
        *(u8 *)((s8 *)owner + 0xA8) = 0xFF;
    }
    return 0;
}
