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

extern struct Gl { s32 w0; s32 w1; s32 w2; } D_0018A160;
extern s32 ref_L17_003C5B68_00 __attribute__((sda));

/* Tells whether a ride platform can start moving now. Returns 1 for a class 0x920 platform, or
   for a class 0x929 platform that is empty, stopped and whose trigger is finished. Returns 0
   otherwise. */
s32 ride_platform_can_start(void *moby) {
    void *vars;
    void *carried;
    s32 classId;
    s32 carriedClass;
    s32 triggerIndex;
    s32 triggerState;
    void *trigger;

    if (D_0018A160.w0 == 0) {
        return 0;
    }
    classId = (*(s16 *)((char *)(moby) + (0xAA)));
    if (classId == 0x920) {
success:
        return 1;
    }
    if (classId != 0x929) {
        goto fail;
    }
    vars = (*(void **)((char *)(moby) + (0x68)));
    carried = (*(void **)((char *)(vars) + (0x9C)));
    if (carried != NULL) {
        carriedClass = (*(u16 *)((char *)(carried) + (0xAA)));
        if ((u32) (carriedClass - 0x920) < 2U) {
            goto fail;
        }
        if ((s16) carriedClass == classId) {
            goto fail;
        }
    }
    if ((*(f32 *)((char *)(vars) + (0x98))) != 0.0f) {
        goto fail;
    }
    triggerIndex = (*(s32 *)((char *)(vars) + (0xA0)));
    if (triggerIndex == -1) {
        goto success;
    }
    trigger = (void *) (ref_L17_003C5B68_00 + (triggerIndex << 8));
    if (trigger == NULL) {
        goto success;
    }
    triggerState = (*(u8 *)((char *)(trigger) + (0x20)));
    if (triggerState == 0xFE) {
        goto success;
    }
    if (triggerState == 0xFD) {
        goto success;
    }
fail:
    return 0;
}
