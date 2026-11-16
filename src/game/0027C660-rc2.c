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

extern s8 *g_dma_packet_cursor;
extern s8 *g_clear_color_packet;
extern s8 *g_gfx_packet_cursor;
extern void func_0029D0E0(s8 *p);
extern void gfx_append_vu1_preset_a(void);

/* Wraps the draw list in end markers so the graphics chip can finish the queued work. */
void DoGifPaging(void) {
    s8 *cursor;
    s8 *packet;
    s8 *packet_copy;
    s32 tag_word;
    cursor = g_dma_packet_cursor;
    g_gfx_packet_cursor = cursor;
    tag_word = 0x20000000;
    packet = g_clear_color_packet;
    g_dma_packet_cursor = cursor + 0x10;
    *(s32 *)packet = tag_word;
    packet_copy = g_clear_color_packet;
    *(s32 *)(packet_copy + 4) = (s32)g_dma_packet_cursor;
    *(s32 *)(g_clear_color_packet + 8) = 0;
    *(s32 *)(g_clear_color_packet + 0xC) = 0;
    func_0029D0E0(packet_copy);
    gfx_append_vu1_preset_a();
    packet = g_dma_packet_cursor;
    *(s32 *)packet = tag_word;
    cursor = g_clear_color_packet;
    packet_copy = g_dma_packet_cursor;
    *(s32 *)(packet_copy + 4) = (s32)(cursor + 0x10);
    packet = g_dma_packet_cursor;
    *(s32 *)(packet + 8) = 0;
    packet_copy = g_dma_packet_cursor;
    *(s32 *)(packet_copy + 0xC) = 0;
    cursor = g_dma_packet_cursor;
    packet = g_gfx_packet_cursor;
    g_dma_packet_cursor = cursor + 0x10;
    *(s32 *)packet = tag_word;
    cursor = g_dma_packet_cursor;
    packet_copy = g_gfx_packet_cursor;
    *(s32 *)(packet_copy + 4) = (s32)cursor;
    packet = g_gfx_packet_cursor;
    *(s32 *)(packet + 8) = 0;
    cursor = g_gfx_packet_cursor;
    *(s32 *)(cursor + 0xC) = 0;
}
