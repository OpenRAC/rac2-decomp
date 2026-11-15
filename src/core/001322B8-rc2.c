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

extern void kernel_process_request_b();
extern s32 *D_001A7480 __attribute__((sda));
extern s32 D_001A7484 __attribute__((sda));

/* Sets up a reply buffer for the next sound request and flushes it from the cache. */
void snd_prepare_reply_buffer(s32 *buffer, s32 count) {
    s8 *base;
    s32 byte_offset;
    s32 end_addr;

    D_001A7484 = count;
    base = (s8 *)(buffer);
    byte_offset = count * 4;
    end_addr = byte_offset + base;
    D_001A7480 = base;
    (*(s32 *)((s8 *)(&((s32 *)base)[count]) + (4))) = 0;
    *(s32 *)base = 0;
    kernel_process_request_b(buffer, base + 3);
    byte_offset += 4;
    base += byte_offset;
    kernel_process_request_b(base, base + 3);
}
