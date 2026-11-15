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

extern s32 ref_L07_003F8908_00(s32 a0);
extern s32 ref_L07_003F8908_01(s32 a0, s32 a1);
extern void ref_L07_003F8908_02(void *a0, s32 a1, s32 a2);
extern s32 ref_L07_003F8908_03(s32 a0);
extern s32 ref_L07_003F8908_04 __attribute__((sda));
extern s32 ref_L07_003F8908_05 __attribute__((sda));
extern s32 ref_L07_003F8908_06 __attribute__((sda));
extern s32 ref_L07_003F8908_07 __attribute__((sda));
extern s32 ref_L07_003F8908_08 __attribute__((sda));
extern s32 ref_L07_003F8908_09 __attribute__((sda));

/* Picks the enemy's next action from its current phase and a random roll, and sets up the timer and handlers for it. Returns the chosen action number. */
s32 enemy_choose_action(void *moby) {
    s32 one  = 1;
    u8 *vars ;
    s32 action ;
    s32 phase ;
    s32 roll;
    s32 handler_b;
    s32 handler_a;
    s32 range_min;
    s32 range_max;

    vars = *(u8 **)((u8 *)moby + 0x68);
    phase = *(s32 *)(vars + 0x420);
    action = 7;
    if (phase != one) {
        action = 7;
        if (phase < 2) {
            if (phase != 0) {
                goto state_default;
            }
        } else {
            goto state_default;
        }
        goto dispatch;
    }

    one = ref_L07_003F8908_00(0xFF) & 1;
    phase = 6;
    if (one != 0) {
        action = phase;
    }
    goto dispatch;

state_default:
    roll = ref_L07_003F8908_00(*(s32 *)(vars + 0x420) + 1);
    switch (roll) {
    case 0:
        action = 7;
        break;
    case 1:
        action = 6;
        break;
    case 2:
        if (*(s32 *)(vars + 0x458) != 0) {
            action = 8;
            ref_L07_003F8908_02((void *)(vars + 0x458), 0, 1);
        } else {
            {
                    s32 mode  = 2;

                    action = 6;
                    roll = ref_L07_003F8908_00(mode);
                    phase = 7;
                    if (roll != 0) {
                        action = phase;
                    }
                }
        }
        break;
    case 3:
        action = 9;
        break;
    }

dispatch:
switch (action) {
    case 7:
        handler_a = ref_L07_003F8908_05;
        range_min = 3;
        handler_b = ref_L07_003F8908_08;
        range_max = 5;
        goto block_35;
    case 6:
        handler_a = ref_L07_003F8908_04;
        range_min = 2;
        handler_b = ref_L07_003F8908_07;
        range_max = 3;
        goto block_35;
    case 8:
        *(s32 *)(vars + 0x438) = 1;
        *(s32 *)(vars + 0x41C) = ref_L07_003F8908_03(*(s32 *)(vars + 0x180));
        goto block_36;
    case 9:
        handler_a = ref_L07_003F8908_06;
        range_min = 1;
        handler_b = ref_L07_003F8908_09;
        range_max = 3;
        goto block_35;
    default:
        return action;
    }

block_35:
    *(s32 *)(vars + 0x444) = handler_a;
    *(s32 *)(vars + 0x448) = handler_b;
    *(s32 *)(vars + 0x438) = ref_L07_003F8908_01(range_min, range_max);

block_36:
    return action;
}
