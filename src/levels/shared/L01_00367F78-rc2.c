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

extern s32 g_current_map_index;
extern s32 ref_L01_00367F78_00 __attribute__((sda));
extern u8 D_001395B8[];

/* Sets a bit in the saved data for each slot from 1 to 4 that matches the current level. */
void save_mark_matching_level_slots(void) {
    u8 *saveData;
    s32 levelId;
    s32 *slotIds;
    u32 slotIndex;
    u32 one;

    saveData = D_001395B8;
    levelId = g_current_map_index;
    slotIndex = 1;
    one = 1;
    slotIds = &ref_L01_00367F78_00;
    for (; (s32) slotIndex < 5; slotIndex++) {
        if (levelId == *slotIds) {
            if (slotIndex < 8U) {
                saveData[0x8D] = (u8) (saveData[0x8D] | (one << slotIndex));
            }
        }
        slotIds += 1;
    }
}
