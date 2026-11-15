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
#ifndef NULL
#define NULL 0
#endif

extern void *ref_L01_003D9830_00(void *, s32, s32);
extern void ref_L01_003D9830_01(void *, s32, s32);
extern s32 ref_L01_003D9830_02 __attribute__((sda));

/* Checks whether a swamp monster has touched the platform, and if so starts the platform sinking. */
void func_L01_003D9830(void *moby) {
    s16 classId;
    u8 attachedState;
    void *vars;
    void *hitSource;
    void *hitClassData;
    void *attached;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    hitSource = ref_L01_003D9830_00(moby, 1, 0);
    if ((hitSource != NULL) && (hitClassData = (*(void **)((s8 *)(hitSource) + (0x20))), (hitClassData != NULL))) {
        classId = (*(s16 *)((s8 *)(hitClassData) + (0xAA)));
        if ((classId == 0xB24 /* moby class 2852 */) || (classId == 0xA54 /* Swamp Monster II */)) {
            attached = (*(void **)((s8 *)(vars) + (0xC8)));
            if (attached != NULL) {
                attachedState = (*(u8 *)((s8 *)(attached) + (0x20)));
                if ((attachedState != 1) && (attachedState != 4) && (attachedState != 5)) {
                    (*(s32 *)((s8 *)(vars) + (0xC4))) = ref_L01_003D9830_02;
                    ref_L01_003D9830_01(moby, 2, -1);
                }
            }
        }
    }
    (*(u8 *)((s8 *)(moby) + (0xA8))) = 0xFF;
}
