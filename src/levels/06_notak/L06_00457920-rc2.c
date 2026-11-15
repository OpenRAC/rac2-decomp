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

extern void *ref_L06_00457920_00(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void ref_L06_00457920_01(s32, s32, f32);
extern s32 ref_L06_00457920_02;
extern s8 ref_L06_00457920_03[];

/* Breaks the object into fifteen flying pieces, each with its own update callback. */
void part_spawn_debris_pieces(void *moby) {
    void *piece;
    s32 pieceVars;
    s32 index;

    index = 0;
    do {
        piece = ref_L06_00457920_00(moby, 2, (*(s16 *)((s8 *)(moby) + (0xAA))), index, (s8 *)moby + 0x10, (s8 *)moby + 0xF0, &ref_L06_00457920_02, 0xFF, 0.0f, 10.0f);
        index += 1;
        if (piece != 0) {
            pieceVars = (*(s32 *)((s8 *)(piece) + (0x68)));
            ref_L06_00457920_01(pieceVars, pieceVars + 0x20, 0.00200000009499490261077880859375f);
            (*(s32 *)((s8 *)(piece) + (0x64))) = (s32)ref_L06_00457920_03;
        }
    } while (index < 0xF);
}
