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

extern void ref_L00_002A6708_00(s32, void *);

typedef struct {
    s8 pad0[0x2290];
    s32 f2290;
    s8 pad1[0x198];
    s32 slots[9];
    void *ptrs[9];
} Ctx;

extern Ctx g_hero_state;
extern s8 g_sound_state[];

/* Goes through nine tracked slots. If a slot still points at a live entry it runs a cleanup on it, then marks the slot as empty. */
void hero_clear_tracked_slots(void) {
    Ctx *ctx = &g_hero_state;
    s8 *table = g_sound_state;
    void **owner_ptrs = ctx->ptrs;
    s32 *slot_ptr = ctx->slots;
    s32 byte_offset = 0;
    s32 remaining = 8;
    s32 slot_index;
    void *owner;
    s8 *entry;
    u8 is_active;
    s32 none = -1;

    do {
        owner = *(void **)(byte_offset + (s32)owner_ptrs);
        slot_index = *slot_ptr;
        if (owner != 0) {
            if (slot_index == none) {
                *slot_ptr = none;
                goto L_inc;
            }
            entry = table + slot_index * 0x70;
            if (*(s32 *)(entry + 0x88) != (s32)owner) {
                *slot_ptr = none;
                goto L_inc;
            }
            is_active = *(u8 *)(entry + 0x74);
        } else {
            if (slot_index == none) {
                *slot_ptr = none;
                goto L_inc;
            }
            entry = table + slot_index * 0x70;
            owner = entry;
            if (*(s32 *)(entry + 0x88) != ctx->f2290) {
                *slot_ptr = none;
                goto L_inc;
            }
            is_active = *(u8 *)(entry + 0x74);
        }
        if (is_active == 0) {
            *slot_ptr = none;
            goto L_inc;
        }
        ref_L00_002A6708_00(slot_index, owner);
        *slot_ptr = none;
    L_inc:
        slot_ptr += 1;
        remaining -= 1;
        byte_offset += 4;
    } while (remaining >= 0);
}
