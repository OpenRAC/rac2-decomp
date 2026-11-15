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
extern void func_00132B58();
extern void func_001333D0();
extern void func_00133400();
extern void func_00133430();
extern void func_00133460();
extern s32 func_00282978();

extern s8 D_002B7DF8[];
extern s8 D_002B7FF0[];
extern s8 D_002B8048[];
/* Updates one music stream channel each frame: starts, pauses, fades out or clears it depending on its state. */
void func_002B7380(s32 channel) {
    s16 state;
    s16 stateNow;
    u16 stateBits;
    s32 handle;
    s32 handleNow;
    s32 handleCopy;
    s32 oldHandle;
    u64 channelAddr;

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
    SendSoundCommand46((*(s32 *)((s8 *)(channel) + (0))));
    (*(s16 *)((s8 *)(channel) + (0xA))) = (s16) ((u16) (*(s16 *)((s8 *)(channel) + (0xA))) ^ 0x8000);
block_17:
    if ((*(s16 *)((s8 *)(channel) + (0xA))) & 0x8000) {
        goto block_32;
    }
block_18:
    stateNow = (*(s16 *)((s8 *)(channel) + (0xA)));
    stateBits = (*(u16 *)((s8 *)(channel) + (0xA)));
    if (stateNow == 1) {
        goto block_32;
    }
    if (stateNow == 8) {
        goto block_32;
    }
    if (stateNow == 9) {
        goto block_32;
    }
    if ((u32) (stateBits - 2) >= 2U) {
        goto block_23;
    }
    handleNow = (*(s32 *)((s8 *)(channel) + (0)));
    goto block_25;
block_23:
    oldHandle = (*(s32 *)((s8 *)(channel) + (0)));
    handleCopy = oldHandle;
    (*(u32 *)((s8 *)(channel) + (0))) = 0xFFFFFFFF;
    channelAddr = (u64) ((s64) channel << 0x20) >> 0x20;
    SendSoundCommand50_00133430(handleCopy, ((s32)D_002B8048), channelAddr);
    SendSoundCommand25(oldHandle, ((s32)D_002B7FF0), channelAddr);
    goto block_32;
block_25:
    if (handleNow == 0xFFFFFFFF) {
        goto block_32;
    }
    if (stateNow != 2) {
        goto block_32;
    }
    SendSoundCommand79(handleNow, ((s32)D_002B7DF8), (u64) ((s64) channel << 0x20) >> 0x20);
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
