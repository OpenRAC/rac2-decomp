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

extern s32 CreateMoby();
extern void moby_transform_joint_to_world();
extern void set_moby_color();
extern void func_002A0F48();
extern void anim_start_blended();

typedef int TI __attribute__((mode(TI)));

/* Creates the Swingshot hook at the owner's grip, remembers its owner and follow distance, and returns it. */
s32 swingshot_hook_spawn(s32 owner, f32 follow_distance) {
    s32 hook;
    s32 hook_vars;

    hook = CreateMoby(MOBY_CLASS_SWINGSHOT_HOOK);
    if (hook != 0) {
        hook_vars = (*(s32 *)((s8 *)(hook) + (0x68)));
        (*(f32 *)((s8 *)(hook_vars) + (4))) = follow_distance;
        (*(s32 *)((s8 *)(hook_vars) + (0))) = owner;
        (*(u8 *)((s8 *)(hook) + (0x30))) = 0xFF;
        (*(s16 *)((s8 *)(hook) + (0x32))) = 0xFF;
        (*(s8 *)((s8 *)(hook) + (0x31))) = 1;
        set_moby_color(hook, 0x80, 0x80, 0x80);
        moby_transform_joint_to_world(owner, 0, hook + 0x10);
        (*(TI *)((s8 *)(hook) + (0xC0))) = (*(TI *)((s8 *)(owner) + (0xC0)));
        (*(TI *)((s8 *)(hook) + (0xD0))) = (*(TI *)((s8 *)(owner) + (0xD0)));
        (*(TI *)((s8 *)(hook) + (0xE0))) = (*(TI *)((s8 *)(owner) + (0xE0)));
        if ((*(u8 *)((s8 *)(hook) + (0x43))) != 0) {
            anim_start_blended(hook, 0, 0, 0xA);
        }
        func_002A0F48(hook);
        (*(s8 *)((s8 *)(hook) + (0x20))) = 0;
        (*(u16 *)((s8 *)(hook) + (0x34))) = (*(u16 *)((s8 *)(hook) + (0x34))) | 4;
    }
    return hook;
}
