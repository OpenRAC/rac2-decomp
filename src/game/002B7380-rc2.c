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
void func_002B7380(s32 arg0) {
    s16 temp_v1;
    s16 temp_v1_2;
    u16 temp_u16;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_s1;
    u64 temp_s0;

    temp_v1 = (*(s16 *)((s8 *)(arg0) + (0xA)));
    if (temp_v1 == 9) {
        goto block_29;
    }
    temp_a0 = (*(s32 *)((s8 *)(arg0) + (0)));
    if (temp_a0 == 0) {
        goto block_29;
    }
    if (temp_a0 == 0xFFFFFFFF) {
        goto block_28;
    }
    if (temp_v1 != 5) {
        goto block_6;
    }
    if (temp_a0 == 0) {
        goto block_8;
    }
    func_00132A70(temp_a0);
    (*(s16 *)((s8 *)(arg0) + (0xA))) = 6;
    goto block_9;
block_6:
    if (temp_v1 != 6) {
        goto block_9;
    }
    if (temp_a0 != 0) {
        goto block_10;
    }
block_8:
    (*(s16 *)((s8 *)(arg0) + (0xA))) = 0;
block_9:
    if ((*(s32 *)((s8 *)(arg0) + (0))) == 0) {
        goto block_32;
    }
block_10:
    if (!((*(s16 *)((s8 *)(arg0) + (0xC))) & 0x8000)) {
        goto block_15;
    }
    if ((*(s16 *)((s8 *)(arg0) + (0xA))) & 0x8000) {
        goto block_13;
    }
    func_001333D0((*(s32 *)((s8 *)(arg0) + (0))));
    (*(s16 *)((s8 *)(arg0) + (0xA))) = (s16) ((u16) (*(s16 *)((s8 *)(arg0) + (0xA))) | 0x8000);
block_13:
    if (FastDecTimer(arg0 + 0xE) != 2) {
        goto block_17;
    }
    (*(s16 *)((s8 *)(arg0) + (0xC))) = 4;
    goto block_17;
block_15:
    if (!((*(s16 *)((s8 *)(arg0) + (0xA))) & 0x8000)) {
        goto block_18;
    }
    func_00133400((*(s32 *)((s8 *)(arg0) + (0))));
    (*(s16 *)((s8 *)(arg0) + (0xA))) = (s16) ((u16) (*(s16 *)((s8 *)(arg0) + (0xA))) ^ 0x8000);
block_17:
    if ((*(s16 *)((s8 *)(arg0) + (0xA))) & 0x8000) {
        goto block_32;
    }
block_18:
    temp_v1_2 = (*(s16 *)((s8 *)(arg0) + (0xA)));
    temp_u16 = (*(u16 *)((s8 *)(arg0) + (0xA)));
    if (temp_v1_2 == 1) {
        goto block_32;
    }
    if (temp_v1_2 == 8) {
        goto block_32;
    }
    if (temp_v1_2 == 9) {
        goto block_32;
    }
    if ((u32) (temp_u16 - 2) >= 2U) {
        goto block_23;
    }
    temp_a0_2 = (*(s32 *)((s8 *)(arg0) + (0)));
    goto block_25;
block_23:
    temp_s1 = (*(s32 *)((s8 *)(arg0) + (0)));
    temp_a0_3 = temp_s1;
    (*(u32 *)((s8 *)(arg0) + (0))) = 0xFFFFFFFF;
    temp_s0 = (u64) ((s64) arg0 << 0x20) >> 0x20;
    func_00133430(temp_a0_3, ((s32)D_002B8048), temp_s0);
    func_00132B58(temp_s1, ((s32)D_002B7FF0), temp_s0);
    goto block_32;
block_25:
    if (temp_a0_2 == 0xFFFFFFFF) {
        goto block_32;
    }
    if (temp_v1_2 != 2) {
        goto block_32;
    }
    func_00133460(temp_a0_2, ((s32)D_002B7DF8), (u64) ((s64) arg0 << 0x20) >> 0x20);
    goto block_32;
block_28:
block_29:
    if (temp_v1 == 7) {
        goto block_31;
    }
    if ((*(s32 *)((s8 *)(arg0) + (0))) != 0) {
        goto block_32;
    }
block_31:
    (*(s16 *)((s8 *)(arg0) + (0xA))) = 0;
block_32:
    if ((*(s16 *)((s8 *)(arg0) + (0xA))) != 0) {
        goto block_34;
    }
    (*(s16 *)((s8 *)(arg0) + (4))) = -1;
block_34:
    return;
}
