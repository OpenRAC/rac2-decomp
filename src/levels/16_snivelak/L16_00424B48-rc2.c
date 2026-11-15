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

extern void ref_L16_00424B48_00(s32, s32, s8 *, s32);

/* After being triggered, slowly sinks the object for a short time and then stops. */
void sinking_l16_platform_update(s8 *moby) {
    s32 frame;
    s32 frameLow;
    s32 stillRunning;
    f32 newHeight;

    if ((*(u8 *)((char *)(moby) + (0x20))) == 0) {
        if ((*(u8 *)((char *)(moby) + (0xBC))) != 0) {
            (*(u8 *)((char *)(moby) + (0x20))) = 1;
            ref_L16_00424B48_00(0, 0, moby, 0xE71);
        }
        (*(s16 *)((char *)(moby) + (0x32))) = 0x80;
    }
    if ((*(u8 *)((char *)(moby) + (0x20))) == 1) {
        newHeight = (*(f32 *)((char *)(moby) + (0x18))) - 0.13333334028720855712890625f;
        frame = (*(u16 *)((char *)(moby) + (0x96))) + 1;
        frameLow = frame & 0xFFFF;
        (*(u16 *)((char *)(moby) + (0x96))) = frame;
        stillRunning = (u32) frameLow < 0x3CU;
        (*(f32 *)((char *)(moby) + (0x18))) = newHeight;
        if (stillRunning == 0) {
            (*(u8 *)((char *)(moby) + (0x20))) = 2;
        }
    }
}
