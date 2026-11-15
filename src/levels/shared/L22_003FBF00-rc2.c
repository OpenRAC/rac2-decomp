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

extern s8 ref_L22_003FBF00_00[];
extern f32 ref_L22_003FBF00_01 __attribute__((sda));
extern void ref_L22_003FBF00_02(void *a, s32 b, void *c, f32 d);
extern void ref_L22_003FBF00_03(void *a, void *b, f32 c);
extern void ref_L22_003FBF00_04(void *a, void *b, f32 c);
extern void ref_L22_003FBF00_05(void *a, void *b, void *c);

/* Works out the world position of one of the object's eight particle anchors, scaled while the object is in its first state. */
void part_get_anchor_position(void *obj, void *outPos, s32 index) {
    s32 slot ;
    void *vars ;
    s32 offset[4];
    s32 mid[4];
    s32 scaled[4];
    void *particle;

    slot = index;
    vars = (*(void **)((s8 *)(obj) + (0x68)));
    ref_L22_003FBF00_02(offset, (slot * 0x10) + (s32)ref_L22_003FBF00_00, (s8 *)vars + 0x10, (*(f32 *)((s8 *)(vars) + (0x1C))));
    vars = (s8 *)vars + (slot * 4);
    particle = (*(void **)((s8 *)(vars) + (0x60)));
    if (particle != 0) {
        if ((*(u8 *)((s8 *)(obj) + (0x20))) == 0) {
            ref_L22_003FBF00_03(offset, offset, (*(f32 *)((s8 *)(particle) + (0x28))));
        }
    }
    ref_L22_003FBF00_04(scaled, (s8 *)obj + 0xE0, ref_L22_003FBF00_01);
    ref_L22_003FBF00_05(mid, (s8 *)obj + 0x10, scaled);
    ref_L22_003FBF00_05(outPos, mid, offset);
}
