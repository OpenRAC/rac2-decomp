
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
void func_L00_003DFDC0(void *moby) {
    f32 sizeA;
    f32 sizeB;
    f32 sizeC;
    f32 sizeD;
    s32 randomA;
    s32 randomB;
    s32 randomC;
    s32 randomD;
    u8 state;
    void *position;
    void *position2;
    void *vars;

    state = (*(u8 *)((char *)(moby) + (0x20)));
    vars = (*(void **)((char *)(moby) + (0x68)));
    switch (state) {                               
    case 0:
        position = moby + 0x10;
        sizeA = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 45.0f);
        randomA = ref_L00_003DFDC0_00(0x5F, 0x6F);
        ref_L00_003DFDC0_02(position, 0x103080, sizeA, randomA, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        sizeB = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 22.5f);
        randomB = ref_L00_003DFDC0_00(0x6F, 0x7F);
        ref_L00_003DFDC0_02(position, 4144959, sizeB, randomB, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        return;
    case 1:
        position2 = moby + 0x10;
        sizeC = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 45.0f);
        randomC = ref_L00_003DFDC0_00(0x5F, 0x6F);
        ref_L00_003DFDC0_02(position2, 0x103080, sizeC, randomC, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        sizeD = (*(f32 *)((char *)(moby) + (0x2C))) * ((*(f32 *)((char *)(vars) + (0x20))) * 22.5f);
        randomD = ref_L00_003DFDC0_00(0x6F, 0x7F);
        ref_L00_003DFDC0_02(position2, 4144959, sizeD, randomD, ref_L00_003DFDC0_01(), 0xB, 2, 1.0f);
        return;
    }
}
