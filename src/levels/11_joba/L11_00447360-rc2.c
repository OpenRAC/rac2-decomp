
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

extern s8 *ref_L11_00447360_00;
extern s8 ref_L11_00447360_01[];

extern void ref_L11_00447360_02(void *, s32, s32, void *, s8 *, f32);
extern void ref_L11_00447360_03(void *);
extern void ref_L11_00447360_04(void *);
extern void ref_L11_00447360_05(void *);
extern void ref_L11_00447360_06(void *);
extern void ref_L11_00447360_07(void *);
extern void ref_L11_00447360_08(void *);
extern void ref_L11_00447360_09(void *);
extern void ref_L11_00447360_10(void *);
extern void ref_L11_00447360_11(void *);
extern void ref_L11_00447360_12(void *);

/* Goes through every game object in the world and calls the special update for its type (decoy, sheep, turrets, robots and so on). */
void func_L11_00447360(s32 param) {
    s8 *moby;
    s16 classId;

    moby = ref_L11_00447360_00;
    if (moby != 0) {
        do {
            classId = *(s16 *)(moby + 0xAA);
            switch (classId) {
            case 0xCB: /* Decoy */
                ref_L11_00447360_02(moby, param, 0x10000, moby + 0x10, ref_L11_00447360_01, 100.0f);
                break;
            case 0xE7D: /* Sheep */
                ref_L11_00447360_11(moby);
                break;
            case 0xEB0: /* Dark Sheep */
                ref_L11_00447360_12(moby);
                break;
            case 0xCB2: /* Synthenoid */
                ref_L11_00447360_06(moby);
                break;
            case 0xB02: /* Kilonoid */
                ref_L11_00447360_05(moby);
                break;
            case 0x1366: /* Miniturret */
                ref_L11_00447360_07(moby);
                break;
            case 0x1367: /* Megaturret */
                ref_L11_00447360_08(moby);
                break;
            case 0x326: /* moby class 806 */
                ref_L11_00447360_03(moby);
                break;
            case 0xA5C: /* Shield Charger */
            case 0x1192: /* Tesla Barrier */
                ref_L11_00447360_04(moby);
                break;
            case 0xE20: /* moby class 3616 */
                ref_L11_00447360_10(moby);
                break;
            case 0xAE0: /* moby class 2784 */
            case 0xAE1:
            case 0xAE2:
            case 0xAEC:
            case 0xB06:
            case 0xB09:
            case 0xCC0 ... 0xCC9:
            case 0xCDB: /* Ammo */
                ref_L11_00447360_09(moby);
                break;
            default:
                break;
            }
            moby = *(s8 **)(moby + 0x28);
        } while (moby != 0);
    }
}
