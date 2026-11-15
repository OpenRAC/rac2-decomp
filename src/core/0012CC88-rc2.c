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

struct T44 { s32 f[11]; };
extern s8 D_0013BBC8[];
extern s32 mpeg_peek_bits(s64,s32);
extern void mpeg_skip_bits(s64,s32);
extern u32 mpeg_read_bits(s64,s32);
 
extern void mpeg_skip_to_start_code(s64);
/* Reads the extension and user data blocks that follow a header, running a handler for each extension type. */
void mpeg_read_extension_data(s64 decoderAddr) {
    struct T44 tab;
    s32 startCode;
    u32 idx;
    tab=*(struct T44 *)D_0013BBC8;
    mpeg_skip_to_start_code(decoderAddr);
    while ((startCode=mpeg_peek_bits(decoderAddr,0x20))==0x1B5 || startCode==0x1B2) {
        if (startCode==0x1B5) {
            mpeg_skip_bits(decoderAddr,0x20);
            idx=mpeg_read_bits(decoderAddr,4);
            idx=(idx>10)?0:idx;
            ((void (*)(s64))tab.f[idx])(decoderAddr);
            mpeg_skip_to_start_code(decoderAddr);
        } else {
            mpeg_skip_bits(decoderAddr,0x20);
            mpeg_skip_to_start_code(decoderAddr);
        }
    }
}
