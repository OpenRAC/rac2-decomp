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

extern void FlushCache();
extern s32 UploadMipTexture();
extern s32 fast_decompress();
extern s32 g_level_data_ptr;
extern s32 g_vram_cursor;
extern s32 g_vram_frame_base;
extern u8 g_language;
extern s32 g_dma_packet_cursor;
extern s64 g_overlay_quad_packet;
extern s64 g_fade_strip_packet;

/* Loads a data block for the next scene and keeps its first two values for drawing. */
void scene_load_texture_block(void) {
    s64 values[4];
    s32 level_index;
    s32 clamped_index;
    s32 archive;
    s32 loaded;

    archive = g_level_data_ptr;
    if (*(s32 *)(archive + 0x50) != -1) {
        level_index = g_language - 1;
        clamped_index = (level_index > -1) ? level_index : 0;
        FlushCache(0);
        fast_decompress(archive + *(s32 *)(archive + 0x50), g_dma_packet_cursor);
        FlushCache(0);
        loaded = g_dma_packet_cursor;
        g_vram_cursor = g_vram_frame_base;
        UploadMipTexture(loaded + *(s32 *)(loaded + 4), values);
        g_overlay_quad_packet = values[0];
        UploadMipTexture(loaded + *(s32 *)(loaded + clamped_index * 4 + 8), values);
        g_fade_strip_packet = values[0];
        g_vram_frame_base = g_vram_cursor + 0x2000;
    }
}
