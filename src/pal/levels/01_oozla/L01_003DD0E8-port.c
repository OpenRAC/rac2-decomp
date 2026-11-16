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
#ifndef NULL
#define NULL 0
#endif

extern void *part_find_owned_effect_slot(void *, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern s32 ref_L01_003D9830_02 __attribute__((sda));

/* Sinks the platform when it is hit by an effect from a hit-class object, as long as its attached moby is idle (PAL: 50 Hz timer). */
void platform_sink_when_hit_pal(void *moby) {
    s16 hit_class;
    u8 attached_state;
    void *vars;
    void *effect_slot;
    void *hit_moby;
    void *attached;

    vars = (*(void **)((s8 *)(moby) + (0x68)));
    effect_slot = part_find_owned_effect_slot(moby, 1, 0);
    if ((effect_slot != NULL) && (hit_moby = (*(void **)((s8 *)(effect_slot) + (0x20))), (hit_moby != NULL))) {
        hit_class = (*(s16 *)((s8 *)(hit_moby) + (0xAA)));
        if ((hit_class == 0xB24) || (hit_class == 0xA54)) {
            attached = (*(void **)((s8 *)(vars) + (0xC8)));
            if (attached != NULL) {
                attached_state = (*(u8 *)((s8 *)(attached) + (0x20)));
                if ((attached_state != 1) && (attached_state != 4) && (attached_state != 5)) {
                    (*(s32 *)((s8 *)(vars) + (0xC4))) = (((s32)(ref_L01_003D9830_02) * 5 + 2) / 6);
                    moby_set_state(moby, 2, -1);
                }
            }
        }
    }
    (*(u8 *)((s8 *)(moby) + (0xA8))) = 0xFF;
}