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

extern s8 *ref_L14_00425C08_00(s32);
extern void ref_L14_00425C08_01(s8 *, s8 *, s32, s32);

/* Returns the helper moby linked to this one, creating a new one (class 4418) if it is missing or dead. */
s8 *func_L14_00425C08(s8 *self) {
    s8 *vars;
    s8 *existing;
    s8 *created;
    u8 state;

    vars = (*(s8 **)((s8 *)(self) + (0x68)));
    existing = (*(s8 **)((s8 *)(vars) + (0x120)));
    if (existing == 0) {
        goto create;
    }
    state = (*(u8 *)((s8 *)(existing) + (0x20)));
    if (state == 0xFE) {
        goto create;
    }
    if (state != 0xFD) {
        return existing;
    }
create:
    created = ref_L14_00425C08_00(0x1142 /* moby class 4418 */);
    (*(s8 **)((s8 *)(vars) + (0x120))) = created;
    if (created != 0) {
        (*(u16 *)((s8 *)(created) + (0x32))) = (*(u16 *)((s8 *)(self) + (0x32)));
        (*(u8 *)((s8 *)((*(s8 **)((s8 *)(vars) + (0x120)))) + (0x30))) = (*(u8 *)((s8 *)(self) + (0x30)));
        (*(s64 *)((s8 *)((*(s8 **)((s8 *)(vars) + (0x120)))) + (0x38))) = (*(s64 *)((s8 *)(self) + (0x38)));
        (*(s8 *)((s8 *)((*(s8 **)((s8 *)(vars) + (0x120)))) + (0x31))) = 1;
        ref_L14_00425C08_01(self, (*(s8 **)((s8 *)(vars) + (0x120))), 2, 0);
    }
    return (*(s8 **)((s8 *)(vars) + (0x120)));
}
