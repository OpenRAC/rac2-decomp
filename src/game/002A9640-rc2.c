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

extern s8 g_impact_queue;

/* Finds the effect slot owned by this object. Returns it if it matches the flag mask, otherwise releases the slot when allowed. */
void *part_find_owned_effect_slot(void *object, u32 flag_mask, s32 keep_slot) {
    u8 slot_index;
    s8 *entry;
    void *owner;

    slot_index = *(u8 *)((s8 *)object + 0xA8);
    if (slot_index == 0xFF) {
        return 0;
    }
    entry = (s8 *)&g_impact_queue + (slot_index << 6);
    owner = *(void **)(entry + 0x38);
    if (owner != object) {
        return 0;
    }
    if (*(u32 *)(entry + 0x24) & flag_mask) {
        return entry;
    }
    if (keep_slot == 0) {
        *(u8 *)((s8 *)owner + 0xA8) = 0xFF;
    }
    return 0;
}
