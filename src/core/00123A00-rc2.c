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

extern void *malloc(s32);
extern s32 *eh_sort_fde_vector(void *, s32);
extern s32 eh_count_fde_records(s32);
extern void eh_collect_fde_records(s32, void *, void *, void *);

/* Gathers and sorts the frame records of a code module the first time they are needed. */
void eh_init_object(void *module) {
    u32 builder[6];
    s32 *list_cursor;
    s32 *fde_lists;
    s32 *fde_lists2;
    s32 total;
    s32 byte_count;

    fde_lists = (*(s32 **)((s8 *)(module) + (0xC)));
    if (fde_lists != 0) {
        list_cursor = fde_lists;
        total = 0;
        if (*list_cursor != 0) {
            do {
                total += eh_count_fde_records(*list_cursor);
                list_cursor++;
            } while (*list_cursor != 0);
        }
    } else {
        total = eh_count_fde_records((*(s32 *)((s8 *)(module) + (8))));
    }
    byte_count = total * 4;
    (*(s32 *)((s8 *)(module) + (0x10))) = total;
    builder[0] = malloc(byte_count);
    builder[2] = malloc(byte_count);
    builder[4] = 0xFFFFFFFF;
    builder[1] = 0;
    builder[3] = 0;
    builder[5] = 0;
    fde_lists2 = (*(s32 **)((s8 *)(module) + (0xC)));
    if (fde_lists2 != 0) {
        list_cursor = fde_lists2;
        if (*list_cursor != 0) {
            do {
                eh_collect_fde_records(*list_cursor, builder, &builder[4], &builder[5]);
                list_cursor++;
            } while (*list_cursor != 0);
        }
    } else {
        eh_collect_fde_records((*(s32 *)((s8 *)(module) + (8))), builder, &builder[4], &builder[5]);
    }
    (*(s32 **)((s8 *)(module) + (0xC))) = eh_sort_fde_vector(builder, total);
    (*(s32 *)((s8 *)(module) + (0))) = builder[4];
    (*(s32 *)((s8 *)(module) + (4))) = builder[5];
}
