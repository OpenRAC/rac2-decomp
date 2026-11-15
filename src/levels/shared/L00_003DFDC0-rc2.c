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

s32 ref_L00_003DFDC0_00(s32, s32);
f32 ref_L00_003DFDC0_01(void);
void ref_L00_003DFDC0_02(void *, s32, f32, s32, f32, s32, s32, f32);

/* Throws out two bursts of particles from the object, sized by its scale and a stored value. */
void part_spawn_bursts_at_moby(void *moby) {
    f32 size_a;
    f32 size_b;
    f32 size_c;
    f32 size_d;
    s32 random_a;
    s32 random_b;
    s32 random_c;
    s32 random_d;
    u8 state;
    void *position;
    void *position2;
    void *vars;

    state = (*(u8 *)((char *)(moby) + (0x20)));
    vars = (*(void **)((char *)(moby) + (0x68)));
    switch (state) {                               
    case 0:
        position = moby + 0x10;
        size_a = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 45.0f);
        random_a = ref_L00_003DFDC0_00(0x5F, 0x6F);
        ref_L00_003DFDC0_02(position, 0x103080, size_a, random_a, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        size_b = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 22.5f);
        random_b = ref_L00_003DFDC0_00(0x6F, 0x7F);
        ref_L00_003DFDC0_02(position, 4144959, size_b, random_b, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        return;
    case 1:
        position2 = moby + 0x10;
        size_c = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 45.0f);
        random_c = ref_L00_003DFDC0_00(0x5F, 0x6F);
        ref_L00_003DFDC0_02(position2, 0x103080, size_c, random_c, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        size_d = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 22.5f);
        random_d = ref_L00_003DFDC0_00(0x6F, 0x7F);
        ref_L00_003DFDC0_02(position2, 4144959, size_d, random_d, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        return;
    }
}
