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

extern void update_moby_animation_state(s8 *);

/* Starts an animation on an object right away, with no blending. */
void anim_start_immediate(s8 *moby, s32 animation, s32 frame) {
    s32 anim_offset;
    s8 *anim_entry;
    s8 *anim_ptr;
    s8 *anim_data;
    s32 start_frame;
    s32 last_frame;
    s32 next_frame;
    u8 frame_count;
    f32 rate;

    anim_offset = animation * 4;
    anim_entry = (*(s8 **)((s8 *)(moby) + (0x24)));
    anim_entry = anim_entry + 0x48;
    anim_entry = anim_entry + anim_offset;
    frame_count = (*(u8 *)((s8 *)(*(s8 **)anim_entry) + (0x10)));
    (*(s8 *)((s8 *)(moby) + (0x42))) = animation;
    start_frame = (frame < (s32) frame_count) ? frame : (frame_count - 1);
    next_frame = start_frame + 1;
    (*(s8 *)((s8 *)(moby) + (0x40))) = start_frame;
    (*(s8 *)((s8 *)(moby) + (0x41))) = next_frame;
    anim_ptr = *(s8 **)anim_entry;
    last_frame = (*(u8 *)((s8 *)(anim_ptr) + (0x10))) - 1;
    if (last_frame < (s32) (u8) (*(s8 *)((s8 *)(moby) + (0x41)))) {
        (*(s8 *)((s8 *)(moby) + (0x41))) = last_frame;
    }
    (*(s8 *)((s8 *)(moby) + (0x43))) = animation;
    anim_data = *(s8 **)((*(s8 **)((s8 *)(moby) + (0x24))) + anim_offset + 0x48);
    frame_count = (*(u8 *)((s8 *)(anim_data) + (0x10)));
    if ((u8) (*(u8 *)((s8 *)(moby) + (0x41))) >= frame_count) {
        (*(s8 *)((s8 *)(moby) + (0x41))) = 0;
    }
    update_moby_animation_state(moby);
    rate = *(*(f32 **)((s8 *)(moby) + (0x58)));
    (*(f32 *)((s8 *)(moby) + (0x4C))) = rate;
    (*(u8 *)((s8 *)(moby) + (0x60))) = (*(u8 *)((s8 *)(moby) + (0x60))) & 0xFD;
    (*(s8 *)((s8 *)(moby) + (0x6C))) = (*(u8 *)((s8 *)(*(s8 **)((*(s8 **)((s8 *)(moby) + (0x24))) + anim_offset + 0x48)) + (0x11)));
}
