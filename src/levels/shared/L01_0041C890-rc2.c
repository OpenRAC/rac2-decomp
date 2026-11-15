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

extern f32 g_001B1B24 __attribute__((sda));
extern void ref_L01_0041C890_00(void *, void *, void *);
extern f32 ref_L01_0041C890_01(f32, f32);
extern void ref_L01_0041C890_02(void *);

/* Moves a falling piece with gravity and spin, and finishes it when its countdown reaches zero. */
void falling_l01_debris_update(s8 *moby) {
    s8 *vars;
    s8 *position_ptr;
    s8 *rotation_ptr;
    s32 countdown;

    position_ptr = moby + 0x10;
    vars = *(s8 **)(moby + 0x68);
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(s8 **)(moby + 0x24) + 0x24) * g_001B1B24;
    *(f32 *)(vars + 0x8) = *(f32 *)(vars + 0x8) - 0.0041666668839752674103f;
    ref_L01_0041C890_00(position_ptr, position_ptr, vars);
    rotation_ptr = moby + 0xF0;
    ref_L01_0041C890_00(rotation_ptr, rotation_ptr, vars + 0x10);
    *(f32 *)(moby + 0xF0) = ref_L01_0041C890_01(*(f32 *)(moby + 0xF0), *(f32 *)(vars + 0x10));
    *(f32 *)(moby + 0xF4) = ref_L01_0041C890_01(*(f32 *)(moby + 0xF4), *(f32 *)(vars + 0x14));
    *(f32 *)(moby + 0xF8) = ref_L01_0041C890_01(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x18));
    countdown = *(u8 *)(moby + 0xBC) - 1;
    *(u8 *)(moby + 0xBC) = countdown;
    if ((countdown & 0xFF) == 0) {
        ref_L01_0041C890_02(moby);
    }
}
