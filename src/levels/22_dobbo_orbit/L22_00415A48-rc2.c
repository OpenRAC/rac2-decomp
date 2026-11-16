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

extern s32 ref_L22_00415A48_00(s32 *a, void *b);
extern s32 ref_L22_00415A48_01(s32 a, s32 b);
extern struct { s32 w0; s32 w1; s32 w2; } g_timer_hud_words;

/* Sets up a timer on first run, then resets it to 0x708 (1800 frames) and calls a helper when a condition is met. */
void timer_trigger_update(void *moby) {
    s32 *vars;
    void *hud_state;

    vars = (*(s32 **)((s8 *)(moby) + (0x68)));
    if ((*(u8 *)((s8 *)(moby) + (0x20))) == 0) {
        (*(u8 *)((s8 *)(moby) + (0x20))) = 1U;
        (*(u8 *)((s8 *)(moby) + (0x30))) = 0xFF;
        *vars = 0x708;
    }
    if ((*(u8 *)((s8 *)(moby) + (0x20))) == 1) {
        hud_state = (void *) g_timer_hud_words.w0;
        if ((ref_L22_00415A48_00(vars, moby) != 0) && ((*(s32 *)((s8 *)(hud_state) + (8))) == 0)) {
            if ((*(s32 *)((s8 *)(hud_state) + (0xC))) == 0) {
                ref_L22_00415A48_01(0x9FD, 0x54);
                *vars = 0x708;
            }
        }
    }
}
