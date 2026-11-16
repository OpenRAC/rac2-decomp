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

extern s32 sceSifCallRpc(s8 *a0, s32 a1, s32 a2, s8 *a3, s32 t0, s32 *t1, s32 t2, s32 t3, s32 s9);
extern s32 sif_rpc_is_handle_valid(s8 *a0, s32 a1);
extern void debug_print_stub(s8 *a0);
extern s8 g_vibration_rpc_client[];
extern s8 g_vibration_packet[];
extern s8 g_str_vibration_debug[];

/* Sends a command with extra data to the vibration (rumble) server. Returns 1 on success. */
s32 dbc_send_vibration_command(s32 port, s32 command, s32 *size_ptr, u8 *data) {
    s32 i;
    s32 result;
    s8 *packet;

    packet = g_vibration_packet;
    *(s32 *)g_vibration_packet = port;
    *(s32 *)(packet + 4) = command;
    *(s32 *)(packet + 8) = *size_ptr;
    i = 0;
    if (*size_ptr > 0) {
        packet += 0xC;
        do {
            packet[i] = data[i];
            i += 1;
        } while (i < *size_ptr);
    }
    if (sif_rpc_is_handle_valid(g_vibration_rpc_client, i) == 1) {
        return 0;
    }
    result = sceSifCallRpc(g_vibration_rpc_client, 0x8000091B, 1, g_vibration_packet, 0x400, g_vibration_packet, 0x400, 0, 0);
    if (result < 0) {
        debug_print_stub(g_str_vibration_debug);
        return 0;
    }
    return 1;
}
