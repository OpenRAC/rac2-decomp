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

extern f32 ref_L03_00384340_00(s32);
extern void ref_L03_00384340_01(void *, s32, s32);
extern s32 ref_L03_00384340_02(void *, s32);
extern void ref_L03_00384340_03(void *);
extern s32 ref_L03_00384340_04;
extern s32 g_001B2548 __attribute__((sda));
extern s32 ref_L03_00384340_05;
extern s32 g_001B2B0C __attribute__((sda));
extern s8 ref_L03_00384340_06[];


/* Updates a group of linked effect objects. At start it fills in each entry from two values, then it switches between two states depending on a timed check. */
void func_L03_00384340(void *moby) {
    void *mobyCopy  = moby;
    s32 *idList  = (*(s32 **)((s8 *)(moby) + (0x68)));
    s32 stateOrBase  = (*(u8 *)((s8 *)(moby) + (0x20)));
    s32 remaining ;
    s32 noneId ;
    s32 entryAddr ;
    f32 valueA ;
    f32 valueB ;
    f32 product ;
    s32 entryId;

    switch (stateOrBase) {
    case 0:
        noneId = -1;
        remaining = 0xF;
        do {
            entryId = *idList;
            if (entryId != noneId) {
                valueA = ref_L03_00384340_00(g_001B2B0C + (entryId << 7));
                valueB = ref_L03_00384340_00(ref_L03_00384340_05 + (*idList << 7) + 0x10);
                entryAddr = *idList;
                product = valueA * valueB;
                stateOrBase = ref_L03_00384340_05;
                valueB = (valueB < valueA) ? valueA : valueB;
                entryAddr <<= 7;
                entryAddr += stateOrBase;
                (*(f32 *)((s8 *)(entryAddr) + (0x7C))) = product;
                entryAddr = *idList;
                entryAddr <<= 7;
                entryAddr += stateOrBase;
                (*(f32 *)((s8 *)(entryAddr) + (0x3C))) = valueB;
                ref_L03_00384340_01(mobyCopy, 2, -1);
            }
            remaining -= 1;
            idList += 1;
        } while (remaining >= 0);
        break;
    case 1:

        ref_L03_00384340_03(mobyCopy);
        if ((ref_L03_00384340_04 & 0xF) == (((s32)mobyCopy >> 8) & 0xF)) {
            if (ref_L03_00384340_02(ref_L03_00384340_06, (*(s32 *)((s8 *)(idList) + (0x44)))) == 0) {
                ref_L03_00384340_01(mobyCopy, 2, -1);
            }
        }
        break;
    case 2:
        if (((g_001B2548 & 0xF) == (((s32)mobyCopy >> 8) & 0xF)) &&
            (ref_L03_00384340_02(ref_L03_00384340_06, (*(s32 *)((s8 *)(idList) + (0x44)))) != 0)) {
            ref_L03_00384340_01(mobyCopy, 1, -1);
        }
        break;
    }
}
