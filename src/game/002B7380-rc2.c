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

extern void func_00132A70();
extern void snd_send_cmd25_with_settings();
extern void func_001333D0();
extern void snd_send_cmd46();
extern void snd_send_cmd50_with_settings();
extern void snd_send_cmd79_with_settings();
extern s32 FastDecTimer();

extern s8 g_music_cmd79_settings[];
extern s8 g_music_cmd25_settings[];
extern s8 g_music_cmd50_settings[];
/* Updates one music stream channel each frame: starts, pauses, fades out or clears it depending on its state. */
void snd_update_music_channel(s32 channel) {
    s16 state;
    s16 state_now;
    u16 state_bits;
    s32 handle;
    s32 handle_now;
    s32 handle_copy;
    s32 old_handle;
    u64 channel_addr;

    state = (*(s16 *)((s8 *)(channel) + (0xA)));
    if (state == 9) {
        goto block_29;
    }
    handle = (*(s32 *)((s8 *)(channel) + (0)));
    if (handle == 0) {
        goto block_29;
    }
    if (handle == 0xFFFFFFFF) {
        goto block_28;
    }
    if (state != 5) {
        goto block_6;
    }
    if (handle == 0) {
        goto block_8;
    }
    func_00132A70(handle);
    (*(s16 *)((s8 *)(channel) + (0xA))) = 6;
    goto block_9;
block_6:
    if (state != 6) {
        goto block_9;
    }
    if (handle != 0) {
        goto block_10;
    }
block_8:
    (*(s16 *)((s8 *)(channel) + (0xA))) = 0;
block_9:
    if ((*(s32 *)((s8 *)(channel) + (0))) == 0) {
        goto block_32;
    }
block_10:
    if (!((*(s16 *)((s8 *)(channel) + (0xC))) & 0x8000)) {
        goto block_15;
    }
    if ((*(s16 *)((s8 *)(channel) + (0xA))) & 0x8000) {
        goto block_13;
    }
    func_001333D0((*(s32 *)((s8 *)(channel) + (0))));
    (*(s16 *)((s8 *)(channel) + (0xA))) = (s16) ((u16) (*(s16 *)((s8 *)(channel) + (0xA))) | 0x8000);
block_13:
    if (FastDecTimer(channel + 0xE) != 2) {
        goto block_17;
    }
    (*(s16 *)((s8 *)(channel) + (0xC))) = 4;
    goto block_17;
block_15:
    if (!((*(s16 *)((s8 *)(channel) + (0xA))) & 0x8000)) {
        goto block_18;
    }
    snd_send_cmd46((*(s32 *)((s8 *)(channel) + (0))));
    (*(s16 *)((s8 *)(channel) + (0xA))) = (s16) ((u16) (*(s16 *)((s8 *)(channel) + (0xA))) ^ 0x8000);
block_17:
    if ((*(s16 *)((s8 *)(channel) + (0xA))) & 0x8000) {
        goto block_32;
    }
block_18:
    state_now = (*(s16 *)((s8 *)(channel) + (0xA)));
    state_bits = (*(u16 *)((s8 *)(channel) + (0xA)));
    if (state_now == 1) {
        goto block_32;
    }
    if (state_now == 8) {
        goto block_32;
    }
    if (state_now == 9) {
        goto block_32;
    }
    if ((u32) (state_bits - 2) >= 2U) {
        goto block_23;
    }
    handle_now = (*(s32 *)((s8 *)(channel) + (0)));
    goto block_25;
block_23:
    old_handle = (*(s32 *)((s8 *)(channel) + (0)));
    handle_copy = old_handle;
    (*(u32 *)((s8 *)(channel) + (0))) = 0xFFFFFFFF;
    channel_addr = (u64) ((s64) channel << 0x20) >> 0x20;
    snd_send_cmd50_with_settings(handle_copy, ((s32)g_music_cmd50_settings), channel_addr);
    snd_send_cmd25_with_settings(old_handle, ((s32)g_music_cmd25_settings), channel_addr);
    goto block_32;
block_25:
    if (handle_now == 0xFFFFFFFF) {
        goto block_32;
    }
    if (state_now != 2) {
        goto block_32;
    }
    snd_send_cmd79_with_settings(handle_now, ((s32)g_music_cmd79_settings), (u64) ((s64) channel << 0x20) >> 0x20);
    goto block_32;
block_28:
block_29:
    if (state == 7) {
        goto block_31;
    }
    if ((*(s32 *)((s8 *)(channel) + (0))) != 0) {
        goto block_32;
    }
block_31:
    (*(s16 *)((s8 *)(channel) + (0xA))) = 0;
block_32:
    if ((*(s16 *)((s8 *)(channel) + (0xA))) != 0) {
        goto block_34;
    }
    (*(s16 *)((s8 *)(channel) + (4))) = -1;
block_34:
    return;
}
