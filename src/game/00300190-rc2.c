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

extern s32 D_001AD7EC;
extern s8 D_001A8BD0;
extern s32 g_hero_moby[];
extern void moby_transform_point_and_rotation_by_parent(s32, s32, void *, void *, void *, void *);
typedef int TI __attribute__((mode(TI)));

/* Copies a 4-float vector, passing it through the current transform when one is set. */
void vec_transform_or_copy(void *dest, void *source) {
    s8 scratch[16];
    s32 transform = D_001AD7EC;
    if (transform != 0) {
        moby_transform_point_and_rotation_by_parent(g_hero_moby[0], transform, source, &D_001A8BD0, dest, scratch);
        return;
    }
    *(TI *)dest = *(TI *)source;
}
