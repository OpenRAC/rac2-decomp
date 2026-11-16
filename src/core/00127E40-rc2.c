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

extern char *strncpy(void *dst, s8 *src, s32 n);
extern void SignalSema(s32 h);
extern s32 PollSema(s32 h);
extern void sif_process_cmd_queue_b(s32 a, s32 b);
extern s32 sceSifCallRpc(void *a, s32 b, s32 c, void *d, s32 e, void *f, s32 g, s32 h, s32 i);

extern s32 g_mc_sema;
extern s32 g_mc_result_code;
extern s8 g_mc_rpc_client[];
extern s8 g_mc_set_file_info_request[];
extern s8 g_mc_rpc_result[];

/* Changes the information stored with a file on a memory card. */
s32 sceMcSetFileInfo(s32 port, s32 slot, s8 *fname, s32 flags, s32 block_count, s32 buffer_addr) {
    s8 *client;
    s8 *request;
    s32 result;

    client = g_mc_rpc_client;
    if (*(s32 *)(client + 0x24) == 0) {
        return -0x64;
    }
    if (PollSema(g_mc_sema) < 0) {
        return -0xC8;
    }
    if (fname == NULL || *fname == 0) {
        SignalSema(g_mc_sema);
        return -0xD2;
    }
    *(s32 *)g_mc_set_file_info_request = port;
    request = g_mc_set_file_info_request;
    *(s32 *)(request + 4) = slot;
    *(s32 *)(request + 8) = flags;
    *(s32 *)(request + 0xC) = block_count;
    *(s32 *)(request + 0x10) = buffer_addr;
    strncpy(request + 0x14, fname, 0x3FF);
    request[0x413] = 0;
    if (block_count >= 0) {
        sif_process_cmd_queue_b(buffer_addr, block_count << 6);
    }
    result = sceSifCallRpc(client, 13, 1, request, 0x414, g_mc_rpc_result, 4, 0, 0);
    if (result == 0) {
        g_mc_result_code = 13;
    } else {
        SignalSema(g_mc_sema);
    }
    return result;
}
