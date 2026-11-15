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
void linked_effect_group_update(void *moby) {
    void *moby_copy  = moby;
    s32 *id_list  = (*(s32 **)((s8 *)(moby) + (0x68)));
    s32 state_or_base  = (*(u8 *)((s8 *)(moby) + (0x20)));
    s32 remaining ;
    s32 none_id ;
    s32 entry_addr ;
    f32 value_a ;
    f32 value_b ;
    f32 product ;
    s32 entry_id;

    switch (state_or_base) {
    case 0:
        none_id = -1;
        remaining = 0xF;
        do {
            entry_id = *id_list;
            if (entry_id != none_id) {
                value_a = ref_L03_00384340_00(g_001B2B0C + (entry_id << 7));
                value_b = ref_L03_00384340_00(ref_L03_00384340_05 + (*id_list << 7) + 0x10);
                entry_addr = *id_list;
                product = value_a * value_b;
                state_or_base = ref_L03_00384340_05;
                value_b = (value_b < value_a) ? value_a : value_b;
                entry_addr <<= 7;
                entry_addr += state_or_base;
                (*(f32 *)((s8 *)(entry_addr) + (0x7C))) = product;
                entry_addr = *id_list;
                entry_addr <<= 7;
                entry_addr += state_or_base;
                (*(f32 *)((s8 *)(entry_addr) + (0x3C))) = value_b;
                ref_L03_00384340_01(moby_copy, 2, -1);
            }
            remaining -= 1;
            id_list += 1;
        } while (remaining >= 0);
        break;
    case 1:

        ref_L03_00384340_03(moby_copy);
        if ((ref_L03_00384340_04 & 0xF) == (((s32)moby_copy >> 8) & 0xF)) {
            if (ref_L03_00384340_02(ref_L03_00384340_06, (*(s32 *)((s8 *)(id_list) + (0x44)))) == 0) {
                ref_L03_00384340_01(moby_copy, 2, -1);
            }
        }
        break;
    case 2:
        if (((g_001B2548 & 0xF) == (((s32)moby_copy >> 8) & 0xF)) &&
            (ref_L03_00384340_02(ref_L03_00384340_06, (*(s32 *)((s8 *)(id_list) + (0x44)))) != 0)) {
            ref_L03_00384340_01(moby_copy, 1, -1);
        }
        break;
    }
}
