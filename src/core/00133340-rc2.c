#include "names.h"

/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
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

extern void snd_queue_command(s32 a0, s32 a1, void *a2, s32 a3, s64 t0);

/* Packs eight sound values and sends command 0x2C with a reply callback. */
void snd_send_cmd2c_packed(s32 p0, s32 p1, s32 lo0, s32 lo1, s32 hi0, s32 hi1, s32 p4, s32 p5, s32 p6, s32 p7, s32 callback, s64 callback_data) {
    s32 payload[8];
    s32 packed02;
    s32 packed13;

    packed13 = ((u32)hi1 << 16) | (lo1 & 0xFFFF);
    packed02 = ((u32)hi0 << 16) | (lo0 & 0xFFFF);
    payload[0] = p0;
    payload[1] = p1;
    payload[2] = packed02;
    payload[3] = packed13;
    payload[4] = p4;
    payload[5] = p5;
    payload[6] = p6;
    payload[7] = p7;
    snd_queue_command(0x2C, 0x20, payload, callback, callback_data);
}
