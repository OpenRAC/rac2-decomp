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

extern s32 ref_L16_0041EBE8_00(s8 *);
extern void ref_L16_0041EBE8_01(s8 *, s32, s32);
extern f32 ref_L16_0041EBE8_02(f32);
extern void ref_L16_0041EBE8_03(s8 *, f32);
extern f32 ref_L16_0041EBE8_04 __attribute__((sda));
extern f32 ref_L16_0041EBE8_05 __attribute__((sda));
extern f32 ref_L16_0041EBE8_06 __attribute__((sda));
extern f32 ref_L16_0041EBE8_07 __attribute__((sda));
extern f32 ref_L16_0041EBE8_08;
extern f32 g_001B3AAC __attribute__((sda));

/* Swings an object to a set angle with a bounce, then stops once it has settled. */
void swing_to_angle_update(s8 *moby) {
    f32 angle;
    f32 finalSpeed;
    f32 targetAngle;
    f32 newSpeed;
    u8 state;

    state = *(u8 *)(moby + 0x20);
    switch (state) {
    case 0:
        if (ref_L16_0041EBE8_00(moby) != 0) {
            ref_L16_0041EBE8_04 = 0.0f;
            ref_L16_0041EBE8_08 = 0.0f;
            ref_L16_0041EBE8_01(moby, 1, -1);
        }
        break;
    case 1:
        newSpeed = ref_L16_0041EBE8_08 + (ref_L16_0041EBE8_06 * 0.00000484813745060819201171398162841796875f);
        targetAngle = ref_L16_0041EBE8_05 * 0.0174532942473888397216796875f;
        angle = ref_L16_0041EBE8_04 + newSpeed;
        ref_L16_0041EBE8_08 = newSpeed;
        ref_L16_0041EBE8_04 = angle;
        if (targetAngle <= angle) {
            ref_L16_0041EBE8_04 = targetAngle;
            finalSpeed = newSpeed * ref_L16_0041EBE8_07;
            g_001B3AAC = finalSpeed;
            if (ref_L16_0041EBE8_02(finalSpeed) < 0.000290888245217502117156982421875f) {
                ref_L16_0041EBE8_01(moby, 2, -1);
            }
        }
        ref_L16_0041EBE8_03(moby, ref_L16_0041EBE8_04);
        break;
    }
}
