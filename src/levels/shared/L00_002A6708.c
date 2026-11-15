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

extern Ctx D_00189E20;
extern s8 D_00188660[];

/* Goes through nine tracked slots. If a slot still points at a live entry it runs a cleanup on it, then marks the slot as empty. */
void func_L00_002A6708(void) {
    Ctx *ctx = &gHeroState;
    s8 *table = gSoundState;
    void **ownerPtrs = ctx->ptrs;
    s32 *slotPtr = ctx->slots;
    s32 byteOffset = 0;
    s32 remaining = 8;
    s32 slotIndex;
    void *owner;
    s8 *entry;
    u8 isActive;
    s32 none = -1;

    do {
        owner = *(void **)(byteOffset + (s32)ownerPtrs);
        slotIndex = *slotPtr;
        if (owner != 0) {
            if (slotIndex == none) {
                *slotPtr = none;
                goto L_inc;
            }
            entry = table + slotIndex * 0x70;
            if (*(s32 *)(entry + 0x88) != (s32)owner) {
                *slotPtr = none;
                goto L_inc;
            }
            isActive = *(u8 *)(entry + 0x74);
        } else {
            if (slotIndex == none) {
                *slotPtr = none;
                goto L_inc;
            }
            entry = table + slotIndex * 0x70;
            owner = entry;
            if (*(s32 *)(entry + 0x88) != ctx->f2290) {
                *slotPtr = none;
                goto L_inc;
            }
            isActive = *(u8 *)(entry + 0x74);
        }
        if (isActive == 0) {
            *slotPtr = none;
            goto L_inc;
        }
        ref_L00_002A6708_00(slotIndex, owner);
        *slotPtr = none;
    L_inc:
        slotPtr += 1;
        remaining -= 1;
        byteOffset += 4;
    } while (remaining >= 0);
}
