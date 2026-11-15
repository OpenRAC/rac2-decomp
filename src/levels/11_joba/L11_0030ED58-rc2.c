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
extern s8 ref_L11_0030ED58_00[];
extern s32 ref_L11_0030ED58_01 __attribute__((sda));
extern void ref_L11_0030ED58_02(s32 *, s32, s32, s32, s32);

/* When the game is in state 11 and the level is in mode 2, picks one of three cues from a
   progress counter and starts it. */
void level_start_progress_cue(void) {
    s8 *levelState;
    s32 cueId;
    s32 progress ;
    s32 limit ;

    if (g_current_map_index == 11) {
        levelState = ref_L11_0030ED58_00;
        if ((*(s32 *)((s8 *)(levelState) + (0x30))) == 2) {
            progress = (*(s32 *)((s8 *)(levelState) + (0x34)));
            cueId = -1;
            if ((u32)(progress - 0x1B9) < 0xB3U) {
                cueId = 0x46;
            } else if ((u32)(progress - 0x321) < 0x95U) {
                cueId = 0x47;
            } else {
                limit = 0x44B;
                if (!(limit < progress)) {
                    cueId = 0x48;
                }
            }
            if (cueId != -1) {
                ref_L11_0030ED58_02(&ref_L11_0030ED58_01, cueId, 2, 0x80808080, 0);
            }
        }
    }
}
