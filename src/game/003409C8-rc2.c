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

extern s32 func_002E5E58(s32 a, s32 b, s32 c);
extern void func_003407F8(void *o, void *p, s32 n);
extern s16 D_00259F58[][5];

struct Obj {
    s8 pad[0x814];
    s32 column;  /* 0x814 */
    s32 page;  /* 0x818 */
    s32 flag;  /* 0x81C */
    s32 value;  /* 0x820 */
};

/* Moves the selection around the four-column item grid and remembers the selected value. */
void func_003409C8(struct Obj *o, s32 flags) {
    if (flags & 0x1000) {
        s32 minusOne;
        s32 newPage;
        s32 nextValue;
        PlaySoundFromGlobalBank(3, 0, 0);
        minusOne = -1;
        nextValue = o->page - 1;
        newPage = (minusOne < nextValue) ? nextValue : 5;
        o->page = newPage;
    } else if (flags & 0x4000) {
        s32 nextValue;
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = o->page + 1;
        nextValue = (5 < nextValue) ? 0 : nextValue;
        o->page = nextValue;
    } else if (flags & 0x8000) {
        s32 nextValue;
        s32 savedPage;
        s32 pageOffset;
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = o->column - 1;
        o->column = nextValue;
        if (nextValue < 0) {
            savedPage = o->page;
            o->column = 3;
            pageOffset = savedPage - 4;
            if ((u32)pageOffset < 2) {
                o->column = 2;
                o->page = pageOffset;
                o->flag = 1;
            }
        }
    } else if (flags & 0x2000) {
        s32 nextValue;
        s32 currentPage;
        PlaySoundFromGlobalBank(3, 0, 0);
        nextValue = o->column + 1;
        o->column = nextValue;
        if (nextValue >= 4) {
            o->column = 0;
            currentPage = o->page;
            if (currentPage == 4) {
                o->page = 0;
                o->flag = 1;
            } else if (currentPage == 5) {
                o->column = 1;
                o->page = 1;
                o->flag = 1;
            }
        }
    } else if (flags & 0x40) {
        AddMenuItemToRing(o, D_00259F58, 4);
    }
    o->value = D_00259F58[o->column + o->page * 4][3];
}
