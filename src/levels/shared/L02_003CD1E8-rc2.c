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

typedef int TI __attribute__((mode(TI)));

extern f32 ref_L02_003CD1E8_00(f32);
extern f32 ref_L02_003CD1E8_01(f32);
extern void ref_L02_003CD1E8_02(void *, void *, void *);
extern f32 ref_L02_003CD1E8_03(f32, f32);
extern f32 ref_L02_003CD1E8_04(void);
extern s32 ref_L02_003CD1E8_05(void *, void *, void *, s32, f32);

/* Picks a random sideways direction and speed, then turns it to match the object facing and stores it as a velocity. */
void moby_set_random_spread_velocity(void *moby, void *outVelocity) {
    f32 angle;
    f32 velY;
    f32 speed;
    void *vars;
    TI homeCopy;
    TI homeRaw ;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    speed = ref_L02_003CD1E8_03(2.0f, 5.0f);
    angle = ref_L02_003CD1E8_04();
    (*(f32 *)((s8 *)(outVelocity) + (0))) = ref_L02_003CD1E8_00(angle) * speed;
    velY = ref_L02_003CD1E8_01(angle) * speed;
    (*(s32 *)((s8 *)(outVelocity) + (8))) = 0;
    (*(f32 *)((s8 *)(outVelocity) + (4))) = velY;
    ref_L02_003CD1E8_02(outVelocity, outVelocity, vars + 0x340);
    homeRaw = *(volatile TI *)((char *)vars + 0x340);
    homeCopy = homeRaw;
    ref_L02_003CD1E8_05(&homeCopy, outVelocity, outVelocity, (*(s32 *)((s8 *)(vars) + (0x318))), (*(f32 *)((s8 *)(vars) + (0x100))));
}
