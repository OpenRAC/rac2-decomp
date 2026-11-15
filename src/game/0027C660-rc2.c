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

extern s8 *D_001B22A8;
extern s8 *D_001B15F4;
extern s8 *D_001B15F8;
extern void func_0029D0E0(s8 *p);
extern void func_002FC748(void);

/* Wraps the draw list in end markers so the graphics chip can finish the queued work. */
void func_0027C660(void) {
    s8 *cursor;
    s8 *packet;
    s8 *packetCopy;
    s32 tagWord;
    cursor = gDmaPacketCursor;
    D_001B15F8 = cursor;
    tagWord = 0x20000000;
    packet = D_001B15F4;
    gDmaPacketCursor = cursor + 0x10;
    *(s32 *)packet = tagWord;
    packetCopy = D_001B15F4;
    *(s32 *)(packetCopy + 4) = (s32)gDmaPacketCursor;
    *(s32 *)(D_001B15F4 + 8) = 0;
    *(s32 *)(D_001B15F4 + 0xC) = 0;
    func_0029D0E0(packetCopy);
    AppendVu1DmaChainTable1();
    packet = gDmaPacketCursor;
    *(s32 *)packet = tagWord;
    cursor = D_001B15F4;
    packetCopy = gDmaPacketCursor;
    *(s32 *)(packetCopy + 4) = (s32)(cursor + 0x10);
    packet = gDmaPacketCursor;
    *(s32 *)(packet + 8) = 0;
    packetCopy = gDmaPacketCursor;
    *(s32 *)(packetCopy + 0xC) = 0;
    cursor = gDmaPacketCursor;
    packet = D_001B15F8;
    gDmaPacketCursor = cursor + 0x10;
    *(s32 *)packet = tagWord;
    cursor = gDmaPacketCursor;
    packetCopy = D_001B15F8;
    *(s32 *)(packetCopy + 4) = (s32)cursor;
    packet = D_001B15F8;
    *(s32 *)(packet + 8) = 0;
    cursor = D_001B15F8;
    *(s32 *)(cursor + 0xC) = 0;
}
