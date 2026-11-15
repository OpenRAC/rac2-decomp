#include "names.h"

/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

extern f32 IntToFloat(s32);
extern s8 g_active_camera[];

/* Sets a camera value: snaps it to the target, or eases to it over a number of frames. */
void cam_set_value_target(s32 frames, s32 mode, f32 target, f32 extra1, f32 extra2, f32 extra3) {
    f32 step_per_frame;

    switch (mode) {
    case 0: {
        s8 *camera = g_active_camera;
        (*(s8 *)((char *)(camera) + (0x3E9))) = 1;
        (*(f32 *)((char *)(camera) + (0x3D4))) = target;
        (*(s8 *)((char *)(camera) + (0x3E8))) = 0;
        return;
    }
    case 1:
    case 2:
        if (frames == 0) {
            s8 *camera = g_active_camera;
            (*(f32 *)((char *)(camera) + (0x3D4))) = target;
            (*(s8 *)((char *)(camera) + (0x3E8))) = 0;
        } else {
            s8 *camera = g_active_camera;
            (*(s16 *)((char *)(camera) + (0x3EA))) = frames;
            step_per_frame = 1.0f / IntToFloat(frames);
            (*(s8 *)((char *)(camera) + (0x3E8))) = mode;
            (*(f32 *)((char *)(camera) + (0x3F0))) = (*(f32 *)((char *)(camera) + (0x3D8)));
            (*(f32 *)((char *)(camera) + (0x3EC))) = step_per_frame;
        }
        {
            s8 *camera = g_active_camera;
            (*(s8 *)((char *)(camera) + (0x3E9))) = 1;
        }
        break;
    case 3: {
        s8 *camera = g_active_camera;
        (*(s8 *)((char *)(camera) + (0x3E8))) = mode;
        (*(f32 *)((char *)(camera) + (0x3D4))) = target;
        (*(s8 *)((char *)(camera) + (0x3E9))) = 1;
        (*(f32 *)((char *)(camera) + (0x3DC))) = extra1;
        (*(f32 *)((char *)(camera) + (0x3E0))) = extra2;
        (*(f32 *)((char *)(camera) + (0x3E4))) = extra3;
        break;
    }
    }
}
