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

extern s8 g_hero_position[];
extern s8 ref_L04_00441100_00[];
extern s8 g_barlow_trigger_flag;
extern s32 ref_L04_00441100_01(s8 *, s32);
extern void ref_L04_00441100_02(s8 *);
extern void ref_L04_00441100_03(s8 *, s32, s32);

/* On its first update waits until the hero is at the linked spot, then sets a level flag and moves to the next state. */
void barlow_proximity_trigger_update(s8 *object) {
    s32 *links;
    s32 linked_id;

    if (*(u8 *)(object + 0x20) == 0) {
        links = *(s32 **)(object + 0x68);
        linked_id = *links;
        if (linked_id != -1 && ref_L04_00441100_01(g_hero_position, linked_id) != 0) {
            ref_L04_00441100_02(ref_L04_00441100_00);
            g_barlow_trigger_flag = 1;
            ref_L04_00441100_03(object, 1, -1);
        }
    }
}
