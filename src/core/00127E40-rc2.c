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
#ifndef NULL
#define NULL 0
#endif

extern s32 strncpy(void *dst, s8 *src, s32 n);
extern void SignalSema(s32 h);
extern s32 PollSema(s32 h);
extern void sif_process_cmd_queue_b(s32 a, s32 b);
extern s32 sceSifCallRpc(void *a, s32 b, s32 c, void *d, s32 e, void *f, s32 g, s32 h, s32 i);

extern s32 D_00137E6C;
extern s32 D_00137E68;
extern s8 D_00141B00[];
extern s8 D_00141BB0[];
extern s8 D_001430C0[];

/* Changes the information stored with a file on a memory card. */
s32 sceMcSetFileInfo(s32 port, s32 slot, s8 *fname, s32 flags, s32 blockCount, s32 bufferAddr) {
    s8 *client;
    s8 *request;
    s32 result;

    client = D_00141B00;
    if (*(s32 *)(client + 0x24) == 0) {
        return -0x64;
    }
    if (PollSema(D_00137E6C) < 0) {
        return -0xC8;
    }
    if (fname == NULL || *fname == 0) {
        SignalSema(D_00137E6C);
        return -0xD2;
    }
    *(s32 *)D_00141BB0 = port;
    request = D_00141BB0;
    *(s32 *)(request + 4) = slot;
    *(s32 *)(request + 8) = flags;
    *(s32 *)(request + 0xC) = blockCount;
    *(s32 *)(request + 0x10) = bufferAddr;
    strncpy(request + 0x14, fname, 0x3FF);
    request[0x413] = 0;
    if (blockCount >= 0) {
        sif_process_cmd_queue_b(bufferAddr, blockCount << 6);
    }
    result = sceSifCallRpc(client, 13, 1, request, 0x414, D_001430C0, 4, 0, 0);
    if (result == 0) {
        D_00137E68 = 13;
    } else {
        SignalSema(D_00137E6C);
    }
    return result;
}
