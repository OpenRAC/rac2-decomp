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

extern s32 sceSifBindRpc(s8 *a0, u32 a1, s32 a2);
extern s8 D_00140140[];
extern s32 D_00134744;

/* Connects to an RPC server on the IOP, retrying until the server is ready. Returns 0 on success or -1 on failure. */
s32 iop_remote_cmd_bind_server(void) {
    s32 delay;
    s32 result;

    goto loop_3;
block_1:
    delay = 0x100000;
    do {
        delay -= 1;
    } while (delay != -1);
loop_3:
    if (sceSifBindRpc(D_00140140, 0x80000003, 0) < 0) {
        result = -1;
    } else {
        if ((*(s32 *)((char *)(D_00140140) + (0x24))) == 0) {
            goto block_1;
        }
        D_00134744 = 0;
        result = 0;
    }
    return result;
}
