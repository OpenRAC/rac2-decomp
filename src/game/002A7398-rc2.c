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

extern void func_0029F390(s8 *);

/* Starts an animation on an object right away, with no blending. */
void func_002A7398(s8 *moby, s32 animation, s32 frame) {
    s32 animOffset;
    s8 *animEntry;
    s8 *animPtr;
    s8 *animData;
    s32 startFrame;
    s32 lastFrame;
    s32 nextFrame;
    u8 frameCount;
    f32 rate;

    animOffset = animation * 4;
    animEntry = (*(s8 **)((s8 *)(moby) + (0x24)));
    animEntry = animEntry + 0x48;
    animEntry = animEntry + animOffset;
    frameCount = (*(u8 *)((s8 *)(*(s8 **)animEntry) + (0x10)));
    (*(s8 *)((s8 *)(moby) + (0x42))) = animation;
    startFrame = (frame < (s32) frameCount) ? frame : (frameCount - 1);
    nextFrame = startFrame + 1;
    (*(s8 *)((s8 *)(moby) + (0x40))) = startFrame;
    (*(s8 *)((s8 *)(moby) + (0x41))) = nextFrame;
    animPtr = *(s8 **)animEntry;
    lastFrame = (*(u8 *)((s8 *)(animPtr) + (0x10))) - 1;
    if (lastFrame < (s32) (u8) (*(s8 *)((s8 *)(moby) + (0x41)))) {
        (*(s8 *)((s8 *)(moby) + (0x41))) = lastFrame;
    }
    (*(s8 *)((s8 *)(moby) + (0x43))) = animation;
    animData = *(s8 **)((*(s8 **)((s8 *)(moby) + (0x24))) + animOffset + 0x48);
    frameCount = (*(u8 *)((s8 *)(animData) + (0x10)));
    if ((u8) (*(u8 *)((s8 *)(moby) + (0x41))) >= frameCount) {
        (*(s8 *)((s8 *)(moby) + (0x41))) = 0;
    }
    update_moby_animation_state(moby);
    rate = *(*(f32 **)((s8 *)(moby) + (0x58)));
    (*(f32 *)((s8 *)(moby) + (0x4C))) = rate;
    (*(u8 *)((s8 *)(moby) + (0x60))) = (*(u8 *)((s8 *)(moby) + (0x60))) & 0xFD;
    (*(s8 *)((s8 *)(moby) + (0x6C))) = (*(u8 *)((s8 *)(*(s8 **)((*(s8 **)((s8 *)(moby) + (0x24))) + animOffset + 0x48)) + (0x11)));
}
