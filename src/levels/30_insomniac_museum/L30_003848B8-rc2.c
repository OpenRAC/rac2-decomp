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

extern s32 ref_L30_003848B8_00 __attribute__((sda));
extern s32 ref_L30_003848B8_01[];
extern s8 g_music_state[];

/* Picks the next time value for the chosen entry and stores it in the game state; returns 1 if it did, 0 if not. */
s32 museum_schedule_next_exhibit_entry(void *moby) {
    s8 *vars;
    s8 *game_state;
    s8 *state;
    s32 kind;
    s32 slot;
    s32 pending;
    s32 value;
    s32 first_offset;
    s32 second_offset;

    game_state = g_music_state;
    vars = *(s8 **)((s8 *)moby + 0x68);
    slot = *(s32 *)(vars + 0x144);
    kind = ref_L30_003848B8_01[slot];
    if (*(s32 *)(game_state + 0x68) == 0) {
        pending = *(s32 *)(game_state + 0x24);
        if ((pending == -1) && (slot != pending)) {
            if (kind != 6) {
                if ((((s32) ref_L30_003848B8_00 >> kind) ^ 1) & 1) {
                    first_offset = kind * 4;
                    value = *(s32 *)(vars + first_offset + 0xE0);
                    ref_L30_003848B8_00 |= 1 << kind;
                } else {
                    first_offset = kind * 4;
                    second_offset = kind * 4;
                    value = *(s32 *)(vars + second_offset + 0x10C);
                }
            } else if (slot == 1) {
                value = *(s32 *)(vars + 0xF8);
            } else {
                value = *(s32 *)(vars + 0x124);
            }
            state = g_music_state;
            *(s32 *)(state + 0x24) = (value & 0x3FFF) + 0xBB8;
            *(s32 *)(state + 0x28) = 0;
            return 1;
        }
    }
    return 0;
}
