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

extern f32 *map_get_coefficients(s32);
extern s32 g_current_map_index;

/* Turns a world position into a 0-1 position on the map screen for the given map (or the current map when -1 is passed). */
void map_convert_world_to_map_position(f32 world_x, f32 world_y, f32 *out_map_x, f32 *out_map_y, s32 requested_map) {
    f32 *x_transform;
    f32 *y_transform;
    s32 map_index;

    map_index = (~requested_map != 0) ? requested_map : g_current_map_index;
    if (map_index <= -1) {
        map_index = 0;
    }
    if (map_index >= 0x15) {
        map_index = 0;
    }
    x_transform = map_get_coefficients(map_index);
    *out_map_x = (x_transform[0] + (map_get_coefficients(map_index)[1] * world_x)) * 0.001953125f;
    y_transform = map_get_coefficients(map_index);
    *out_map_y = (y_transform[2] + (map_get_coefficients(map_index)[3] * world_y)) * 0.001953125f;
}
