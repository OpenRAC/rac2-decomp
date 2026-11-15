
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

typedef struct { f32 x, y, z; } V3;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s8 b00[0x10]; V3 v10; s32 p1c; V4 v20; V4 v30; } Fr;

extern f32 ref_L11_0043A810_00 __attribute__((sda));
extern f32 ref_L11_0043A810_01 __attribute__((sda));
extern f32 ref_L11_0043A810_02 __attribute__((sda));
extern f32 ref_L11_0043A810_03 __attribute__((sda));
extern f32 ref_L11_0043A810_04 __attribute__((sda));
extern void ref_L11_0043A810_05(void *);
extern void ref_L11_0043A810_06(f32 *, s32, void *);
extern f32 ref_L11_0043A810_07(s32, void *);
extern f32 ref_L11_0043A810_08(f32, f32);
extern void ref_L11_0043A810_09(void *, void *, void *, f32);
extern f32 ref_L11_0043A810_10(f32, f32);
extern f32 ref_L11_0043A810_11(f32);
extern void ref_L11_0043A810_12(void *, s32, void *);
extern void ref_L11_0043A810_13(void *, void *);
extern void ref_L11_0043A810_14(s32, void *, f32);

/* Turns the drone's head to aim at the hero, with a small left-right sway while it fires. */
void func_L11_0043A810(void *moby) {
    Fr fr;
    s8 *vars;
    s8 *aimTarget;
    f32 distance;
    f32 pitch, headingToHero, turnedHeading, smoothedHeading, swayStep, newSway, swayLimit, sway;
    s16 swayDirection;

    vars = *(s8 **)((s8 *)moby + 0x68);
    ref_L11_0043A810_12(moby, 3, fr.b00);
    aimTarget = vars + 0x50;
    ref_L11_0043A810_06(&fr.v10.x, (s32)aimTarget, fr.b00);
    distance = ref_L11_0043A810_07((s32)aimTarget, fr.b00);
    ref_L11_0043A810_05(&fr.v20);
    pitch = ref_L11_0043A810_08(fr.v10.z, distance) + -1.5707964f + ref_L11_0043A810_04;
    fr.v20.y = pitch;
    if (ref_L11_0043A810_01 < pitch) {
        fr.v20.y = ref_L11_0043A810_01;
    } else if (pitch < ref_L11_0043A810_02) {
        fr.v20.y = ref_L11_0043A810_02;
    }
    ref_L11_0043A810_13(&fr.v30, &fr.v20);
    ref_L11_0043A810_14((s32)(vars + 0x270), &fr.v30, ref_L11_0043A810_03);
    ref_L11_0043A810_05(&fr.v20);
    headingToHero = ref_L11_0043A810_08(fr.v10.x, fr.v10.y);
    fr.v20.z = headingToHero;
    turnedHeading = ref_L11_0043A810_10(headingToHero, *(f32 *)(moby + 0xF8));
    fr.v20.z = turnedHeading;
    smoothedHeading = ref_L11_0043A810_11(turnedHeading);
    fr.v20.z = smoothedHeading;
    fr.v20.z = smoothedHeading + *(f32 *)(vars + 0x2DC);
    swayStep = *(f32 *)(vars + 0x2E0) * 0.00029088825f;
    swayDirection = *(s16 *)(vars + 0x2EE);
    sway = *(f32 *)(vars + 0x2DC);
    if (swayDirection == 0) {
        newSway = sway - swayStep;
    } else {
        newSway = sway + swayStep;
    }
    swayLimit = ref_L11_0043A810_00;
    *(f32 *)(vars + 0x2DC) = newSway;
    if ((swayLimit < newSway) || (swayLimit = -swayLimit, (newSway < swayLimit))) {
        *(f32 *)(vars + 0x2DC) = swayLimit;
        *(s16 *)(vars + 0x2EE) = (s16)((u16)*(s16 *)(vars + 0x2EE) ^ 1);
    }
    ref_L11_0043A810_13(&fr.v30, &fr.v20);
    ref_L11_0043A810_09(vars + 0x230, vars + 0x230, &fr.v30, 0.0625f);
}
