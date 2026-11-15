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

extern s8 D_00222AE0[];
extern s8 D_002222E0[];
extern s8 g_hero_position[];
extern s32 IsPointInCuboid(s32 noise_ptr, s32 index);

/* Sets the height of each surface grid point from its base height plus the wave noise. */
void surface_grid_update_heights(void *object) {
    void *state;
    s32 index;
    s32 flags;
    s32 row;
    s32 table_offset;
    s8 *noise_ptr;
    s8 *height_ptr;
    s8 *table_ptr;

    state = (*(void **)((s8 *)(object) + (0x68)));
    index = (*(s32 *)((s8 *)(state) + (0x44)));
    if (index != -1 && IsPointInCuboid((s32)g_hero_position, index) != 0 && !((*(u32 *)((s8 *)(state) + (0x4C))) & 4)) {
        table_offset = (*(s32 *)((s8 *)(state) + (0x40))) << 10;
        table_ptr = (s8 *)D_00222AE0;
        table_ptr += 8;
        height_ptr = table_ptr + table_offset;
        noise_ptr = D_002222E0;
        for (index = 0; index < 0x40; index++) {
            *(f32 *)height_ptr = (*(f32 *)((s8 *)(state) + (0x70))) + (*(f32 *)((s8 *)(state) + (4)));
            flags = (*(s32 *)((s8 *)(state) + (0x4C)));
            if (~flags & 0x10) {
                if ((index % 8 != 0 && index % 8 != 7) || ((flags ^ 1) & 1)) {
                    row = index / 8;
                    if ((row != 0 && row != 7) || !((*(s32 *)((s8 *)(state) + (0x4C))) & 2)) {
                        *(f32 *)height_ptr += *(f32 *)noise_ptr * (*(f32 *)((s8 *)(state) + (0x34)));
                    }
                }
            }
            noise_ptr += 0x20;
            height_ptr += 0x10;
        }
    }
}
