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

extern s8 g_mc_rpc_client[];
extern s8 g_mc_format_request[];
extern s8 g_mc_rpc_result[];
extern s32 g_mc_sema;
extern s32 g_mc_result_code;
extern void SignalSema(s32);
extern s32 PollSema(s32);
extern s32 sceSifCallRpc(s32, s32, s32, s32, s32, s32, s32, s32, s32);

/* Sends a memory card command that takes a port and a slot (probably the format command). */
s32 sceMcFormat(s32 port, s32 slot) {
    s8 *client = g_mc_rpc_client;
    s8 *request;
    s32 slot_copy = slot;
    s32 port_copy;
    s32 result;

    if (*(s32 *)(client + 0x24) == 0) {
        return -0x64;
    }
    port_copy = port;
    if (PollSema(g_mc_sema) < 0) {
        return -0xC8;
    }
    request = g_mc_format_request;
    *(s32 *)(request + 4) = port_copy;
    *(s32 *)(request + 8) = slot_copy;
    result = sceSifCallRpc((s32)client, 0x10, 1, (s32)request, 0x30, (s32)g_mc_rpc_result, 4, 0, 0);
    if (result == 0) {
        g_mc_result_code = 0x10;
    } else {
        SignalSema(g_mc_sema);
    }
    return result;
}
