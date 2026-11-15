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

struct Obj27 {
    s32 f0;
    s8 pad4[0x34];
    s16 f38;
    s16 pad3A;
    s32 f3C;
};

extern struct Obj27 ref_L00_002F46C8_00;
extern void ref_L00_002F46C8_01(void *arg0);

/* Starts a timed object the first time it is called: sets a 60 frame timer and a default mode of 8 if none was set. */
void level_start_timed_object_once(void) {
    struct Obj27 *p  = &ref_L00_002F46C8_00;

    if (p->f38 == 0) {
        p->f38 = 1;
        p->f3C = 0x3C;
        ref_L00_002F46C8_01(p);
        if (ref_L00_002F46C8_00.f0 == 0) {
            ref_L00_002F46C8_00.f0 = 8;
        }
    }
}
