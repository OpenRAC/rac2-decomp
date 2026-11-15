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
extern s8 *D_001B20E4;
extern s8 *D_001B20E0;
extern s32 D_001A72D4;
extern s32 D_001A72D0;
extern void func_0029D0E0(s8 *);
extern s32 gfx_append_vu1_preset_a(void);

/* Links the render packet buffers together into one chain and restores the buffer mark. */
void gfx_link_packet_chain(void) {
    s32 tag_word;
    s8 *first_tag;

    D_001B20E4 = g_dma_packet_cursor;
    tag_word = 0x20000000;
    g_dma_packet_cursor = g_dma_packet_cursor + 0x10;
    (*(s32 *)((s8 *)(D_001B20E0) + (0))) = tag_word;
    first_tag = D_001B20E0;
    (*(s8 **)((s8 *)(first_tag) + (4))) = g_dma_packet_cursor;
    (*(s32 *)((s8 *)(D_001B20E0) + (8))) = 0;
    (*(s32 *)((s8 *)(D_001B20E0) + (0xC))) = 0;
    func_0029D0E0(first_tag);
    (void) gfx_append_vu1_preset_a();
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (0))) = tag_word;
    (*(s8 **)((s8 *)(g_dma_packet_cursor) + (4))) = D_001B20E0 + 0x10;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (8))) = 0;
    (*(s32 *)((s8 *)(g_dma_packet_cursor) + (0xC))) = 0;
    g_dma_packet_cursor = g_dma_packet_cursor + 0x10;
    (*(s32 *)((s8 *)(D_001B20E4) + (0))) = tag_word;
    (*(s8 **)((s8 *)(D_001B20E4) + (4))) = g_dma_packet_cursor;
    (*(s32 *)((s8 *)(D_001B20E4) + (8))) = 0;
    (*(s32 *)((s8 *)(D_001B20E4) + (0xC))) = 0;
    D_001A72D0 = D_001A72D4;
}
