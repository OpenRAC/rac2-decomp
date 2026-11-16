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

extern void FastVecSub(f32 *a, s32 b, s8 *c);
extern void FastVecScale(f32 *a, f32 *b, f32 c);
extern void transform_vector(f32 *a, f32 *b, s8 *c);
extern s8 g_camera_eye_state[];
extern s8 g_projection_scale[];
extern s32 g_screen_width;
extern s32 g_screen_height;

/* Turns a point in the world into a screen position between 0 and 1. */
void gfx_world_to_screen_unit(s32 world_pos, f32 *screen_x, f32 *screen_y) {
    f32 point[4];
    s8 *matrices;
    f32 w;
    f32 pixel_x;
    f32 pixel_y;

    matrices = g_camera_eye_state;
    FastVecSub(point, world_pos, matrices);
    FastVecScale(point, point, 1024.0f);
    point[3] = 1.0f;
    transform_vector(point, point, matrices - 0x100);
    w = point[3];
    FastVecScale(point, point, *(f32 *)g_projection_scale / w);
    pixel_x = point[0] + (f32)(g_screen_width >> 1);
    *screen_x = pixel_x;
    *screen_x = pixel_x / (f32)g_screen_width;
    pixel_y = point[1] + (f32)(g_screen_height >> 1);
    *screen_y = pixel_y;
    *screen_y = pixel_y / (f32)g_screen_height;
}
