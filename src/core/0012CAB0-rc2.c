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

extern void mpeg_skip_to_start_code(s8 *);
extern s32 mpeg_read_bits(s8 *, s32);
extern void mpeg_read_sequence_header(s8 *);
extern void mpeg_read_picture_header(s8 *);
extern void mpeg_read_gop_header(s8 *);
extern void mpeg_dispatch_callback(s32, void *);

/* Reads headers from the video stream until a picture begins, then returns its type. Returns 0 at the end of the stream. */
s32 mpeg_read_headers_until_picture(s8 *decoder_ptr) {
    struct {
        s32 a;
        s32 pad;
        s64 b;
        s64 c;
    } blk;
    u32 start_code;

    for (;;) {
        mpeg_skip_to_start_code(decoder_ptr);
        start_code = mpeg_read_bits(decoder_ptr, 0x20);
        switch (start_code) {
        case 0x1B3:
            mpeg_read_sequence_header(decoder_ptr);
            break;
        case 0x1B8:
            mpeg_read_gop_header(decoder_ptr);
            break;
        case 0x100:
            mpeg_read_picture_header(decoder_ptr);
            blk.a = 5;
            blk.b = -1;
            blk.c = -1;
            mpeg_dispatch_callback(*(s32 *)(decoder_ptr + 0x858), &blk);
            *(s64 *)(decoder_ptr + 0x830) = blk.c;
            *(s64 *)(decoder_ptr + 0x828) = blk.b;
            return *(s32 *)(decoder_ptr + 0x150);
        case 0x1B7:
            return 0;
        }
    }
}
